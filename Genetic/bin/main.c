#include "Genetic.h"

int num_stem = 0;   /* 找到的长度 >1 的茎区数 */

int main(int argc, char *argv[])
{
    FILE *fp1 = fopen("input.txt","r");
    
    char seq[100];
    fgets(seq, 100, fp1);
    fclose(fp1);
    
    int len = strlen(seq);              /* 序列长度 */
    int i, j;
    int myrank, nprocs;
    int p, k;                     /* 后续输出结果要用 */

    MPI_Init(&argc,&argv);              /* MPI 初始化 */
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    NUM = NUM / nprocs;              /* 每个进程需要处理的 */

    sleep(myrank);              /* 在每个进程之间造成一定延迟，体现种群生成的随机性！ */

    char tmp[len];       /* 后续输出结果所用 */

    pool(seq);

    int N = num_stem - 1;
    int fit_score[NUM];
    int **new_popu;

    int **get_init = Init();

    for (i = 0; i < NUM; ++i)
        get_init[i] = modify(get_init[i]);

    for (i = 0; i < NUM; ++i)
    {
        fit_score[i] = num_pair(get_init[i]);
    }

    int pre_max_fit = 0;        /* 迭代选择过程中用于储存最大适应度，（停止准则） */
    int now_max_fit = 0;
    int num_iter = MAXITER;

    while (num_iter > 0) {              /* 迭代 */
        new_popu = Select(fit_score, get_init);
        cross(new_popu);
        mutate(new_popu);

        for (i=0; i < NUM; ++i)
            new_popu[i] = modify(new_popu[i]);

        for (i=0; i < NUM; ++i)
            fit_score[i] = num_pair(new_popu[i]);

        now_max_fit = most_fit(new_popu);

        if (now_max_fit > pre_max_fit) {       /* 有新的最大适应度出现，计数器回到初始值 */
            pre_max_fit = now_max_fit;
            num_iter = MAXITER;
        } else
            num_iter--;

        get_init = new_popu;
    }
                                    /* 此时得到的 get_init 即是最后得到的优化种群！ */
    int tmp1 = most_fit(get_init);      /* 最后筛选的标准还是找出适应度最大的个体 */
    int tmp2[NUM];
    int tmp3 = 0;

    for (i = 0; i < NUM; ++i) {
        if (num_pair(get_init[i]) == tmp1) {
            tmp2[tmp3] = i;
            tmp3 += 1;
        }                           /* tmp3 记录的是找到拥有最大适应度的个体个数，可能不止一个 */
    }

    char result[tmp3][len];             /* 初始化矩阵，后面配对用括号表示 */
    int k1, k2;
    for (i = 0; i < tmp3; ++i) {
        for (j = 0; j < len; ++j)
            result[i][j] = '.';
    }

    for (i = 0; i < tmp3; ++i) {
        for (j = 0; j < N; ++j) {
            if (get_init[tmp2[i]][j] == 1) {
                for (k1 = 0; k1 < sample[j].length; ++k1) {
                    result[i][sample[j].start + k1] = '(';
                }
                for (k2 = 0; k2 < sample[j].length; ++k2) {
                    result[i][sample[j].end - k2] = ')';
                }
            }
        }
    }

    if (myrank != 0)            /* 子进程将结果发送到主进程 */
    {
        MPI_Send(&tmp3, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        for (i=0;i<tmp3;++i)
        {
            MPI_Send(result[i], len, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
    }

    if (myrank == 0)            /* 主进程接受 */
    {
        for (p=1;p<nprocs;++p)
        {
            MPI_Recv(&k, 1, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (i=0;i<k;++i)
            {
                MPI_Recv(tmp, len, MPI_CHAR, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (j=0;j<len;++j)
                    printf("%c",tmp[j]);
                printf("\n");
            }
        }
    }

    MPI_Finalize();
    
    return 0;
}
