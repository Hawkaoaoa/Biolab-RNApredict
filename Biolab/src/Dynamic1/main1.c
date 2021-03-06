
#include "Base_Tran_Num.c"

void Dynamic1(FILE *fp1, FILE *fp2, char *input, char *output){
	char *seq;
	int *numseq,res_num,seqnum;
	//numseq is used to transfer base to num
	//seqnum stores the number of sequences in the input file
	//seq=(char *)malloc(sizeof(char)*MAX_SEQLEN);
	int len,i,f=0;

	seqnum=seq_num(input);

	while(f<seqnum){
		f++;
		seq=(char *)malloc(sizeof(char)*MAX_SEQLEN);
		fgets(seq,MAX_SEQLEN,fp1);

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
	DB_notion(res_num,pair,len,output);

	free(pair);
	free(numseq);
	free(seq);
}
    printf("Success!");
}
