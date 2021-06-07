# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include "mpi.h"
# include <unistd.h>

#define CROSS 0.3  
#define MUTATE 0.05 
#define MAXITER 30 
int NUM = 2000; 

typedef enum {false,true} bool;

struct mysample{
    int start;
    int end;
    int length;
}sample[1000];

int num_stem = 0;  

void pool(char *seq)  
{
    int len = strlen(seq);
    int **a;
    a = (int**)malloc(sizeof(int*)*len);   
    int i = 0,j = 0;
    for (i=0;i<len;++i)
        a[i] = (int*)malloc(sizeof(int)*len);

    for (i=0;i<len-3;++i) 
    {
        for (j=i+4;j<len;++j)
        {
            if ((seq[i] == 'A' && seq[j] == 'U' || seq[i] == 'U' && seq[j] =='A') \
                || (seq[i] == 'G' && seq[j] == 'C' || seq[i] == 'C' && seq[j] =='G')\
                || (seq[i] == 'G' && seq[j] == 'U' || seq[i] == 'U' && seq[j] =='G'))
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }

    int num1 = 0, num2 = 0; 
    int k = 0; 
    bool flag; 

    for (i=0;i<len-3;++i)  
    {
        for (j=i+4;j<len;++j)
        {
            if (a[i][j] == 1)
            {
                num1=i;
                num2=j;
                k = 1;
                flag = false;
                num1++;
                num2--;

                while(a[num1][num2] == 1)
                {
                    k++;
                    flag = true;
                    num1++;
                    num2--;
                    if (num2 < num1 + 4)
                        break;
                }

                if (flag == true)
                {
                    sample[num_stem].start = i;
                    sample[num_stem].end = j;
                    sample[num_stem].length = k;
                    num_stem++;
                }
            }
        }
    }
    free(a);
}

int is_compatible(int i, int j)    
{
    if ((sample[i].start+sample[i].length<=sample[j].start && sample[i].end-sample[i].length>=sample[j].end)\
        || (sample[j].start+sample[j].length<=sample[i].start && sample[j].end-sample[j].length>=sample[i].end)\
        || sample[i].end<sample[j].start || sample[j].end<sample[i].start)
        return 1;
    else
        return 0;
}

int num_pair(int *individual)  
{
    int N = num_stem - 1;
    int i = 0;
    int num = 0;
    for (i=0;i<N;++i)
    {
        if (individual[i] == 1)
        {
            num += sample[i].length;
        }
    }

    return num;
}

int conflict(int *individual)   
{
    int i = 0, j = 0;
    int N = num_stem - 1;

    for (i=0;i<N-1;++i)
    {
        for (j=i+1;j<N;++j)
        {
            if (individual[i] == 1 && individual[j] == 1) {
                if (is_compatible(i, j))
                    continue;
                else
                    return 1;
            }
        }
    }
    return 0;
}

int max_index(int *individual)  
{
    int i = 0;
    int N = num_stem - 1;
    int tmp_max = 0;
    int index_max;
    int flag = 0;

    for (i=0;i<N;++i)
    {
        if (individual[i] == 1) {
            flag = 1;
            if (sample[i].length > tmp_max)
                index_max = i;
        }
    }
    if (flag == 0)
        return -1;
    else
        return index_max;
}

int *modify(int *individual)      
{
    int N = num_stem - 1;
    int i = 0;
    int index_max;
    int tmp_max = 0;

    int *new_individual = (int *)calloc(sizeof(int),N);

    for (i=0;i<N;++i)
        new_individual[i] = 0;

    int flag = N;

    while (flag > 0) {
        flag--;
        if (max_index(individual) == -1)
            break;
        index_max = max_index(individual);
        new_individual[index_max] = 1;
        individual[index_max] = 0;

        if (conflict(new_individual))
        {
            new_individual[index_max] = 0;
        }
        else
            continue;
    }

    return new_individual;
}

int **Init()        
{
    int N = num_stem - 1;
    int **population;
    population = (int**)malloc(sizeof(int*)*NUM);
    int i = 0,j = 0;
    for (i=0;i<NUM;++i)
        population[i] = (int*)malloc(sizeof(int)*N);

    srand((unsigned)time(NULL));
    for (i=0;i<NUM;++i)
    {
        for (j=0;j<N;++j)
        {
            if (rand()%2 == 0)
                population[i][j] = 1;
            else
                population[i][j] = 0;
        }
    }
    return population;
}

int **Select(int *fit_score, int **old_popu)
{
    int i = 0, sum = 0;
    int N = num_stem - 1;

    for (i;i<NUM;++i)
    {
        sum += fit_score[i];     
    }

    float portion[NUM];    

    for (i=0;i<NUM;++i)
    {
        portion[i] = (float)fit_score[i] / (float)sum;
    }

    float boundary[NUM];        
    float bound = 0;

    for (i=0;i<NUM;++i)
    {
        bound += portion[i];
        boundary[i] = bound;
    }

    srand((unsigned)time(NULL));

    int **new_popu;
    new_popu = (int**)malloc(sizeof(int*)*NUM);

    for (i=0;i<NUM;++i)
        new_popu[i] = (int*)malloc(sizeof(int)*N); 

    int k = 0;
    int j = 0;

    for (i=0;i<NUM;++i)
    {
        float num = rand() % 1000 / 1000.0;
        if (num <= boundary[0])    
        {
            new_popu[k] = old_popu[0];
            k++;
        }
        if (num >= boundary[NUM-2])
        {
            new_popu[k] = old_popu[NUM-1];
            k++;
        }
        for (j=0;j<NUM-1;++j)
        {
            if (num >= boundary[j] && num <= boundary[j+1]) 
            {
                new_popu[k] = old_popu[j+1];
                k++;
            }
        }
    }

    return new_popu;
}

void cross(int **popu)
{
    int N = num_stem - 1;
    int i = 0, j = 0;
    int num = 0;
    int tmp;
    srand((unsigned)time(NULL));
    double flag1;
    int flag2;
    int individual_tobe_cross[2];

    for (i=0;i<NUM;++i)
    {
        flag1 = rand() % 1000 / 1000.0;
        if (flag1 < CROSS)         
        {
            individual_tobe_cross[num] = i;
            num += 1;
        }
        if (num == 2)
        {
            flag2 = rand() % N;
            for (j=flag2;j<N;++j)   
            {
                tmp = popu[individual_tobe_cross[0]][j];
                popu[individual_tobe_cross[0]][j] = popu[individual_tobe_cross[1]][j];
                popu[individual_tobe_cross[1]][j] = tmp;
            }
        }
    }
}

void mutate(int **popu)
{
    int N = num_stem - 1;
    int i = 0;
    srand((unsigned)time(NULL));
    double flag1;
    int flag2;

    for (i=0;i<NUM;++i)
    {
        flag1 = rand() % 1000 / 1000.0;
        if (flag1 < MUTATE) 
        {
            flag2 = rand() % N;
            if (popu[i][flag2] == 1)        
                popu[i][flag2] = 0;
            else
                popu[i][flag2] = 1;
        }
    }
}

int most_fit(int **popu)        
{
    int i = 0;
    int max_fit = 0;
    int score = 0;

    for (i=0;i<NUM;++i)
    {
        score = num_pair(popu[i]);
        if (score > max_fit)
            max_fit = score;
    }
    return max_fit;
}

int main(int argc, char *argv[])
{
    FILE *fp1 = fopen("input.txt","r");
    
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

    int **get_init = Init();

    for (i = 0; i < NUM; ++i)
        get_init[i] = modify(get_init[i]);

    for (i = 0; i < NUM; ++i)
    {
        fit_score[i] = num_pair(get_init[i]);
    }

    int pre_max_fit = 0;        
    int now_max_fit = 0;
    int num_iter = MAXITER;

    while (num_iter > 0) {             
        new_popu = Select(fit_score, get_init);
        cross(new_popu);
        mutate(new_popu);

        for (i=0; i < NUM; ++i)
            new_popu[i] = modify(new_popu[i]);

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

