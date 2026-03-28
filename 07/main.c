#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	struct Node* next;
	int value;
}Node;

void insert(Node**);
Node* insert_first(Node*, int);
Node* insert_last(Node*, int);
void print(Node*);
void free_linked_list(Node*);
void menu();

int main(void) {
	Node* head = NULL;
	char input;
	while (1) {
		menu();
		int result = scanf(" %c", &input);
		if (result != 1) {
			break;
		}

		switch (input) {
			case '1': insert(&head);			break;
			case '2': print(head);				break;
			case '3': free_linked_list(head);	return 0;
			default: printf("Wrong input number (%c)\n", input);
		}
	}
	return 0;
}

/*
- 입력 예시
	last 20
	last 10
	first 30
	first 50
	last 33
	first 44
	quit
*/
void insert(Node** head) {
	printf("Input inserted Node position(first or last or quit) and value\n");
	printf("ex) first 20\n");
	char pos[10];
	int value;
	while (1) {
		if (scanf("%9s", pos) != 1) {
			printf("Wrong position string format\n");
			continue;
		}

		if (strcmp(pos, "quit") == 0) {
			return;
		}
		else if (strcmp(pos, "first") == 0) {
			if (scanf(" %d", &value) != 1) {
				printf("Wrong integer value\n");
				continue;
			}
			*head = insert_first(*head, value);
		}
		else if (strcmp(pos, "last") == 0) {
			if (scanf(" %d", &value) != 1) {
				printf("Wrong integer value\n");
				continue;
			}
			*head = insert_last(*head, value);
		}
		else {
			printf("Wrong position string format\n");
		}
	}
}

Node* insert_first(Node* head, int value) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = value;
	if (head == NULL) {
		new_node->next = NULL;
	}
	else {
		new_node->next = head;
	}
	return new_node;
}

Node* insert_last(Node* head, int value) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = value;
	new_node->next = NULL;
	if (head == NULL) {
		return new_node;
	}

	Node* last = head;
	for (; last->next != NULL; last = last->next);
	last->next = new_node;
	return head;
}

void print(Node* head) {
	if (head == NULL) {
		return;
	}

	Node* current = head;
	do {
		printf("%d -> ", current->value);
		current = current->next;
	} while (current != NULL);
	printf("NULL\n");
}

void free_linked_list(Node* head) {
	if (head == NULL) {
		return;
	}

	Node* next = NULL;
	Node* current = head;
	printf("Wiil be free : %d value Node\n", head->value);
	do {
		next = current->next;
		free(current);
		// 아직 다음 노드가 메모리(heap)에 남아 있음을 의미
		if (next != NULL) {
			printf("Wiil be free : %d value Node\n", next->value);
		}
		current = next;
	} while (current != NULL);
}

void menu() {
	printf("===== MENU =====\n");
	printf("1. Insert Linked List\n");
	printf("2. Print Linked List\n");
	printf("3. exit\n");
	printf("(INPUT) ");
}