# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include "mpi.h"
# include <unistd.h>

#define CROSS 0.4   /* 交叉 */
#define MUTATE 0.2  /* 变异 */
#define MAXITER 100 /* 计数器， 最大适应度不变的次数 （停止准则） */
int NUM = 2000; /* 每一代的个体数, 在主程序中会被划分，交给每个子进程处理！ */

typedef enum {false,true} bool;

struct mysample{
    int start;
    int end;
    int length;
}sample[1000];

int num_stem = 0;   /* 找到的长度 >1 的茎区数 */
