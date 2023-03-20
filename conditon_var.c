#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_cond_t cond;
pthread_mutex_t lock;

void* thread1();
void* thread2();
void* thread3();

int num = 1;

int main()
{
	pthread_t id1;
	pthread_t id2;
	pthread_t id3;
	pthread_create(&id1, NULL, thread1, NULL);
	pthread_create(&id2, NULL, thread2, NULL);
	pthread_create(&id3, NULL, thread3, NULL);
	pthread_join(id1, NULL);
	return 0;
}

void* thread1()
{
	pthread_mutex_lock(&lock);
	if ( num != 1) {
		pthread_cond_wait(&cond, &lock);
	}
	printf("\nThread 1 process\n");
	num++;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
}

void* thread2()
{
        pthread_mutex_lock(&lock);
        if ( num != 2) {
                pthread_cond_wait(&cond, &lock);
        }
        printf("\nThread %d process\n", num);
        num++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
}

void* thread3()
{
        pthread_mutex_lock(&lock);
        if ( num != 3) {
                pthread_cond_wait(&cond, &lock);
        }
        printf("\nThread %d process\n", num);
        num++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
}
