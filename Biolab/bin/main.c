#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dynamic1.h"
#include "Dynamic2.h"
#include "Weight.h"

int main(int argc, char *argv[])
{
  FILE *fp1 = fopen((char *)argv[2], "rt");
  FILE *fp2 = fopen((char *)argv[3],"wt");
 
  if(argc!=4){
	printf("Wrong command line parameter!\n");
	printf("$0<INPUT><OUTPUT>\n");
	return -1;
}

 if (fp1 == NULL || fp2 == NULL){
    perror("Error while opening the file.\n");
    exit(-1);
  }

 if(strcmp((char *)argv[1],"-d1") != 0 && strcmp((char *)argv[1],"-d2") != 0\
&& strcmp((char *)argv[1],"-w") !=0){
	printf("Wrong options!\n");
	printf("The options are -d1 -d2 or -w.\n");
	return -1;
}

  if(strcmp((char *)argv[1],"-d1") == 0)
    {
      Dynamic1(fp1, fp2, argv[2], argv[3]);
    }
  if(strcmp((char *)argv[1],"-d2") == 0)
    {
      Dynamic2(fp1, fp2);
    }
  if(strcmp((char *)argv[1],"-w") == 0)
    {
      Weight(fp1, fp2);
    }
 
  fclose(fp1);
  fclose(fp2);

  return 0;
}
