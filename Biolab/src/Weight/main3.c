#include "Weight.h"

int finalwtsum = 0;

void Weight(FILE *inputFile, FILE *outputFile)
{
    int i,j,n, len;
    int **wMatrix = 0, **sMatrix = 0;

#ifdef SUBSECTION
    int **optsMatrix = 0;
    int maxfinalwtsum=0;
    int w1=0, w2=0;
    int k = 0;

    clock_t start, finish;
    float duration;
    start = clock();
#endif
	char seq[10000];


	if (inputFile  == NULL)
    {
        printf("Error! opening file put_in_1.txt");
        // 文件指针返回 NULL 则退出
        exit(1);
    }

	if (outputFile == NULL)
	{
        printf("Error! opening file result_1.txt");
        // 文件指针返回 NULL 则退出
       
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
			fscanf(inputFile,"%[\n \t]", seq);
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
                if ((seq[i]=='G' && seq[j]=='U')||(seq[i]=='U' && seq[j]=='G'))
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

    finish = clock();
    duration = (float)(finish - start) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );
}
