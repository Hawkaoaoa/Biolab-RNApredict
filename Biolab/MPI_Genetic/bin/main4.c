#include "Genetic.h"

int num_stem = 0;
int NUM = 2000;

int main(int argc, char *argv[])
{
    FILE *fp1 = fopen(argv[1],"r");

    char seq[100];
    fgets(seq, 100, fp1);
    fclose(fp1);

    int len = strlen(seq);
    int i, j;
    int myrank, nprocs;
    int p, k;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    NUM = NUM / nprocs;

    sleep(myrank);

    char tmp[len];

    pool(seq);

    int N = num_stem - 1;
    int fit_score[NUM];
    int **new_popu;
    new_popu = (int **)malloc(sizeof(int *) *NUM);
    for (i=0;i<NUM;++i)
        new_popu[i] = (int *)malloc(sizeof(int)*N);

    int **get_init = (int **)Init();

    for (i = 0; i < NUM; ++i)
        get_init[i] = (int *)modify(get_init[i]);

    for (i = 0; i < NUM; ++i)
    {
        fit_score[i] = num_pair(get_init[i]);
    }

    int pre_max_fit = 0;
    int now_max_fit = 0;
    int num_iter = MAXITER;

    while (num_iter > 0) {
        new_popu = (int **)Select(fit_score, get_init);
        cross(new_popu);
        mutate(new_popu);

        for (i=0; i < NUM; ++i)
            new_popu[i] = (int *)modify(new_popu[i]);

        for (i=0; i < NUM; ++i)
            fit_score[i] = num_pair(new_popu[i]);

        now_max_fit = most_fit(new_popu);
        if (now_max_fit > pre_max_fit) {
            pre_max_fit = now_max_fit;
            num_iter = MAXITER;
        } else
            num_iter--;

        get_init = new_popu;
    }

    int tmp1 = most_fit(get_init);
    int tmp2[NUM];
    int tmp3 = 0;

    for (i = 0; i < NUM; ++i) {
        if (num_pair(get_init[i]) == tmp1) {
            tmp2[tmp3] = i;
            tmp3 += 1;
        }
    }

    char result[tmp3][len];
    int k1, k2;
    for (i = 0; i < tmp3; ++i) {
        for (j = 0; j < len; ++j)
            result[i][j] = '.';
    }

    for (i = 0; i < tmp3; ++i) {
        for (j = 0; j < N; ++j) {
            if (get_init[tmp2[i]][j] == 1) {
                for (k1 = 0; k1 < sample[j].length; ++k1) {
                    result[i][sample[j].start + k1] = '(';
                }
                for (k2 = 0; k2 < sample[j].length; ++k2) {
                    result[i][sample[j].end - k2] = ')';
                }
            }
        }
    }

    if (myrank != 0)
    {
        MPI_Send(&tmp3, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        for (i=0;i<tmp3;++i)
        {
            MPI_Send(result[i], len, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
    }

    if (myrank == 0)
    {
        for (p=1;p<nprocs;++p)
        {
            MPI_Recv(&k, 1, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (i=0;i<k;++i)
            {
                MPI_Recv(tmp, len, MPI_CHAR, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (j=0;j<len;++j)
                    printf("%c",tmp[j]);
                printf("\n");
            }
        }
    }

    MPI_Finalize();

    return 0;
}

