#ifndef __MAIN_H__
#define __MAIN_H__

#define MAX_BUFFER 10

typedef enum MENU_NUMBER {
	INSERT = 1,
	DELETE,
	PRINT,
	EXIT
} MENU_NUMBER;

typedef struct Node {
	struct Node* rlink; // 오른쪽 링크
	struct Node* llink; // 왼쪽 링크
	int value;
} Node;

void menu();

void insert(Node**);
Node* insert_first(Node*, int);
Node* insert_last(Node*, int);
void delete(Node**);
Node* delete_first(Node*);
Node* delete_last(Node*);

void print(Node*);
void print_linked_list(Node*);
void print_forward(Node*, int);
void print_backward(Node*, int);

Node* create_node(int);
void free_doubly(Node*);

#endif