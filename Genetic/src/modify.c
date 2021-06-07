#include "Genetic.h"
int *modify(int *individual)        /* 对不相容的茎区组合进行修正 */
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
        index_max = max_index(individual);
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
