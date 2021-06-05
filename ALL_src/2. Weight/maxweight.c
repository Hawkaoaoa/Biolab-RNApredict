#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
//#include<cstdlib>

//#include<iostream>
//#include <sstream>
//#include<iomanip>
//#include <fstream>
//using namespace std;

// #define MINFOLDSPAN	4
// #define MINSTEMLEN	3

#define MINFOLDSPAN 4
#define MINSTEMLEN 3

#define GC 11
#define AU 8
#define GU 3

#define OUTSIDEGU
#define SUBSECTION

#define FALSE 0
#define TRUE 1


void WeightMatch(int p, int q, int **ptwMatrix, int **ptsMatrix,int len);
void OutputResuit(int **ptsMatrix, int seqlen,FILE *outputFile);

int finalwtsum = 0;
int main()
{
    int i,j,n, len;
    int **wMatrix = 0, **sMatrix = 0;
	FILE *inputFile, *outputFile;
#ifdef SUBSECTION
    int **optsMatrix = 0;
    int maxfinalwtsum=0;
    int w1=0, w2=0;
    int k = 0;
#endif
	char seq[4096];


	if ((inputFile = fopen("put_in_1.txt", "r")) == NULL)
    {
        printf("Error! opening file put_in_1.txt");
        // 文件指针返回 NULL 则退出
        exit(1);
    }

	if ((outputFile = fopen("result_1.txt", "w")) == NULL)
	{
        printf("Error! opening file result_1.txt");
        // 文件指针返回 NULL 则退出
		fclose(inputFile);
        exit(1);
    }

	while(TRUE)
    {
		//const char *seq = "GGGGCTATGGCGCAGGCTGGTAGCGCGTCTCGTTCGCAATGAGAAGGTCAGGGGTTCGAATCCCCTTAGCTCCA";
		int readResult = fscanf(inputFile,"%[^\n]", seq);
		if(EOF == readResult)
		{
			break;
		}
		if(readResult == 0)
		{
			fscanf(inputFile,"%[\r\n \t]", seq);
			continue;
		}

        n=strlen(seq);

		if(n < 3)
			continue;

        len=n;
		//----------------------------------------------------------------------------
		//initialization
        wMatrix = (int**)malloc(sizeof(int*) * n);
        sMatrix = (int**)malloc(sizeof(int*) * n);
#ifdef SUBSECTION
        optsMatrix = (int**)malloc(sizeof(int*) * n);
#endif
        for (i=0; i<n; i++)
        {
            wMatrix[i] = (int*)malloc(sizeof(int) * n);
            sMatrix[i] = (int*)malloc(sizeof(int) * n);
#ifdef SUBSECTION
			optsMatrix[i] = (int*)malloc(sizeof(int) * n);
#endif
        }

        for (i=0; i<n; i++)
		{
            for(j=0;j<n;j++)
			{
				wMatrix[i][j] = 0;
				sMatrix[i][j] = 0;
#ifdef SUBSECTION
                optsMatrix[i][j] = 0;
#endif
			}
		}
		//----------------------------------------------------------------------------
        //evaluate weight matrix
        for (i=0; i<n; i++)
        {
            for(j=i+MINFOLDSPAN; j<n; j++)
            {
                if ((seq[i]=='G' && seq[j]=='C')||(seq[i]=='C' && seq[j]=='G'))
					wMatrix[i][j] = GC;
                if ((seq[i]=='A' && seq[j]=='U')||(seq[i]=='U' && seq[j]=='A'))
					wMatrix[i][j] = AU;
                if ((seq[i]=='G' && seq[j]=='U') || (seq[i]=='U' && seq[j]=='G'))
					wMatrix[i][j] = GU;
            }
        }
		//----------------------------------------------------------------------------
        //search and select weight matrix
		//printf("\nBeing searching the maximal weighted matching relation.Please wait...\n");
        WeightMatch(0, n-1, wMatrix, sMatrix,len);
#ifdef SUBSECTION
        maxfinalwtsum = finalwtsum;
        finalwtsum = 0;
		for (i=0; i<n; i++)
		{
			for(j=0;j<n;j++)
			{
				optsMatrix[i][j] = sMatrix[i][j];
				sMatrix[i][j] = 0;
			}
		}
		for(i=0; i<n-1; i++)
		{
			WeightMatch(0, i, wMatrix, sMatrix,len);
			w1 = finalwtsum;
			finalwtsum = 0;
			WeightMatch(i+1, n-1, wMatrix, sMatrix,len);
			w2 = finalwtsum;
			finalwtsum = 0;
            if (maxfinalwtsum < w1+w2)
            {
                maxfinalwtsum = w1+w2;
                for(j=0; j<n;j++)
                    for (k=0; k<n; k++)
                        optsMatrix[j][k] = sMatrix[j][k];
            }
            for(j=0;j<n;j++)
			{
                for (k=0; k<n; k++)
					sMatrix[j][k] = 0;
			}
		}
#endif
        //printf("Search completed!\n");
		//----------------------------------------------------------------------------
        //test result
        // cout<<"wMatrix"<<endl;
        // for(i=0;i<n;i++){
        //     for(j=0;j<n;j++){
        //         cout<<wMatrix[i][j]<<" ";
        //     }cout<<endl;
        // }

#ifdef SUBSECTION
		//printf("Have SUBSECTION\n");
        OutputResuit(optsMatrix, n, outputFile);

#else
        OutputResult(sMatrix, n);
		printf("No SUBSECTION\n");
#endif

		//-----------------------------------------------------------------------------
		//free

        for (i=0; i<n; i++)
        {
            free(wMatrix[i]);
            free(sMatrix[i]);
#ifdef SUBSECTION
			free(optsMatrix[i]);
#endif
        }

		free(wMatrix);
        free(sMatrix);
#ifdef SUBSECTION
        free(optsMatrix);
#endif
    }

	fclose(inputFile);
	fclose(outputFile);

	system("pause");
}


