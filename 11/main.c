#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/*
first 20
first 30
first 40
last 25
last 35
last 45
*/

int main(void) {
	struct Node* head = NULL;
	unsigned int input; char ch;
	while (1) {
		menu();
		if (scanf(" %u", &input) != 1) {
			printf("Invalid input..\n");
			continue;
		}
		while ((ch = getchar()) != '\n' && ch != EOF);

		switch (input) {
			case INSERT:	insert(&head);		break;
			case DELETE:	delete(&head);		break;
			case PRINT:		print(head);		break;
			case EXIT:		free_doubly(head);	return;
			default:		printf("Not allowed menu number\n");
		}
	}
	return 0;
}


void menu() {
	printf("======= MENU =======\n");
	printf("1. INSERT\n");
	printf("2. DELETE\n");
	printf("3. PRINT\n");
	printf("4. EXIT\n");
	printf("[INPUT] ");
}

void insert(Node** head) {
	int value;
	char pos[MAX_BUFFER];
	while (1) {
		printf("[Enter position and value]\n");
		if (scanf(" %9s", pos) != 1) {
			printf("Position Allocation Failed...\n");
			continue;
		}
		if (strncmp(pos, "quit", MAX_BUFFER) == 0) {
			break;
		}

		if (strncmp(pos, "first", MAX_BUFFER) == 0) {
			if (scanf(" %d", &value) != 1) {
				printf("Wrong integer value\n");
				continue;
			}
			*head = insert_first(*head, value);
			print_linked_list(*head);
		}
		else if (strncmp(pos, "last", MAX_BUFFER) == 0) {
			if (scanf(" %d", &value) != 1) {
				printf("Wrong integer value\n");
				continue;
			}
			*head = insert_last(*head, value);
			print_linked_list(*head);
		}
		else {
			printf("Not Support Position...\n");
		}
	}
}

void delete(Node** head) {
	if (*head == NULL) {
		printf("Empty Doubly LinkedList\n");
		return;
	}
	char pos[MAX_BUFFER];
	while (1) {
		printf("[Enter position]\n");
		if (scanf(" %9s", pos) != 1) {
			printf("Position Allocation Failed...\n");
			continue;
		}
		if (strncmp(pos, "quit", MAX_BUFFER) == 0) {
			break;
		}

		if (strncmp(pos, "first", MAX_BUFFER) == 0) {
			*head = delete_first(*head);
			print_linked_list(*head);
		}
		else if (strncmp(pos, "last", MAX_BUFFER) == 0) {
			*head = delete_last(*head);
			print_linked_list(*head);
		}
		else {
			printf("Not Support Position...\n");
		}
	}
}

Node* insert_first(Node* head, int value) {
	Node* newNode = create_node(value);

	if (head != NULL) {
		newNode->rlink = head;
		head->llink = newNode;
	}
	head = newNode;

	return head;
}

Node* insert_last(Node* head, int value) {
	Node* newNode = create_node(value);

	if (head != NULL) {
		Node* last = head;
		for (; last->rlink != NULL; last = last->rlink);
		last->rlink = newNode;
		newNode->llink = last;
	}
	else {
		head = newNode;
	}

	return head;
}

Node* delete_first(Node* head) {
	if (head->rlink == NULL) {
		free(head);
		return NULL;
	}

	Node* removeNode = head;
	Node* nextNode = head->rlink;
	nextNode->llink = NULL;
	free(removeNode);
	return nextNode;
}

Node* delete_last(Node* head) {
	if (head->rlink == NULL) {
		free(head);
		return NULL;
	}

	Node* removeNode = head;
	for (; removeNode->rlink != NULL; removeNode = removeNode->rlink);
	Node* previousNode = removeNode->llink;
	previousNode->rlink = NULL;
	free(removeNode);
	return head;
}

void print(Node* head) {
	char mode[MAX_BUFFER];
	unsigned int index;
	while (1) {
		printf("[Enter print MODE]\n");
		if (scanf(" %9s", mode) != 1) {
			printf("Invalid print MODE...\n");
			continue;
		}
		if (strncmp(mode, "quit", MAX_BUFFER) == 0) {
			break;
		}

		if (strncmp(mode, "forward", MAX_BUFFER) == 0) {
			if (scanf(" %u", &index) != 1) {
				printf("Wrong unsigned integer value\n");
				continue;
			}
			print_forward(head, index);
		}
		else if (strncmp(mode, "backward", MAX_BUFFER) == 0) {
			if (scanf(" %u", &index) != 1) {
				printf("Wrong unsigned integer value\n");
				continue;
			}
			print_backward(head, index);
		}
		else if (strncmp(mode, "print", MAX_BUFFER) == 0) {
			print_linked_list(head);
		}
	}
}

void print_forward(Node* head, int index) {
	if (head == NULL) {
		return;
	}

	int i = 0;
	Node* temp = head;
	for (; temp != NULL; temp = temp->rlink, i++) {
		if (i >= index) {
			printf("%d -> ", temp->value);
		}
	}

	if (i <= index) {
		printf("Wrong index range\n");
		return;
	}

	printf("NULL\n\n");
}

void print_backward(Node* head, int index) {
	if (head == NULL) {
		return;
	}

	int i = 0;
	Node* temp = head; Node* baseNode = NULL;
	// i와 index가 같을 때 baseNode 선정
	// 해당 노드부터 뒤에 있는 모든 노드의 값 출력
	for (; temp != NULL; temp = temp->rlink, i++) {
		if (i == index) {
			baseNode = temp;
			break;
		}
	}
	
	// 마지막 노드 이후 증감식에 의해 i == index인 경우가 발생함
	// 그러므로 BaseNode가 NULL인지도 확인
	if (i != index || baseNode == NULL) {
		printf("Wrong index range\n");
		return;
	}

	for (; baseNode != NULL; baseNode = baseNode->llink) {
		if (i >= index) {
			printf("%d -> ", baseNode->value);
		}
	}
	printf("NULL\n\n");
}

void print_linked_list(Node* head) {
	if (head == NULL) {
		return;
	}

	printf("NULL -> ");
	for (Node* temp = head; temp != NULL; temp = temp->rlink) {
		printf("%d -> ", temp->value);
	}
	printf("NULL\n\n");
}

Node* create_node(int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->llink = NULL; 
	newNode->rlink = NULL;
	newNode->value = value;
	return newNode;
}

void free_doubly(Node* head) {
	if (head == NULL) {
		return;
	}

	Node* nextNode = head->rlink;
	Node* removeNode = head;
	for (; nextNode != NULL; removeNode = nextNode) {
		printf("%d Node deallocation\n", removeNode->value);
		nextNode = removeNode->rlink;
		free(removeNode);
	}
}