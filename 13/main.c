#include "main.h"

#define INSERT_N 100000
#define EXTENSION_N 10000

int main(void) {
	run_simulation(PLUS);
	run_simulation(TIMES);
	return 0;
}

void run_simulation(METHOD m) {
	int i = m == PLUS ? 1 : 2;
	for (; i < EXTENSION_N; i++) {
		ArrayList* arr = NULL;
		init_arr(&arr, i, m);

		clock_t start = clock();
		for (int j = 1; j <= INSERT_N; j++) {
			insert_last(arr, j);
		}
		clock_t end = clock();
		clock_t interval = end - start;

		if (m == PLUS) {
			printf("Estimated Time(PLUS) : %ld\n", interval);
		}
		else if (m == TIMES) {
			printf("Estimated Time(TIMES) : %ld\n", interval);
		}
		
		record(arr, interval);
		free(arr->data);
		free(arr);
	}
}

void init_arr(ArrayList** arr, int n, METHOD m) {
	*arr = (ArrayList*)malloc(sizeof(ArrayList));
	(*arr)->size = 0; (*arr)->capacity = 1;
	(*arr)->data = (int*)malloc(sizeof(int) * (*arr)->capacity);
	(*arr)->n = n; (*arr)->method = m; (*arr)->extensions = 0;
}

int is_empty(ArrayList* arr) {
	return arr->capacity == arr->size;
}

void deep_copy(ArrayList* arr) {
	int* new_arr = NULL;

	if (arr->method == PLUS) {
		arr->capacity = arr->capacity + arr->n;
	}
	else if (arr->method == TIMES) {
		arr->capacity = arr->capacity * arr->n;
	}
	else {
		printf("Not Supported Extension Method...\n");
		return;
	}

	new_arr = (int*)malloc(sizeof(int) * arr->capacity);
	for (int i = 0; i < arr->size; i++) {
		new_arr[i] = arr->data[i];
	}
	free(arr->data);
	arr->data = new_arr;
	arr->extensions += 1;
}

void insert_last(ArrayList* arr, int element) {
	if (is_empty(arr)) {
		deep_copy(arr);
	}
	arr->data[arr->size++] = element;
}

void record(ArrayList* arr, clock_t interval) {
	FILE* fp = fopen("record.txt", "a");
	if (fp == NULL) {
		printf("File open failed\n");
		return;
	}

	int result = fprintf(
		fp, 
		"%d, %d, %d, %ld\r", 
		arr->n, arr->method, arr->extensions, interval
	);
	if (result < 0) {
		printf("Write Failed...\n");
	}

	fclose(fp);
}
