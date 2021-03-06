#include "Dynamic1.h"
int Nussinov(int *num_seq,int len,struct Pair *pair_res)
{
	int **MMS,**P,i,j,k,new=0,max=0,pair_num=0;
	int size=len+1;
	struct Pair *pair1,*pair;
	pair1=(struct Pair *)malloc(len/2*sizeof(struct Pair));
	pair=pair1;
	*pair=(struct Pair){1,len};

	//allocate matrix
	MMS=(int **)malloc(sizeof(int *)*size);
	for(i=0;i<size;i++){
		MMS[i]=(int *)malloc(sizeof(int)*size);
	}
	P=(int **)malloc(sizeof(int *)*size);
	for(i=0;i<size;i++){
		P[i]=(int *)malloc(sizeof(int)*size);
	}

	//Initialize
	for(i=1;i<size;i++){
		MMS[i][i-1]=0;
		MMS[i][i]=0;
		P[i][i]=-1;
	}

	for(j=2;j<size;j++){
		for(i=j-1;i>=1;i--){
			max=MMS[i][j-1];
			P[i][j]=-1;
			for(k=i;k<j-MIN_HARPIN_SIZE;k++){
				if(Pair(num_seq[k-1],num_seq[j-1])){
					new=1+MMS[i][k-1]+MMS[k+1][j-1];
					if(max<new){
						max=new;
						P[i][j]=k;
					}
				}
			}
			MMS[i][j]=max;
		}
	}
	/*for(i=0;i<size;i++){
		printf("\n");
		for(j=0;j<size;j++)
		{
			printf("%d\t",P[i][j]);
		}
	}*/
	while(pair-pair1!=-1){
		i=pair->base1;
		j=pair->base2;
		pair--;
		k=P[i][j];
		if(k==-1){
			if(i<j){
				pair++;
				*(pair)=(struct Pair){i,j-1};
			}
		}
		else {
			pair_res[pair_num++]=(struct Pair){k-1,j-1};
			if(i<k) *(++pair)=(struct Pair){i,k-1};
			if(j-k>2) *(++pair)=(struct Pair){k+1,j-1};
		}
	}
	free(pair1);
	free(MMS);
	free(P);

	return pair_num;
 }
