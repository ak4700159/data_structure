#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int max_size;
	int size;
	int* pArray;
} ArrayList;

void menu();
void init(ArrayList* arr);
int is_full(ArrayList* arr);
int is_empty(ArrayList* arr);
void insert(ArrayList* arr, int pos);
void delete(ArrayList* arr, int pos);
void print_list(ArrayList* arr);

int main(void) {
	ArrayList arr = { 0, 0, NULL };
	char input;
	while (1) {
		menu();
		// 문자열을 입력한 경우 버퍼속 문자를 전부 비워야됨
		scanf(" %c", &input);
		switch (input) {
			case '1': init(&arr);					break;
			case '2': insert(&arr, 0);				break;
			case '3': insert(&arr, arr.size);		break;
			case '4': delete(&arr, 0);				break;
			case '5': delete(&arr, arr.size-1);		break;
			case '6': print_list(&arr);				break;
			case '7': free(arr.pArray);				return 0;
			default: printf("Wrong input number: -%c-\n\n", input);
		}
	}
	return 0;
}

void menu() {
	printf("===== MENU =====\n");
	printf("1. Initiate Array\n");
	printf("2. Insert First\n");
	printf("3. Insert Last\n");
	printf("4. Delete First\n");
	printf("5. Delete Last\n");
	printf("6. Print List\n");
	printf("7. Exit\n");
	printf("(Input) ");
}

void init(ArrayList* arr) {
	while (1) {
		printf("Input ArrayList Max size: ");
		int reuslt = scanf(" %d", &arr->max_size);
		if (reuslt == 1 && arr->max_size > 0) {
			break;
		}
		printf("Wrong input format\n");
	}

	free(arr->pArray);
	arr->pArray = (int*)malloc(sizeof(int) * arr->max_size);
	if (arr->pArray == NULL) {
		printf("Memory allocation Failed!\n");
		return;
	}
	arr->size = 0;
}

int is_full(ArrayList* arr) {
	return arr->max_size == arr->size;
}

int is_empty(ArrayList* arr) {
	return arr->size == 0;
}

void insert(ArrayList* arr, int pos) {
	if (arr->pArray == NULL) {
		printf("Please allocate pArray\n");
		return;
	}

	if (is_full(arr)) {
		printf("ArrayList is full\n");
		return;
	}

	if (pos < 0 || pos > arr->size) {
		printf("Invalid position\n");
		return;
	}

	int insert_element;
	while (1) {
		printf("Input insert element: ");
		int reuslt = scanf(" %d", &insert_element);
		if (reuslt != 0 && insert_element >= 0) {
			break;
		}
		printf("Wrong input format\n");
	}


	for (int i = arr->size; i > pos; i--) {
		arr->pArray[i] = arr->pArray[i-1];
	}
	arr->pArray[pos] = insert_element;
	arr->size++;
}

void delete(ArrayList* arr, int pos) {
	if (arr->pArray == NULL) {
		printf("please allocate pArray\n");
		return;
	}

	if (is_empty(arr)) {
		printf("ArrayList is empty\n");
		return;
	}

	if (pos < 0 || pos >= arr->size) {
		printf("Invalid position\n");
		return;
	}

	int delete_element = arr->pArray[pos];
	for (int i = pos; i < arr->size - 1; i++) {
		arr->pArray[i] = arr->pArray[i + 1];
	}
	arr->size--;
}

void print_list(ArrayList* arr) {
	if (arr->pArray == NULL) {
		printf("please allocate pArray\n");
		return;
	}

	for (int i = 0; i < arr->size; i++) {
		if (i == arr->size - 1) {
			printf("%d, (%d/%d)\n", arr->pArray[i], arr->size, arr->max_size);
			break;
		}
		printf("%d -> ", arr->pArray[i]);
	}
}



