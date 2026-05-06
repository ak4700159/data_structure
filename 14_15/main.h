#ifndef __MAIN_H__
#define __MAIN_H__

typedef struct {
	int top;
	int capacity;
	int* array;
} ArrayStack;

typedef enum {
	CREATE = 1,
	PUSH,
	POP,
	PRINT,
	EXIT
} SELECT;

void menu();
void print(ArrayStack*);

ArrayStack* createStack(int);
int isEmpty(ArrayStack*);
int isFull(ArrayStack*);
void push(ArrayStack*, int);
int pop(ArrayStack*);
// 과제 14
int* deep_copy(int*, int);
void realloc_user(ArrayStack*);

#endif