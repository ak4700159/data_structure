#ifndef __MAIN_H__
#define __MAIN_H__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	PLUS = 1,
	TIMES = 2
} METHOD;

typedef struct ArrayList {
	int size;       // 현재 배열 크기
	int capacity;	// 수용 가능한 배열 크기
	int extensions;	// 확장 횟수
	int* data;		// 배열

	int n;			// 확장 크기
	METHOD method;	// 확장 방법
} ArrayList;

void run_simulation(METHOD);

void init_arr(ArrayList**, int, METHOD);
int is_empty(ArrayList*);

void deep_copy(ArrayList*);

void insert_last(ArrayList*, int);
void insert(ArrayList*);

void record(ArrayList*, clock_t);

#endif