#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MIN_HARPIN_SIZE 3 
#define MAX_SEQLEN 1000

struct Pair{
	int base1;
	int base2;
}; 

int seq_num(char *input)
{
	int seqnum=0;
	char *seq;
	seq=(char *)malloc(sizeof(char)*MAX_SEQLEN);
	FILE *fp;
	fp=fopen(input,"r");
	if(fp==NULL){
		printf("Wrong input file!\n");
		return -1;
	}
	while(fgets(seq,MAX_SEQLEN,fp)){
		seqnum++;
	}
	return seqnum;
}

void usage()
{
	printf("$0<input file><output file>\n");
}

int max(int a,int b)
{
	return (a>b)?a:b;
}

int min(int a,int b)
{
	return (a<b)?a:b;
}

int Base_Tran_Num(char base)
{
	if(base=='A') return 0;
	else if(base=='G') return 1;
	else if(base=='C') return 2;
	else if(base=='U') return 3;
	else if(base=='T') return 3;
	else return -1;
}

int Pair(int a,int b)
{
	if(a+b==3) return 1;
	else return 0;
}

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

void DB_notion(int num_pair,struct Pair *pair,int len)
{
	int i=0,j=0,k=num_pair-1;
	char *DB;
	DB = (char *)malloc(sizeof(char)*len);
	for(i=0;i<len;i++){
		for(j=0;j<num_pair;j++){
			if(i==pair[j].base1){
			*(DB+i)='<';
			break;
			}
			else if(i==pair[j].base2){
			*(DB+i)='>';
			break;	
			}
			else *(DB+i)='.';
		}
	}
	*(DB+i)='\0';
	
		printf("%s\n",DB);
		free(DB);
}

int main(){
	char *seq;
	int *numseq,res_num;
	seq=(char *)malloc(sizeof(char)*MAX_SEQLEN);
	int len,i;
	
	strcpy(seq,"GGGGCTATGGCGCAGGCTGGTAGCGCGTCTCGTTCGCAATGAGAAGGTCAGGGGTTCGAATCCCCTTAGCTCCA");
	//change base to num
	len=strlen(seq);
	if(seq[len-1]=='\n') len--;
	numseq=(int *)malloc(sizeof(int)*len);
	for(i=0;i<len;i++){
		numseq[i]=Base_Tran_Num(seq[i]);
	}
	
	//execute Nussinov
	struct Pair *pair;
	pair=(struct Pair*)malloc(sizeof(struct Pair)*len/2);
	res_num=Nussinov(numseq,len,pair);
	
	printf("%d\n",res_num);
	for(i=0;i<res_num;i++){
		printf("%d %d\n",pair[i].base1,pair[i].base2);
	}
	//printf DB_notion
	DB_notion(res_num,pair,len);
	
	free(pair);
	free(seq);
	free(numseq);
	
	return 0;
}
