#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// 기존
typedef struct Node {
	struct Node* next;
	int value;
}Node;

void menu();
void print(Node*);
void search(Node*);
void free_linked_list(Node*);

// 수정 및 추가
void delete(Node**);
Node* delete_element(Node*, int);
void insert(Node**);
Node* insert_element(Node*, int, int);
void insert_after(Node**);
bool isNumber(char*);

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
		case '3': search(head);				break;
		case '4': insert_after(&head);		break;
		case '5': print(head);				break;
		case '6': free_linked_list(head);	return 0;
		default: printf("Wrong input number (%c)\n", input);
		}
	}
	return 0;
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
	printf("NULL\n\n");
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
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Search\n");
	printf("4. Insert after value\n");
	printf("5. Print\n");
	printf("6. exit\n");
	printf("(INPUT) ");
}


Node* insert_element(Node* head, int pos, int value) {
	// 음수 예외처리
	if (pos < 0) {
		return head;
	}

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		return head;
	}
	newNode->next = NULL;
	newNode->value = value;

	int i = 0;
	Node* nextNode = head;		// 삽입될 노드가 가리킬 노드 포인터 변수
	Node* previousNode = NULL;	// 삽입될 노드를 가리킬 노드 포인터 변수
	for (; nextNode != NULL; nextNode = nextNode->next, i++) {
		if (i == pos) {
			break;
		}
		previousNode = nextNode;
	}

	// LinkedList 내 노드를 추가 가능한 경우
	if (i == pos) {
		// head 노드 교체
		if (pos == 0) {
			newNode->next = head;
			head = newNode;
		} 
		else {
			previousNode->next = newNode;
			// 삽입될 자리가 마지막 위치가 아닌 경우
			if (nextNode != NULL) {
				newNode->next = nextNode;
			}
		}
	}
	else {
		printf("Not Found %d position...\n", pos);
		free(newNode);
	}
	return head;
}

/*
- 입력 예시
	0 20
	1 10
	2 30
	3 50
	4 33
	5 44
	quit
*/
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

		if (!isNumber(pos)) {
			printf("Invaild Number\n");
		}

		if (scanf(" %d", &value) == 1) {
			(*head) = insert_element(*head, atoi(pos), value);
		}
	}
}


Node* delete_element(Node* head, int pos) {
	// Linked List 할당 예외 처리
	if (head == NULL) {
		printf("HEAD is NULL\n");
		return NULL;
	}
	// 음수 예외 처리
	if (pos < 0) {
		printf("Not allowed negative value...\n");
		return head;
	}

	Node* deleteNode = head;	// 삭제될 노드
	Node* previousNode = NULL;	// 삭제될 노드를 가리키고 있는 노드
	int i = 0;  // LinkedList 내 현재 인덱스
	for (; deleteNode->next != NULL; deleteNode = deleteNode->next, i++) {
		if (i == pos) {
			break;
		}
		previousNode = deleteNode;
	}

	// LinkedList 내 노드를 삭제 가능한 경우
	if (i == pos) {
		Node* nextNode = deleteNode->next;
		// 삭제할 노드 할당 해제
		free(deleteNode);
		if (i == 0) {
			head = nextNode;
		}
		else {
			if (nextNode == NULL) {
				previousNode->next = NULL;
			}
			else {
				previousNode->next = nextNode;
			}
		}
	}
	// LinkedList 내 노드를 삭제 불가능한 경우
	else {
		printf("Not Found %d position...\n", pos);
	}
	return head;
}

/*
- 입력 예시
	0
	0
	0
	quit
*/
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

		if (!isNumber(pos)) {
			printf("Invaild Number\n");
		}

		*head = delete_element(*head, atoi(pos));
	}
}

void search(Node* head) {
	int search_value;
	printf("Search value : ");
	if (scanf(" %d", &search_value) != 1) {
		printf("Wrong input format\n");
		return;
	}

	int i = 0;
	for (Node* temp = head; temp != NULL; temp = temp->next) {
		if (search_value == temp->value) {
			printf("Find %d value, %d position\n\n", temp->value, i + 1);
			return;
		}
		i++;
	}
	printf("Not Found %d value...\n\n", search_value);
}

bool isNumber(char* str) {
	if (str == NULL || *str == '\0') return false; // 빈 문자열 처리

	for (int i = 0; i < strlen(str); i++) {
		if (!isdigit(str[i])) { // 숫자가 아니면
			return false;
		}
	}
	return true;
}

void insert_after(Node** head) {
	int previousValue;
	int value;
	printf("Input previous value and value\n");
	if (scanf(" %d %d", &previousValue, &value) != 2) {
		printf("Invalid value\n");
		return;
	}

	Node* temp = *head; int i = 0;
	for (; temp != NULL; temp = temp->next, i++) {
		if (temp->value == previousValue) {
			break;
		}
	}
	if (temp == NULL) {
		printf("Not found previous value: %d\n", previousValue);
		return;
	}

	// 현재 i는 previousValue를 가진 노드 인덱스이기 때문에 다음 노드에 삽입되기 위해 i+1 전달
	*head = insert_element(*head, i+1, value);
}