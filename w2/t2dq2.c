#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
void main()
{
	fork();
	fork();
	//fork();
	printf("fork\n");
	exit(0);
}