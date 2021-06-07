#include "Weight.h"


void OutputResuit(int **ptsMatrix, int seqlen,FILE *outputFile)
{
	int i,j;
    int *str;//[seqlen];

	str = (int*)malloc(sizeof(int)*seqlen);
	memset(str, 0, sizeof(int)*seqlen);

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

		}
        else if(str[i]==2)
		{
			fprintf(outputFile, ")");
		}
        else
		{
			fprintf(outputFile, ".");
		}
    }
 
	fprintf(outputFile, "\n");
	//printf("\n");
	free(str);
	str=0;
}
