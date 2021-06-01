int **Init()        /* 生成一个含有 NUM 个个体的随机0，1矩阵 （初始种群） */
{
    int N = num_stem - 1;
    int **population;
    population = (int**)malloc(sizeof(int*)*NUM);
    int i = 0,j = 0;
    for (i=0;i<NUM;++i)
        population[i] = (int*)malloc(sizeof(int)*N);

    srand((unsigned)time(NULL));
    for (i=0;i<NUM;++i)
    {
        for (j=0;j<N;++j)
        {
            if (rand()%2 == 0)
                population[i][j] = 1;
            else
                population[i][j] = 0;
        }
    }
    return population;
}
