#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  even  = PTHREAD_COND_INITIALIZER;
pthread_cond_t  odd   = PTHREAD_COND_INITIALIZER;

void *evenval(void *);
void *oddval(void *);
int num = 0;

int main()
{
    pthread_t pthread1;
	pthread_t pthread2;
    if (pthread_create(&pthread1, NULL, evenval, NULL) != 0) {
		exit(1);
	}
    if (pthread_create(&pthread2, NULL, oddval, NULL) != 0) {
		exit(1);
	}
    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
	return 0;
}

void *evenval(void *ptr)
{
	//pthread_mutex_lock(&mutex);
    while (num < 10) {
		pthread_mutex_lock(&mutex);
        while ((num & 1) == 1)
       		pthread_cond_wait(&even, &mutex);
        printf("\nEven value = %d\n", num);
		num++;
      	pthread_cond_signal(&odd);
        pthread_mutex_unlock(&mutex);
//		pthread_exit(NULL);
    	}
	//pthread_mutex_unlock(&mutex);
}

void *oddval(void *ptr)
{
	//pthread_mutex_lock(&mutex);
    while (num < 10) {
	 	pthread_mutex_lock(&mutex);
        while ((num & 1) == 0)
            pthread_cond_wait(&odd, &mutex);
        printf("\nOdd value = %d\n", num);
		num++;
        pthread_cond_signal(&even);
	 	pthread_mutex_unlock(&mutex);
		//pthread_exit(NULL);
	}
	//pthread_mutex_unlock(&mutex);
}
