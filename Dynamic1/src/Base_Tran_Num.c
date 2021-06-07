#include "Dynamic1.h"
int Base_Tran_Num(char base)
{
	if(base=='A') return 0;
	else if(base=='G') return 1;
	else if(base=='C') return 2;
	else if(base=='U') return 3;
	else if(base=='T') return 3;
	else return -1;
}
