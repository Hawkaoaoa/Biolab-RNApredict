#include "Genetic.h"
int num_pair(int *individual)   /* 以配对碱基数对判断标准来计算适应度分数 */
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
