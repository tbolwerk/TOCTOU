#include "stdio.h"
#include "stdlib.h"
#include "pthread/pthread.h"

int amount;

void* withdraw(void *x)
{
	int xi = (int) x;
	if(amount - xi >= 0){
		amount -= xi;
		return (void*)(xi);
	}
	printf("Not enough money, to withdraw $%d\n", xi);
	return 0;
}

int main(int argc, char** argv)
{
	int count = 0;
	while(amount >= 0){
		amount = 100;
		pthread_t a;
		pthread_t b;
		pthread_create(&a, NULL, withdraw, (void*) 100);
		pthread_create(&b, NULL, withdraw, (void*) 100);

		void* ret_from_thread_a;
		void* ret_from_thread_b;
		int ra = 0;
		int rb = 0;
		pthread_join(a, &ret_from_thread_a);
		ra = (int) ret_from_thread_a;
		pthread_join(b, &ret_from_thread_b);
		rb = (int) ret_from_thread_b;

		printf("A thread, which returned %d\n", ra);
		printf("B thread, which returned %d\n", rb);
		printf("Amount in the bank %d\n", amount);
		count ++;
	}
	printf("After just %d iterations we got a TOCTOU issue\n", count);
	return 0;
}

