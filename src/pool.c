void pool(char *seq)          /* 构建茎区池 */
{
    int len = strlen(seq);
    int **a;
    a = (int**)malloc(sizeof(int*)*len);  /* 找茎区全集的矩阵 a */
    int i = 0,j = 0;
    for (i=0;i<len;++i)
        a[i] = (int*)malloc(sizeof(int)*len);

    for (i=0;i<len-3;++i)    /* 能配对的填为1 */
    {
        for (j=i+4;j<len;++j)
        {
            if ((seq[i] == 'A' && seq[j] == 'U' || seq[i] == 'U' && seq[j] =='A') \
                || (seq[i] == 'G' && seq[j] == 'C' || seq[i] == 'C' && seq[j] =='G')\
                || (seq[i] == 'G' && seq[j] == 'U' || seq[i] == 'U' && seq[j] =='G'))
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }

    int num1 = 0, num2 = 0;   /* 开始搜索连续茎区的起始点、终止点 */
    int k = 0;   /* 记录茎区的长度 */
    bool flag;    /* 是否找到了 长度＞1 的茎区 */

    for (i=0;i<len-3;++i)                 /* 上三角矩阵 */
    {
        for (j=i+4;j<len;++j)
        {
            if (a[i][j] == 1)
            {
                num1=i;
                num2=j;
                k = 1;
                flag = false;
                num1++;
                num2--;

                while(a[num1][num2] == 1)
                {
                    k++;
                    flag = true;
                    num1++;
                    num2--;
                    if (num2 < num1 + 4)
                        break;
                }

                if (flag == true)
                {
                    sample[num_stem].start = i;
                    sample[num_stem].end = j;
                    sample[num_stem].length = k;
                    num_stem++;
                }
            }
        }
    }
    free(a);
}
