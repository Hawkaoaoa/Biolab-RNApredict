#include "Genetic.h"
int is_compatible(int i, int j)     /* 相容性检测 返回值为1则为相容*/
{
    if ((sample[i].start+sample[i].length<=sample[j].start && sample[i].end-sample[i].length>=sample[j].end)\
        || (sample[j].start+sample[j].length<=sample[i].start && sample[j].end-sample[j].length>=sample[i].end)\
        || sample[i].end<sample[j].start || sample[j].end<sample[i].start)
        return 1;
    else
        return 0;
}
