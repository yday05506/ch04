#include <stdio.h>
#define SIZE 6

int queue[SIZE] = { 0 };
int rear = -1;
int front = 0;

int main(void)
{
	add(10);
	add(20);
	add(30);

	printf("%d\n", delete());	// 10
	printf("%d\n", delete());	// 20
	printf("%d\n", delete());	// 30
	printf("%d\n", delete());	// Queue Underflow!, -1

	add(40);
	add(50);
	add(60);
	add(70);	// Queue Overflow!

	printf("%d\n", delete());	// 40
	printf("%d\n", delete());	// 50
	printf("%d\n", delete());	// 60
	printf("%d\n", delete());	// Queue Underflow!, -1

	return 0;
}

int add(int data)
{
	if (rear == SIZE - 1)
	{
		printf("Queue Overflow!\n");
		return -1;
	}
	queue[++rear % SIZE] = data;	// Circular

	return 0;
}

int delete(void)
{
	if (rear < front)
	{
		printf("Queue Underflow!\n");
		return -1;
	}

	return queue[front++ % SIZE];
}