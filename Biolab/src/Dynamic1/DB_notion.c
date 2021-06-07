#include "Dynamic1.h"
void DB_notion(int num_pair,struct Pair *pair,int len,char *output)
{
	FILE *fp;
	fp=fopen(output,"a+");

	int i=0,j=0;
	char *DB;
	DB = (char *)malloc(sizeof(char)*(len+1));
	for(i=0;i<len;i++){
		for(j=0;j<num_pair;j++){
			if(i==pair[j].base1){
			*(DB+i)='(';
			break;
			}
			else if(i==pair[j].base2){
			*(DB+i)=')';
			break;
			}
			else {
			*(DB+i)='.';
			}
		}
	}
	*(DB+i)='\0';
	fprintf(fp,"%s\n",DB);
	fclose(fp);
}
