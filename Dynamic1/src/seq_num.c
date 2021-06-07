#include "Dynamic1.h"
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
