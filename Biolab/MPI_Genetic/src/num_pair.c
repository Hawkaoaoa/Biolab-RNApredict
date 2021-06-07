#include "Genetic.h"
int num_pair(int *individual)
{
        extern NUM;
        extern num_stem;
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

