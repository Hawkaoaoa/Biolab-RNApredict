void create_T()    /* �����ʾ si,sj �����Ƿ����ݵ�T���� */
{
    int N = num_stem - 1;
    int **T;
    T = (int**)malloc(sizeof(int*)*N);  /* ���� T ���� */
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
