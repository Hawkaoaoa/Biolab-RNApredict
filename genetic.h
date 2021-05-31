# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

#define CROSS 0.6   /* 交叉 */
#define MUTATE 0.05    /* 变异 */
#define NUM 30   /* 每一代的个体数 */
#define MAXITER 20  /* 计数器， 最大适应度不变的次数 （停止准则） */

typedef enum {false,true} bool;

struct mysample{
    int start;
    int end;
    int length;
}sample[1000];

int num_stem = 0;   /* 找到的长度 >1 的茎区数 */
