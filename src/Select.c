int **Select(int *fit_score, int **old_popu)
{
    int i = 0, sum = 0;
    int N = num_stem - 1;

    for (i;i<NUM;++i)
    {
        sum += fit_score[i];        /* ���и����ܵ÷� */
    }

    float portion[NUM];     /* �������� */

    for (i=0;i<NUM;++i)
    {
        portion[i] = (float)fit_score[i] / (float)sum;
    }

    float boundary[NUM];        /* �������̣� �˴�����ÿ�����������߽磬��Ϊѡ���׼ */
    float bound = 0;

    for (i=0;i<NUM;++i)
    {
        bound += portion[i];
        boundary[i] = bound;
    }

    srand((unsigned)time(NULL));

    int **new_popu;
    new_popu = (int**)malloc(sizeof(int*)*NUM);

    for (i=0;i<NUM;++i)
        new_popu[i] = (int*)malloc(sizeof(int)*N);  /* ѡ�����������Ⱥ */

    int k = 0;
    int j = 0;

    for (i=0;i<NUM;++i)
    {
        float num = rand() % 1000 / 1000.0;
        if (num <= boundary[0])     /* ͷβ���ּ������ ��С�� �п��ܻ������������⴦�� */
        {
            new_popu[k] = old_popu[0];
            k++;
        }
        if (num >= boundary[NUM-2])
        {
            new_popu[k] = old_popu[NUM-1];
            k++;
        }
        for (j=0;j<NUM-1;++j)
        {
            if (num >= boundary[j] && num <= boundary[j+1]) /* ���ݸ��ʴ��ڵĲ�ͬ�����䣬ѡ���Ӧ�ĸ����Ŵ�����һ�� */
            {
                new_popu[k] = old_popu[j+1];
                k++;
            }
        }
    }

    return new_popu;
}
