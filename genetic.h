# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

#define CROSS 0.6   /* ���� */
#define MUTATE 0.05    /* ���� */
#define NUM 30   /* ÿһ���ĸ����� */
#define MAXITER 20  /* �������� �����Ӧ�Ȳ���Ĵ��� ��ֹͣ׼�� */

typedef enum {false,true} bool;

struct mysample{
    int start;
    int end;
    int length;
}sample[1000];

int num_stem = 0;   /* �ҵ��ĳ��� >1 �ľ����� */
