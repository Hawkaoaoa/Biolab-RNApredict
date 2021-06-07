#include "Genetic.h"
void mutate(int **popu)
{
        extern NUM;
        extern num_stem;
        int N = num_stem - 1;
    int i = 0;
    srand((unsigned)time(NULL));
    double flag1;
    int flag2;

    for (i=0;i<NUM;++i)
    {
        flag1 = rand() % 1000 / 1000.0;
        if (flag1 < MUTATE)
        {
            flag2 = rand() % N;
            if (popu[i][flag2] == 1)
                popu[i][flag2] = 0;
            else
                popu[i][flag2] = 1;
        }
    }
}
