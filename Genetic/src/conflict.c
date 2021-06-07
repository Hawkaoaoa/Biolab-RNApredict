#include "Genetic.h"

int conflict(int *individual)   /* 该个体中的茎区是否冲突 */
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
