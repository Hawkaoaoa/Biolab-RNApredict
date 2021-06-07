# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

#define CROSS 0.4 /* 交叉 */
#define MUTATE 0.05    /* 变异 */
#define NUM 50   /* 每一代的个体数 */
#define MAXITER 25  /* 计数器， 最大适应度不变的次数 （停止准则） */

typedef enum {false,true} bool;

struct mysample{
    int start;
    int end;
    int length;
}sample[1000];

int num_stem = 0;   /* 找到的长度 >1 的茎区数 */

void pool(char *seq)          /* 构建茎区池 */
{
    int len = strlen(seq);
    int **a;
    a = (int**)malloc(sizeof(int*)*len);  /* 找茎区全集的矩阵 a */
    int i = 0,j = 0;
    for (i=0;i<len;++i)
        a[i] = (int*)malloc(sizeof(int)*len);

    for (i=0;i<len-3;++i)    /* 能配对的填为1 */
    {
        for (j=i+4;j<len;++j)
        {
            if ((seq[i] == 'A' && seq[j] == 'U' || seq[i] == 'U' && seq[j] =='A') \
                || (seq[i] == 'G' && seq[j] == 'C' || seq[i] == 'C' && seq[j] =='G')\
                || (seq[i] == 'G' && seq[j] == 'U' || seq[i] == 'U' && seq[j] =='G'))
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }

    int num1 = 0, num2 = 0;   /* 开始搜索连续茎区的起始点、终止点 */
    int k = 0;   /* 记录茎区的长度 */
    bool flag;    /* 是否找到了 长度＞1 的茎区 */

    for (i=0;i<len-3;++i)                 /* 上三角矩阵 */
    {
        for (j=i+4;j<len;++j)
        {
            if (a[i][j] == 1)
            {
                num1=i;
                num2=j;
                k = 1;
                flag = false;
                num1++;
                num2--;

                while(a[num1][num2] == 1)
                {
                    k++;
                    flag = true;
                    num1++;
                    num2--;
                    if (num2 < num1 + 4)
                        break;
                }

                if (flag == true)
                {
                    sample[num_stem].start = i;
                    sample[num_stem].end = j;
                    sample[num_stem].length = k;
                    num_stem++;
                }
            }
        }
    }
    free(a);
}

int is_compatible(int i, int j)      /* 相容性检测 返回值为1则为相容*/
{
    if ((sample[i].start+sample[i].length<=sample[j].start && sample[i].end-sample[i].length>=sample[j].end)\
        || (sample[j].start+sample[j].length<=sample[i].start && sample[j].end-sample[j].length>=sample[i].end)\
        || sample[i].end<sample[j].start || sample[j].end<sample[i].start)
        return 1;
    else
        return 0;
}

void create_T()    /* 创造表示 si,sj 茎区是否相容的T矩阵 */
{
    int N = num_stem - 1;
    int **T;
    T = (int**)malloc(sizeof(int*)*N);  /* 创建 T 矩阵 */
    int i = 0,j = 0;
    for (i=0;i<N;++i)
        T[i] = (int*)malloc(sizeof(int)*N);

    for (i=0;i<N;++i)
    {
        for (j=0;j<N;++j)
        {
            if (is_compatible(i,j))
                T[i][j] = 1;
            else
                T[i][j] = 0;
            if (i == j)
                T[i][j] = 0;
        }
    }
}
/*
void sort(int *a, int l)      //a为数组地址，l为数组长度。  从大到小排序
{
    int i, j;
    int tmp;
    for(i = 0; i < l - 1; i ++)
        for(j = i+1; j < l; j ++)
        {
            if(a[i] < a[j])
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
} */

/*
void energy_table()
{
    int **table ;
    table = (int**)malloc(sizeof(int*)*6);  // 创建 energy_table 矩阵
    int i = 0,j = 0;
    for (i=0;i<6;++i)
        table[i] = (int*)malloc(sizeof(int)*6);
    char *index[6] = {"AU","CG","GC","UA","GU","UG"};
}


int calcu_energy(int x[], int len)               /* 计算自由能
{
    int energy = 0;
    int i = 0;
    int left = 0, right = 0, length = 0;
    for (i=0;i<len;++i)
    {
        if (x[i] == 1)
        {
            left = sample[i].start;
            right = sample[i].end;
            length = sample[i].length;

        }
    }

    return energy;
}
*/
int num_pair(int *individual)              /* 以配对碱基数对判断标准来计算适应度分数 */
{
    int N = num_stem - 1;
    int i = 0;
    int num = 0;
    for (i=0;i<N;++i)
    {
        if (individual[i] == 1)
        {
            num += sample[i].length;
        }
    }

    return num;
}

int conflict(int *individual)
{
    int i = 0, j = 0;
    int N = num_stem - 1;

    for (i=0;i<N-1;++i)
    {
        for (j=i+1;j<N;++j)
        {
            if (individual[i] == 1 && individual[j] == 1) {
                if (is_compatible(i, j))
                    continue;
                else
                    return 1;
            }
        }
    }
    return 0;
}

int max_index(int *individual)
{
    int i = 0;
    int N = num_stem - 1;
    int tmp_max = 0;
    int index_max;
    int flag = 0;

    for (i=0;i<N;++i)
    {
        if (individual[i] == 1) {
            flag = 1;
            if (sample[i].length > tmp_max)
                index_max = i;
        }
    }
    if (flag == 0)
        return -1;
    else
        return index_max;
}

int *modify(int *individual)            /* 对不相容的茎区组合进行修正 */
{
    int N = num_stem - 1;
    int i = 0;
    int index_max;
    int tmp_max = 0;

    int *new_individual = (int *)calloc(sizeof(int),N);

    for (i=0;i<N;++i)
        new_individual[i] = 0;

    int flag = N;

    while (flag > 0) {
            flag--;
            if (max_index(individual) == -1)
                break;
            index_max = max_index(individual);              /* 从大到小依次加入到新序列中，一有冲突就不加这个 */
            new_individual[index_max] = 1;
            individual[index_max] = 0;

            if (conflict(new_individual))
            {
                new_individual[index_max] = 0;
            }
            else
                continue;
    }

    return new_individual;
}

int **Init()      /* 生成一个含有 NUM 个个体的随机0，1矩阵 （初始种群） */
{
    int N = num_stem - 1;
    int **population;
    population = (int**)malloc(sizeof(int*)*NUM);
    int i = 0,j = 0;
    for (i=0;i<NUM;++i)
        population[i] = (int*)malloc(sizeof(int)*N);

    srand((unsigned)time(NULL));
    for (i=0;i<NUM;++i)
    {
        for (j=0;j<N;++j)
        {
            if (rand()%2 == 0)
                population[i][j] = 1;
            else
                population[i][j] = 0;
        }
    }
    return population;
}

int **select(int *fit_score, int **old_popu)
{
    int i = 0, sum = 0;
    int N = num_stem - 1;

    for (i;i<NUM;++i)
    {
        sum += fit_score[i];          /* 所有个体总得分 */
    }

    float portion[NUM];        /* 创造轮盘 */

    for (i=0;i<NUM;++i)
    {
        portion[i] = (float)fit_score[i] / (float)sum;
    }

    float boundary[NUM];     /* 线性轮盘， 此处设置每个个体所处边界，作为选择标准 */
    float bound = 0;

    for (i=0;i<NUM;++i)               /* 内存不够分配了...... */
    {
        bound += portion[i];
        boundary[i] = bound;
    }

    srand((unsigned)time(NULL));

    int **new_popu;
    new_popu = (int**)malloc(sizeof(int*)*NUM);

    for (i=0;i<NUM;++i)
        new_popu[i] = (int*)malloc(sizeof(int)*N);                  /* 选择出来的新种群 */

    int k = 0;
    int j = 0;

    for (i=0;i<NUM;++i)
    {
        float num = rand() % 1000 / 1000.0;
        if (num <= boundary[0])                  /* 头尾两种极端情况 ，小数 有可能会有误差，所以特殊处理 */
        {
            new_popu[k] = old_popu[0];
            k++;
        }
        if (num >= boundary[NUM-2])
        {
            new_popu[k] = old_popu[NUM-1];
            k++;
        }
        for (j=0;j<NUM-1;++j)
        {
            if (num >= boundary[j] && num <= boundary[j+1])        /* 根据概率处在的不同的区间，选择对应的个体遗传到下一代 */
            {
                new_popu[k] = old_popu[j+1];
                k++;
            }
        }
    }

    return new_popu;
}

void cross(int **popu)
{
    int N = num_stem - 1;
    int i = 0, j = 0;
    int num = 0;
    int tmp;
    srand((unsigned)time(NULL));
    double flag1;
    int flag2;
    int individual_tobe_cross[2];

    for (i=0;i<NUM;++i)
    {
        flag1 = rand() % 1000 / 1000.0;
        if (flag1 < CROSS)                      /* 遍历每个个体，若满足CROSS, 则会发生交叉 */
        {
            individual_tobe_cross[num] = i;
            num += 1;
        }
        if (num == 2)
        {
            flag2 = rand() % N;
            for (j=flag2;j<N;++j)              /* 随机选择一个交叉位点，这个位点之后的部分做交换 */
            {
                tmp = popu[individual_tobe_cross[0]][j];
                popu[individual_tobe_cross[0]][j] = popu[individual_tobe_cross[1]][j];
                popu[individual_tobe_cross[1]][j] = tmp;
            }
        }
    }
}

void mutate(int **popu)
{
    int N = num_stem - 1;
    int i = 0;
    srand((unsigned)time(NULL));
    double flag1;
    int flag2;

    for (i=0;i<NUM;++i)
    {
        flag1 = rand() % 1000 / 1000.0;
        if (flag1 < MUTATE)                      /* 遍历每个个体，若满足MUTATE, 则会发生突变 */
        {
            flag2 = rand() % N;
            if (popu[i][flag2] == 1)             /* 1变为0， 0变为1 */
                popu[i][flag2] = 0;
            else
                popu[i][flag2] = 1;
        }
    }
}

int most_fit(int **popu)
{
    int i = 0;
    int max_fit = 0;
    int score = 0;

    for (i=0;i<NUM;++i)
    {
        score = num_pair(popu[i]);
        if (score > max_fit)
            max_fit = score;
    }
    return max_fit;
}

int main(int argc, char *argv[])
{
    char *seq="GGGUUAUCCC";
    int i,j;

    pool(seq);           /* 生成茎区池 */
    /* create_T();  */

    int N = num_stem - 1;          /* 连续茎区的个数 */
    int fit_score[NUM];    /* 记录每个个体的分数，为选择做铺垫 */
    int **new_popu;         /* 选择 后的新种群 */

    int **get_init = Init();    /* 初始化种群 */

    for (i=0;i<NUM;++i)
        get_init[i] = modify(get_init[i]);       /* 修正 */

    for (i=0;i<NUM;++i)                 /* 每个个体得分 */
    {
        fit_score[i] = num_pair(get_init[i]);
    }

    int pre_max_fit = 0;
    int now_max_fit = 0;
    int num_iter = MAXITER;

    while (num_iter > 0)
    {
        new_popu = select(fit_score,get_init);          /* 选择 */
        cross(new_popu);
        mutate(new_popu);

        for (i=0;i<NUM;++i)               /* 修正 */
            new_popu[i] = modify(new_popu[i]);

        for (i=0;i<NUM;++i)                 /* 每个个体得分 */
            fit_score[i] = num_pair(new_popu[i]);

        now_max_fit = most_fit(new_popu);    /* 当前种群中的最大适应度 */
        printf("%d\n",now_max_fit);
        if (now_max_fit > pre_max_fit)
        {
            pre_max_fit = now_max_fit;
            num_iter = MAXITER;
        }
        else
            num_iter--;

        get_init = new_popu;
    }

    for (i=0;i<NUM;++i)
    {
        for (j=0;j<N;++j)
            printf("%d", get_init[i][j]);
        printf("\n");
    }
    printf("%d\n",sample[4].start);
    printf("%d\n",sample[4].end);
    printf("%d\n",sample[4].length);

    return 0;
 }
