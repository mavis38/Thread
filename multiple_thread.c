#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Terminal: man pthread_create
//SYNOPSIS
       //#include <pthread.h>

       //int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
       //                   void *(*start_routine) (void *), void *arg);

       //Compile and link with -pthread.

void* run_sum(void* arg);
void* run_sub(void* arg);
void* run_mult(void* arg);

struct sum_struct
{
    long long limit;long long answer;
};

struct sub_struct
{
    long long limit;long long answer;
};

struct mult_struct
{
    long long limit;long long answer;
};

int main(int argc, char **argv)
{
    int arg_num = argc-1;

    pthread_t THREAD_ID_1[arg_num];
    pthread_t THREAD_ID_2[arg_num];
    pthread_t THREAD_ID_3[arg_num];
    
    struct sum_struct limit_1[arg_num];
    struct sub_struct limit2[arg_num];
    struct mult_struct limit3[arg_num];

    for (int i = 0; i < arg_num; i++)
    {
        limit_1[i].limit = atoll(argv[1+i]);
        limit2[i].limit = atoll(argv[1+i]);
        limit3[i].limit = atoll(argv[1+i]);

        pthread_attr_t THREAD_ATTRIBUTE;
        pthread_attr_init(&THREAD_ATTRIBUTE);
        pthread_create(&THREAD_ID_1[i], &THREAD_ATTRIBUTE, run_sum, &limit_1[i]);
        pthread_create(&THREAD_ID_2[i], &THREAD_ATTRIBUTE, run_sub, &limit2[i]);
        pthread_create(&THREAD_ID_3[i], &THREAD_ATTRIBUTE, run_mult, &limit3[i]);
    }

    void *exit_status;

    //Outros processos;
    printf("Programa simples usando multiplas Threads.\n");
    printf("Aluno de Eng. de Controle e Automacao\n");
    printf("Universidade Federal de Ouro Preto, Novembro de 2019\n\n");

    for (int i = 0; i < arg_num; i++)
    {
        pthread_join(THREAD_ID_1[i], &exit_status);
        pthread_join(THREAD_ID_2[i], &exit_status);
        pthread_join(THREAD_ID_3[i], &exit_status);

        printf("Soma: %lld\n", limit_1[i].answer);
        printf("Subtracao: %lld\n", limit2[i].answer);
        printf("Multiplicacao: %lld\n", limit3[i].answer);
        printf("\n\n");
    }
}

void* run_sum(void* arg)
{
    struct sum_struct *struct_answer = (struct sum_struct*)arg;

    long long sum = 0;

    for (long long i = 0; i <= (struct_answer->limit); i++) sum+=i;

    struct_answer->answer = sum;

    pthread_exit(0);
}

void* run_sub(void* arg)
{
    struct sub_struct *struct_answer = (struct sub_struct*)arg;

    long long sub = 0;

    for (long long i = 0; i <= (struct_answer->limit); i++) sub-=i;

    struct_answer->answer = sub;

    pthread_exit(0);
}

void* run_mult(void* arg)
{
    struct mult_struct *struct_answer = (struct mult_struct*)arg;

    long long mult = 1;
    int count = 1;

    for (long long i = 0; i <= (struct_answer->limit); i++) 
    {
        mult = mult*count;
        count++;
    }

    struct_answer->answer = mult;

    pthread_exit(0);
}
