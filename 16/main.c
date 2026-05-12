#include "main.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	Element* data_top = NULL;
	Element* command_top = NULL;
	SELECT m;
	while (1) {
		menu();
		int result = scanf(" %d", &m);
		if (result != 1) {
			printf("Wrong input...\n");
			continue;
		}
		if (EXIT_MENU == m) {
			free_linked_list(data_top); 
			free_linked_list(command_top);
			break;
		}

		switch (m) {
		case PUSH_MENU: {
			int value;
			printf("Input value : ");
			result = scanf(" %d", &value);
			if (result != 1) {
				printf("Wrong input...\n");
				break;
			}
			push(&data_top, value, DATA);
			push(&command_top, value, PUSH_COMMAND);
			break;
		}
		case POP_MENU: {
			Element* removed = pop(&data_top);
			if (removed != NULL) {
				push(&command_top, removed->value, POP_COMMAND);
				free(removed);
			}
			break;
		}
		case PRINT_MENU: print(data_top); print(command_top);	break;
		case PEEK_MENU: peek(data_top);							break;
		case UNDO_MENU:	undo(&data_top, &command_top);			break;
		default: printf("Invaild SELECT number...\n");
		}
	}

	return 0;
}

void menu() {
	printf("==== STACK MENU ===\n");
	printf("1. Push\n");
	printf("2. Pop\n");
	printf("3. Print\n");
	printf("4. Peek\n");
	printf("5. Undo\n");
	printf("6. Exit\n");
	printf("(input) ");
}



// 중요함수
void push(Element** top, int value, ElementType type) {
	Element* new = (Element*)malloc(sizeof(Element));
	if (new == NULL) return;
	new->value = value;
	new->type = type;
	new->next = *top;
	*top = new;
}
Element* pop(Element** top) {
	if (*top == NULL) return NULL;
	if (isEmpty(*top)) {
		printf("Stack is Empty\n");
		return NULL;
	}
	Element* delete = *top;
	*top = (*top)->next;
	return delete;
}
void undo(Element** top_data, Element** top_command) {
	Element* last_command = pop(top_command);
	if (last_command == NULL) {
		printf("Not Existed last command\n");
		return;
	}

	// 최근 명령어가 PUSH면 POP함수를 호출하여 되돌리기
	if (last_command->type == PUSH_COMMAND) {
		printf("Undo PUSH COMMAND\n");
		Element* removed = pop(top_data);
		free(removed);
		print(*top_data);
	}
	// 최근 명령어가 POP이면 PUSH함수를 호출하여 되돌리기
	else if (last_command->type == POP_COMMAND) {
		printf("Undo POP COMMAND\n");
		push(top_data, last_command->value, DATA);
		print(*top_data);
	}
}

void free_linked_list(Element* top) {
	if (top == NULL) return;
	
	Element* next; Element* cur = top;
	while (cur != NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}
}
void print(Element* top) {
	if (top == NULL) {
		printf("Empty Stack\n");
		return;
	}
	printf("--------------\n");
	int i = 0;
	for (Element* temp = top; temp != NULL; temp = temp->next, i++) {
		printf("[%d]value=%d", i, temp->value);
		if (temp->type == PUSH_COMMAND) {
			printf(" PUSH COMMAND\n");
		} 
		else if (temp->type == POP_COMMAND) {
			printf(" POP COMMAND\n");
		}
		else {
			printf("\n");
		}
	}
	printf("--------------\n");
}
void peek(Element* top) {
	if (top == NULL) return;
	printf("Top value : %d\n", top->value);
}
int isEmpty(Element* top) {
	return top == NULL;
}