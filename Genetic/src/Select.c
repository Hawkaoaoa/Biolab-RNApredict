#include "Genetic.h"
int **Select(int *fit_score, int **old_popu)
{
    int i = 0, sum = 0;
    int N = num_stem - 1;

    for (i;i<NUM;++i)
    {
        sum += fit_score[i];        /* 所有个体总得分 */
    }

    float portion[NUM];     /* 创造轮盘 */

    for (i=0;i<NUM;++i)
    {
        portion[i] = (float)fit_score[i] / (float)sum;
    }

    float boundary[NUM];        /* 线性轮盘， 此处设置每个个体所处边界，作为选择标准 */
    float bound = 0;

    for (i=0;i<NUM;++i)
    {
        bound += portion[i];
        boundary[i] = bound;
    }

    srand((unsigned)time(NULL));

    int **new_popu;
    new_popu = (int**)malloc(sizeof(int*)*NUM);

    for (i=0;i<NUM;++i)
        new_popu[i] = (int*)malloc(sizeof(int)*N);  /* 选择出来的新种群 */

    int k = 0;
    int j = 0;

    for (i=0;i<NUM;++i)
    {
        float num = rand() % 1000 / 1000.0;
        if (num <= boundary[0])     /* 头尾两种极端情况 ，小数 有可能会有误差，所以特殊处理 */
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
            if (num >= boundary[j] && num <= boundary[j+1]) /* 根据概率处在的不同的区间，选择对应的个体遗传到下一代 */
            {
                new_popu[k] = old_popu[j+1];
                k++;
            }
        }
    }

    return new_popu;
}
