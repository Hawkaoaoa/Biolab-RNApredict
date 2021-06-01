void cross(int **popu)
{
    int N = num_stem - 1;
    int i = 0, j = 0;
    int num = 0;
    int tmp;
    srand((unsigned)time(NULL));
    double flag1;
    int flag2;
    int individual_tobe_cross[2];

    for (i=0;i<NUM;++i)
    {
        flag1 = rand() % 1000 / 1000.0;
        if (flag1 < CROSS)          /* 遍历每个个体，若满足CROSS, 则会发生交叉 */
        {
            individual_tobe_cross[num] = i;
            num += 1;
        }
        if (num == 2)
        {
            flag2 = rand() % N;
            for (j=flag2;j<N;++j)   /* 随机选择一个交叉位点，这个位点之后的部分做交换 */
            {
                tmp = popu[individual_tobe_cross[0]][j];
                popu[individual_tobe_cross[0]][j] = popu[individual_tobe_cross[1]][j];
                popu[individual_tobe_cross[1]][j] = tmp;
            }
        }
    }
}
