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
