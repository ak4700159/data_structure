#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	ArrayStack* stack = NULL;
	SELECT m;
	while (1) {
		menu();
		int result = scanf(" %d", &m);
		if (result != 1) {
			printf("Wrong input...\n");
			continue;
		}

		switch (m) {
		case CREATE: {
			int c;
			printf("Input Capacity : ");
			result = scanf(" %d", &c);
			if (result != 1) {
				printf("Wrong input...\n");
				break;
			}
			stack = createStack(c);
			break;
		}
		case PUSH: {
			int element;
			printf("Input Element : ");
			result = scanf(" %d", &element);
			if (result != 1) {
				printf("Wrong input...\n");
				break;
			}
			push(stack, element);
			break;
		}
		case POP: {
			int element = pop(stack);
			if (element != 0) {
				printf("Pop element %d\n", element);
			}
			break;
		}
		case PRINT: print(stack);  break;
		case EXIT: free(stack->array); free(stack); return;
		default: printf("Invaild SELECT number...\n");
		}
	}

	return 0;
}

void menu() {
	printf("==== MENU ===\n");
	printf("1. Create Stack\n");
	printf("2. Push\n");
	printf("3. Pop\n");
	printf("4. Print\n");
	printf("5. Exit\n");
	printf("(input) ");
}

ArrayStack* createStack(int c) {
	ArrayStack* newStack = (ArrayStack*)malloc(sizeof(ArrayStack));
	newStack->top = -1;
	newStack->capacity = c;
	newStack->array = (int*)malloc(sizeof(int) * c);
	return newStack;
}

int isEmpty(ArrayStack* stack) {
	return stack->top == -1;
}
int isFull(ArrayStack* stack) {
	return stack->top + 1 == stack->capacity;
}
void push(ArrayStack* stack, int element) {
	if (stack == NULL) return;
	if (isFull(stack)) {
		printf("Stack is Full\n");
		realloc_user(stack);
		printf("Realloc Stack data\n");
	}
	stack->array[++stack->top] = element;
}
int pop(ArrayStack* stack) {
	if (stack == NULL) return 0;
	if (isEmpty(stack)) {
		printf("Stack is Empty\n");
		return 0;
	}
	int element = stack->array[stack->top--];
	return element;
}
void print(ArrayStack* stack) {
	if (stack == NULL) return;
	printf("------------\n");
	for (int i = stack->top; i >= 0; i--) {
		printf("[%d]%d\n", i, stack->array[i]);
	}
	printf("Capacity=%d/Top=%d\n", stack->capacity, stack->top);
	printf("------------\n");
}

// 14 과제
int* deep_copy(int* old_data, int capacity) {
	int* new_data = (int*)malloc(sizeof(int) * capacity);
	for (int i = 0; i < (int)(capacity / 2); i++) {
		new_data[i] = old_data[i];
	}
	free(old_data);
	return new_data;
}
void realloc_user(ArrayStack* stack) {
	stack->capacity *= 2;
	stack->array = deep_copy(stack->array, stack->capacity);
}
