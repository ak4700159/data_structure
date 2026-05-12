#ifndef __MAIN_H__
#define __MAIN_H__

typedef enum {
	PUSH_COMMAND = 1,
	POP_COMMAND,	  
	DATA			 
} ElementType;

typedef struct {
	int value;
	ElementType type;
	struct Element* next; // LinkedList 구현
} Element;

typedef enum {
	PUSH_MENU = 1,
	POP_MENU,
	PRINT_MENU,
	PEEK_MENU,
	UNDO_MENU,
	EXIT_MENU
} SELECT;

void menu();
void print(Element*);
void peek(Element*);
int isEmpty(Element*);

// 중요함수
void push(Element**, int, ElementType);
Element* pop(Element**);
void undo(Element**, Element**);
void free_linked_list(Element*);

#endif