void WeightMatch(int p, int q, int **ptwMatrix, int **ptsMatrix,int len)
{
    int i, j, k, x;
    int begin=p,end=q;
    int ms, me, mk, rs, re, rk, bd;
    int flag, sign;
    int maxweightsum, medweightsum;

    if (p + MINFOLDSPAN > q)
        return;

    maxweightsum = 0;
    flag = FALSE;

    for (i = p; i + 2 * (MINSTEMLEN - 1) + MINFOLDSPAN <= q; i++) {
        for (j = i + 2 * (MINSTEMLEN - 1) + MINFOLDSPAN; j <= q; j++) {
#ifdef OUTSIDEGU
            if (ptwMatrix[i][j] == 0)
                continue;
#else
            if(ptwMatrix[i][j]== 0 || ptwMatrix[i][j]==GU)
                continue;
#endif

            for (k = 0, medweightsum = 0; i + k + MINFOLDSPAN <= j - k && ptwMatrix[i + k][j - k] > 0; k++) {
                medweightsum += ptwMatrix[i + k][j - k];
            }
            while (k > 0 && ptwMatrix[i + k - 1][j - k + 1] == GU) {
                medweightsum -= GU;
                k--;
            }

            if (k >= MINSTEMLEN && maxweightsum < medweightsum /*+ (GC + AU + GU) * sqrt(k) / 3*/) {
                maxweightsum = medweightsum /*+ (GC + AU + GU) * sqrt(k) / 3*/;
                ms = i;
                me = j;
                mk = k;
                flag = TRUE;
            }
        }
    }
    if (flag) {
    	//printf("%d\t%d\t%d\t",ms,me,mk);
        for (i = 0; i < mk; i++)
            ptsMatrix[ms + i][me - i] = 1;
        finalwtsum += maxweightsum;

        WeightMatch(p, ms - 1, ptwMatrix, ptsMatrix,len);
        WeightMatch(ms + mk, me - mk, ptwMatrix, ptsMatrix,len);
        WeightMatch(me + 1, q, ptwMatrix, ptsMatrix,len);

        maxweightsum = 0;
        sign = FALSE;
        for (i = p; i <= ms - 1; i++) {
            for (x = p; x <= q && ptsMatrix[i][x] == 0 && ptsMatrix[x][i] == 0; x++);
            if (x <= q)
                continue;

            for (j = q; j >= me + 1; j--) {
#ifdef OUTSIDEGU
                if (ptwMatrix[i][j] == 0)
                    continue;
#else
                if (ptwMatrix[i][j]==O || ptwMatrix[i][j]==GU)
                    continue;
#endif
                k = 0;
                medweightsum = 0;
                bd = ms - i < j - me ? ms - i : j - me;
                while (k < bd && ptwMatrix[i + k][j - k] > 0) {
                    for (x = p; x <= q && ptsMatrix[i + k][x] == 0 && ptsMatrix[x][i + k] == 0; x++);
                    if (x <= q)
                        break;
                    for (x = p; x <= q && ptsMatrix[x][j - k] == 0 && ptsMatrix[j - k][x] == 0; x++);
                    if (x <= q)
                        break;
                    medweightsum += ptwMatrix[i + k][j - k];
                    k++;
                }
                while (k > 0 && ptwMatrix[i + k - 1][j - k + 1] == GU) {
                    medweightsum -= GU;
                    k--;

                    if (k >= MINSTEMLEN && maxweightsum < medweightsum /*+ (GC + AU + GU) * sqrt(k) / 3*/) {
                        maxweightsum = medweightsum /*+ (GC + AU + GU) * sqrt(k) / 3*/;
                        rs = i;
                        re = j;
                        rk = k;
                        sign = TRUE;
                    }
                }
                if (sign) {
                	//printf("%d\t%d\t%d\t",rs,re,rk);
                    for (i = 0; i < rk; i++)
                        ptsMatrix[rs + i][re - i] = 1;
                    finalwtsum += maxweightsum;

                }
            }
        }
    }
    // cout<<"ptsMatrix"<<endl;
    // for(i=0;i<len;i++){
    //     for(j=0;j<len;j++){
    //         cout<<ptsMatrix[i][j]<<" ";
    //     }cout<<endl;
    // }
}


//----------------------------------------------------------------------------
void OutputResuit(int **ptsMatrix, int seqlen,FILE *outputFile)
{
	int i,j;
    int *str;//[seqlen];

	str = (int*)malloc(sizeof(int)*seqlen);
	memset(str, 0, sizeof(int)*seqlen);
	// cout<<"OutputResuit"<<endl;
    // for(i=0; i<seqlen; i++){
	// 	for(j=0; j<seqlen; j++){
	// 		cout<<ptsMatrix[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	for(i=0; i<seqlen; i++){
        int flag=FALSE;
        for (j=0; j<seqlen; j++)
        {
            if(ptsMatrix[i][j] == 1)
            {
                flag=1;
                str[i]=1;
                str[j]=2;
            }
        }
    }

    for(i=0;i<seqlen; i++){
        if(str[i]==1)
		{
			fprintf(outputFile, "(");
			printf("(");
		}
        else if(str[i]==2)
		{
			fprintf(outputFile, ")");
			printf(")");
		}
        else
		{
			fprintf(outputFile, ".");
			printf(".");
		}
    }
    printf("\n");
	fprintf(outputFile, "\r\n");
	//printf("\n");
	free(str);
	str=0;
}
