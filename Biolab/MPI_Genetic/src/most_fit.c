#include "Genetic.h"
int most_fit(int **popu)
{
        extern NUM;
        int max_fit = 0;
    int score = 0;
    int i = 0;
    for (i=0;i<NUM;++i)
    {
        score = num_pair(popu[i]);
        if (score > max_fit)
            max_fit = score;
    }
    return max_fit;
}
