#ifndef __MAIN_H__
#define __MAIN_H__
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Singly LinkedList
typedef struct Node {
	struct Node* link;
	int value;

} Node; 

void run_simulation(int, int, int*, clock_t*, clock_t*);

// HEAD, TAIL, value
void insert_last(Node**, Node**, int);
// HEAD,index
int read_value(Node*, int);
// HEAD, index
Node* delete_node(Node*, int);
// HEAD
void free_linked(Node*);
// value
Node* create_node(int);


// 삽입
void insert_linked(Node**, Node**, int);
void insert_arr(int*, int);
// 랜덤 접근
void read_linked(Node*, int);
void read_arr(int*, int);
// 랜덤 삭제
void delete_linked(Node**, int);
void delete_arr(int*, int);

#endif
