/* File:
 *    pth_busy_bar.c
 *
 * Purpose:
 *    Use busy wait barriers to synchronize threads.
 *
 * Input:
 *    none
 * Output:
 *    Time for BARRIER_COUNT barriers
 *
 * Compile:
 *    gcc -g -Wall -o pth_busy_bar pth_busy_bar.c -lpthread
 * Usage:
 *    ./pth_busy_bar <thread_count>
 *
 * Note:
 *    Compile flag DEBUG will print a message after each barrier
 *
 * IPP:   Section 4.8.1 (p. 177)
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

#define BARRIER_COUNT 100

int thread_count;
int barrier_thread_counts[BARRIER_COUNT];

// Las exclusiones mutuas se utilizan para proteger los datos u otros recursos del acceso simultáneo.
//sera inicializado en pthread_mutex_init(&mutex, NULL); y elimniado con pthread_mutex_destroy(&barrier_mutex)
pthread_mutex_t barrier_mutex; //El ID de mutex

void Usage(char *prog_name);
void *Thread_work(void *rank);

/*--------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    long thread, i;

    //el tipo abstracto pthread_t se implementa como un ID de subproceso entero (4 bytes). 
    pthread_t *thread_handles;  //thread 
    double start, finish;

    if (argc != 2)
        Usage(argv[0]);

    //strtol convierte la parte inicial de la cadena en str en un valor int largo de acuerdo con la base dada
    thread_count = strtol(argv[1], NULL, 10);

    thread_handles = malloc(thread_count * sizeof(pthread_t));


    for (i = 0; i < BARRIER_COUNT; i++)
        barrier_thread_counts[i] = 0;
    // inicializa la exclusión mutua a la que hace referencia mutex con atributos especificados por attr
    pthread_mutex_init(&barrier_mutex, NULL);

    GET_TIME(start);

    for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, Thread_work, (void *)thread);

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }
    GET_TIME(finish);

    printf("Elapsed time = %e seconds\n", finish - start);

    pthread_mutex_destroy(&barrier_mutex);
    free(thread_handles);
    return 0;
} /* main */

/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char *prog_name)
{

    fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
    exit(0);
} /* Usage */

/*-------------------------------------------------------------------
 * Function:    Thread_work
 * Purpose:     Run BARRIER_COUNT barriers
 * In arg:      rank
 * Global var:  thread_count, barrier_thread_counts, barrier_mutex
 * Return val:  Ignored
 */
void *Thread_work(void *rank)
{
#ifdef DEBUG
    long my_rank = (long)rank;
#endif
    int i;

    for (i = 0; i < BARRIER_COUNT; i++)
    {
        //el objeto mutex al que hace referencia mutex se bloqueará llamando a pthread_mutex_lock (). Si el mutex ya está bloqueado, 
        //el subproceso de llamada se bloqueará hasta que el mutex esté disponible.
        pthread_mutex_lock(&barrier_mutex);
        barrier_thread_counts[i]++;
        //La función pthread_mutex_unlock () desbloquea el mutex especificado. 
        pthread_mutex_unlock(&barrier_mutex);
        while (barrier_thread_counts[i] < thread_count);
#ifdef DEBUG
        if (my_rank == 0)
        {
            printf("All threads entered barrier %d\n", i);
            fflush(stdout);
        }
#endif
    }

    return NULL;
} /* Thread_work */