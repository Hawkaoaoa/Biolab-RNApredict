#include "Genetic.h"
int most_fit(int **popu)        /* 输出种群中的最大适应度 */
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
