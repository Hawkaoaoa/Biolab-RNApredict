#include "Genetic.h"
int max_index(int *individual)
{
        extern NUM;
        extern num_stem;
         int N = num_stem - 1;
    int tmp_max = 0;
    int index_max;
    int flag = 0;
    int i = 0;
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
