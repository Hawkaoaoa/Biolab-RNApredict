void create_T()    /* 创造表示 si,sj 茎区是否相容的T矩阵 */
{
    int N = num_stem - 1;
    int **T;
    T = (int**)malloc(sizeof(int*)*N);  /* 创建 T 矩阵 */
    int i = 0,j = 0;
    for (i=0;i<N;++i)
        T[i] = (int*)malloc(sizeof(int)*N);

    for (i=0;i<N;++i)
    {
        for (j=0;j<N;++j)
        {
            if (is_compatible(i,j))
                T[i][j] = 1;
            else
                T[i][j] = 0;
            if (i == j)
                T[i][j] = 0;
        }
    }
}
