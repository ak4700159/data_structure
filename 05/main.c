#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu();
void init(int**, int*);
void print_max_min(int*, int);
void print_average(int*, int);
void delete_element(int**, int*);
void print_array(int*, int);

int main(void) {
	srand((unsigned int)time(NULL));
	int* arr = NULL; int n = 0; 
	char input; 
	while (1) {
		menu();
		// 문자열을 입력한 경우 버퍼속 문자를 전부 비워야됨
		scanf(" %c", &input);
		switch (input) {
			case '1': init(&arr, &n);			break;
			case '2': print_average(arr, n);	break;
			case '3': print_max_min(arr, n);	break;
			case '4': delete_element(&arr, &n);	break;
			case '5': print_array(arr, n);		break;
			case '6': free(arr);				return 0;
			default: printf("Wrong input number: -%c-\n\n", input);
		}
	}
	return 0;
}

void menu() {
	printf("===== MENU =====\n");
	printf("1. Initiate Array\n");
	printf("2. Print Average\n");
	printf("3. Print Min-Max\n");
	printf("4. Delete element\n");
	printf("5. Print all Array elements\n");
	printf("6. Exit\n");
	printf("(Input) ");
}

void init(int** arr, int *size) {
	while (1) {
		printf("Input Array size: ");
		int reuslt = scanf(" %d", size);
		if (reuslt == 1 && (*size) > 0) {
			break;
		}
		printf("Wrong input format\n");
	}

	*arr = (int*)malloc(sizeof(int) * (*size));
	if (*arr == NULL) {
		printf("Memory allocation Failed!\n");
		return;
	}

	for (int i = 0; i < (*size); i++) {
		(*arr)[i] = rand() % 101;
	}
}

void print_max_min(int* arr, int size) {
	if (arr == NULL) {
		printf("Memory allocation First...(please input 1 number)");
		return;
	}

	int min = arr[0], max = arr[0];
	for (int i = 1; i < size; i++) {
		if (min > arr[i]) {
			min = arr[i];
		}
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	printf("Min: %d, Max: %d\n\n", min, max);
}

void print_average(int* arr, int size) {
	if (arr == NULL) {
		printf("Memory allocation First...(please input 1 number)\n");
		return;
	}

	double avr = arr[0];
	for (int i = 1; i < size; i++) {
		avr += arr[i];
	}
	printf("Average : %.3f\n\n", avr / size);
}

void delete_element(int** arr, int* size) {
	if (*arr == NULL) {
		printf("Memory allocation First...(please input 1 number)\n");
		return;
	}

	int delete_number;
	while (1) {
		printf("Input delete number: ");
		int reuslt = scanf(" %d", &delete_number);
		if (reuslt != 0 && delete_number >= 0) {
			break;
		}
		printf("Wrong input format\n");
	}

	int new_len = 0;
	for (int i = 0; i < (*size); i++) {
		if ((*arr)[i] == delete_number) {
			continue;
		}
		new_len++;
	}

	int* new_arr = (int*)malloc(sizeof(int) * new_len);
	for (int i = 0, j = 0; i < (*size); i++) {
		if ((*arr)[i] != delete_number) {
			new_arr[j++] = (*arr)[i];
		}
	}

	free((*arr));
	*arr = new_arr;
	*size = new_len;
}

void print_array(int* arr, int size) {
	if (arr == NULL) {
		printf("Memory allocation First...(please input 1 number)\n");
		return;
	}

	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", arr[i]);
			break;
		}
		printf("%d -> ", arr[i]);
	}
	printf("\n\n");
}