#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Circular LinkedList
// HEAD(last) -> NODE(first) -> ... -> HEAD -> ... 구조
typedef struct Node {
	struct Node* next;
	int value;
}Node;

void menu();
void print(Node*);
void free_linked_list(Node*);

void insert(Node**);
Node* insert_first(Node*, int);
Node* insert_last(Node*, int);

void delete(Node**);
Node* delete_first(Node*);
Node* delete_last(Node*);

void clock_problem(Node**);


/*
first 10
first 20
first 30
last 15
last 25
quit
*/

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
		case '2': delete(&head);			break;
		case '3': clock_problem(&head);		break;
		case '4': print(head);				break;
		case '5': free_linked_list(head);	return 0;
		default: printf("Wrong input number (%c)\n", input);
		}
	}
	return 0;
}

void print(Node* head) {
	if (head == NULL) {
		return;
	}

	Node* current = head->next;
	for (; current != head; current = current->next) {
		printf("%d -> ", current->value);
	}
	printf("%d ...\n\n", head->value);
}

void free_linked_list(Node* head) {
	if (head == NULL) {
		return;
	}

	Node* next = NULL;
	Node* current = head->next;
	for (; current != head; current = next) {
		next = current->next;
		printf("Wiil be free : %d value Node\n", current->value);
		free(current);
	}
	printf("Wiil be free : %d value Node\n", head->value);
	free(head);
}

void menu() {
	printf("===== MENU =====\n");
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Solve clock problem\n");
	printf("4. Print\n");
	printf("5. exit\n");
	printf("(INPUT) ");
}


Node* insert_first(Node* head, int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		return head;
	}
	newNode->next = NULL;
	newNode->value = value;

	// 첫 번째 노드 생성
	if (head == NULL) {
		head = newNode;
		// (Circular)
		head->next = newNode;
	}
	else {
		// head의 다음 노드는 첫 번째 노드이기 때문에
		// 첫 번째 자리에 들어갈 노드는 이전 첫 번째 노드를 가리키면 됨
		newNode->next = head->next;
		// 마지막 노드의 다음은 당연히 첫 번째 자리에 새롭게 삽입될 노드가 됨
		head->next = newNode;
	}
	return head;
}

Node* insert_last(Node* head, int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		return head;
	}
	newNode->next = NULL;
	newNode->value = value;

	if (head == NULL) {
		head = newNode;
		// (Circular)
		head->next = newNode;
	}
	else {
		// 새로운 노드가 마지막 노드가 되기 위해서 첫 번째 노드 포인터 변수를 향함
		newNode->next = head->next;
		// 기존 마지막 노드는 새로운 노드를 향함 (Circular)
		head->next = newNode;
		head = newNode;
	}
	return head;
}

void insert(Node** head) {
	printf("Input insert Node position and value\n");
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

Node* delete_first(Node* head) {
	if (head == NULL) {
		printf("HEAD is NULL\n");
		return NULL;
	}

	if (head == head->next) {
		free(head);
		return NULL;
	}
	Node* removeNode = head->next;
	head->next = removeNode->next;
	free(removeNode);
	return head;
}


Node* delete_last(Node* head) {
	if (head == NULL) {
		printf("HEAD is NULL\n");
		return NULL;
	}

	if (head == head->next) {
		free(head);
		return NULL;
	}
	Node* lastPrevious = head; // 마지막 노드 이전 노드
	for (; lastPrevious->next != head; lastPrevious = lastPrevious->next);
	Node* removeNode = head;
	lastPrevious->next = removeNode->next;
	head = lastPrevious;
	free(removeNode);
	return head;
}

void delete(Node** head) {
	printf("Input delete Node position\n");
	char pos[10];
	while (1) {
		if (scanf("%9s", pos) != 1) {
			printf("Wrong position string format\n");
			continue;
		}

		if (strcmp(pos, "quit") == 0) {
			return;
		}

		else if (strcmp(pos, "first") == 0) {
			*head = delete_first(*head);
		}
		else if (strcmp(pos, "last") == 0) {
			*head = delete_last(*head);
		}
		else {
			printf("Wrong position string format\n");
		}
	}
}


void clock_problem(Node** head) {
	while (delete_first(*head) != NULL); *head = NULL;
	//free_linked_list(*head); head = NULL;

	for (int i = 1; i < 13; i++) {
		*head = insert_last(*head, i);
	}
	print(*head);

	int n1, n2;
	printf("Input n1, n2 : ");
	if (scanf(" %d %d", &n1, &n2) != 2) {
		printf("Wrong Input Format\n");
		return;
	}

	Node* solution = (*head)->next;
	for (int i = 1; i < n1 + n2; i++, solution = solution->next);
	printf("Solution : %d + %d = %d\n", n1, n2, solution->value);
}