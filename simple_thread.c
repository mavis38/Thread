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
void* run_div(void* arg);

long long sum = 0;
long long sub = 0;
long long mult = 1;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Utilizacao: %s <num>\n", argv[0]);
        exit(-1);
    }
    long long limit = atoll(argv[1]);

    pthread_t THREAD_ID_1;
    pthread_t THREAD_ID_2;
    pthread_t THREAD_ID_3;

    void *exit_status;

    pthread_attr_t THREAD_ATTRIBUTE;
    pthread_attr_init(&THREAD_ATTRIBUTE);

    pthread_create(&THREAD_ID_1, &THREAD_ATTRIBUTE, run_sum, &limit);
    pthread_create(&THREAD_ID_2, &THREAD_ATTRIBUTE, run_sub, &limit);
    pthread_create(&THREAD_ID_3, &THREAD_ATTRIBUTE, run_mult, &limit);

    //Outros processos;
    printf("Programa simples usando Threads.\n");
    printf("Aluno de Eng. de Controle e Automacao\n");
    printf("Universidade Federal de Ouro Preto, Novembro de 2019\n\n");

    pthread_join(THREAD_ID_1, &exit_status);
    pthread_join(THREAD_ID_2, &exit_status);
    pthread_join(THREAD_ID_3, &exit_status);

    printf("Soma: %lld\n", sum);
    printf("Subtracao: %lld\n", sub);
    printf("Multiplicacao: %lld\n", mult);
}

void* run_sum(void* arg)
{
    long long *ptr_limit = (long long*)arg;
    long long limit = *ptr_limit;

    for (long long i = 0; i <= limit; i++) sum+=i;

    pthread_exit(0);
}

void* run_sub(void* arg)
{
    long long *ptr_limit = (long long*)arg;
    long long limit = *ptr_limit;

    for (long long i = 0; i <= limit; i++) sub-=i;

    pthread_exit(0);
}

void* run_mult(void* arg)
{
    long long *ptr_limit = (long long*)arg;
    long long limit = *ptr_limit;

    for (long long i = 1; i <= limit; i++) mult = mult*i;

    pthread_exit(0);
}
