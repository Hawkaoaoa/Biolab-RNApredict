# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include "mpi.h"
# include <unistd.h>

#define CROSS 0.4   /* ���� */
#define MUTATE 0.2  /* ���� */
#define MAXITER 100 /* �������� �����Ӧ�Ȳ���Ĵ��� ��ֹͣ׼�� */
int NUM = 2000; /* ÿһ���ĸ�����, ���������лᱻ���֣�����ÿ���ӽ��̴��� */

typedef enum {false,true} bool;

struct mysample{
    int start;
    int end;
    int length;
}sample[1000];

int num_stem = 0;   /* �ҵ��ĳ��� >1 �ľ����� */
