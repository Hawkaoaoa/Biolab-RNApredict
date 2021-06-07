#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MINFOLDSPAN 4
#define MINSTEMLEN 2

#define GC 12
#define AU 7
#define GU 3

#define OUTSIDEGU
#define SUBSECTION

#define FALSE 0
#define TRUE 1


void WeightMatch(int p, int q, int **ptwMatrix, int **ptsMatrix,int len);
void OutputResuit(int **ptsMatrix, int seqlen,FILE *outputFile);
