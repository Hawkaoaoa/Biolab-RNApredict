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
        if (flag1 < MUTATE) /* ����ÿ�����壬������MUTATE, ��ᷢ��ͻ�� */
        {
            flag2 = rand() % N;
            if (popu[i][flag2] == 1)        /* 1��Ϊ0�� 0��Ϊ1 */
                popu[i][flag2] = 0;
            else
                popu[i][flag2] = 1;
        }
    }
}
