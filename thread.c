#include <stdio.h>
#include <pthread.h>

//global variable
int i = 2;

void *fun(void *p);//sub thread

int main()
{
	//declare var for thread's id
	pthread_t id;
	int j = 1;
	pthread_create(&id, NULL, fun, &j);
	int *ptr;//to catch sub thread value when sub thread returns
	pthread_join(id, (void **)&ptr); //wait for fun() and retrieve value in ptr
	printf("value received by main thread from sub thread");
	printf("%i\n", *ptr);//print value of ptr received from sub thread (fun())
	return 0;
}

void *fun(void *p)
{
	//print value received as argument
	printf("value received as argument in strating routine ");
	printf("%i\n", *(int*)p);
	pthread_exit(&i); //exit thread and return reference to global variable
}
