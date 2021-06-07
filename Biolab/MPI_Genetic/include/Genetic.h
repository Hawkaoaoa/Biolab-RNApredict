# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include "mpi.h"
# include <unistd.h>

#define CROSS 0.3
#define MUTATE 0.05
#define MAXITER 30

typedef enum {false,true} bool;

struct mysample{
    int start;
    int end;
    int length;
}sample[1000];
