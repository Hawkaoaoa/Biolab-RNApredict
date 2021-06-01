void mutate(int **popu)
{
    int N = num_stem - 1;
    int i = 0;
    srand((unsigned)time(NULL));
    double flag1;
    int flag2;

    for (i=0;i<NUM;++i)
    {
        flag1 = rand() % 1000 / 1000.0;
        if (flag1 < MUTATE) /* 遍历每个个体，若满足MUTATE, 则会发生突变 */
        {
            flag2 = rand() % N;
            if (popu[i][flag2] == 1)        /* 1变为0， 0变为1 */
                popu[i][flag2] = 0;
            else
                popu[i][flag2] = 1;
        }
    }
}
