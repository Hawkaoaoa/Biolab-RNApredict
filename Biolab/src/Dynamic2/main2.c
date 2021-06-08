#include "Dynamic2.h"
#include "basepair_match.c"

void Dynamic2(FILE *fp1, FILE*fp2)
{

    char str[100];
    char seq[100][100];
    int num = 0;

    while (fgets(str, 100, fp1) != NULL){
        strcpy(seq[num], str);
        num++;
    }

	int s[100][2];

	int len, i, k;
	char tmp[100];
    start = clock();
	for (k=0;k<num;++k)
    {
        for(len=0; seq[k][len]!='\0';len++); //计算字符串B的长度

        for (i=0;i<100;++i)
            tmp[i] = '.';

        int max_pair = basepair_match(seq[k],s,len);

        for(i=0;i<max_pair;i++)
            {
                //printf("%d-%d\n",s[i][0],s[i][1]);
                tmp[s[i][0]] = '(';
                tmp[s[i][1]] = ')';
                tmp[len] = '\0';
            }
            fprintf(fp2, "%s", tmp);
            fprintf(fp2, "\n");
    }

    printf( "Success!" );
}
