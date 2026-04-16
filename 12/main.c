#include "main.h"

int main() {
	srand((unsigned int)time(NULL));
	int N; int iter;
	printf("Size : "); scanf(" %d", &N);
	printf("Iter : "); scanf(" %d", &iter);

	int i = 0;
	clock_t array_delete_time = 0;
	clock_t linked_delete_time = 0;
	int array_delete_win = 0.;
	while (i < iter) {
		run_simulation(
			N, 1, 
			&array_delete_win, 
			&array_delete_time, 
			&linked_delete_time
		);
		printf("\n");
		i++;
	}
	printf("ArrayList delete total time : %ld ms\n", array_delete_time);
	printf("Singly LinkedList delete total time : %ld ms\n", linked_delete_time);
	printf("ArrayList win count : %d\n", array_delete_win);
	printf("Singly LinkedList win count : %d\n", iter - array_delete_win);
	return 0;
}

void run_simulation(int size, int debug, int* aw, clock_t* adt, clock_t* ldt) {
	int* arr = (int*)malloc(sizeof(int) * size);
	Node* head = NULL; Node* tail = NULL;
	clock_t linked_delete_time = 0;
	clock_t array_delete_time = 0;

	clock_t start = clock();
	insert_arr(arr, size);
	clock_t end = clock();
	if (debug) printf("ArrayList Insertion time : %ld ms\n", end - start);

	start = clock();
	insert_linked(&head, &tail, size);
	end = clock();
	if (debug) printf("Singly LinkedList Insertion time : %ld ms\n\n", end - start);

	start = clock();
	read_arr(arr, size);
	end = clock();
	if (debug) printf("ArrayList Random Access time : %ld ms\n", end - start);

	start = clock();
	read_linked(head, size);
	end = clock();
	if (debug) printf("Singly LinkedList Random Access time : %ld ms\n\n", end - start);

	start = clock();
	delete_arr(arr, size);
	end = clock();
	array_delete_time = end - start;
	if (debug) printf("ArrayList Random Delete time : %ld ms\n", array_delete_time);
	*adt += array_delete_time;

	start = clock();
	delete_linked(&head, size);
	end = clock();
	linked_delete_time = end - start;
	if (debug) printf("Singly LinkedList Random Delete time : %ld ms\n", linked_delete_time);
	*ldt += linked_delete_time;

	if (array_delete_time < linked_delete_time) {
		*aw += 1;
	}

	free(arr);
	free_linked(head);
	if(debug) printf("==================================================\n\n");
}


void insert_last(Node** head, Node** tail, int value) {
	Node* newNode = create_node(value);
	if (newNode == NULL) {
		printf("Allocation Failed...\n");
		return;
	}

	if (*head == NULL) {
		*head = newNode;
		*tail = *head;
		return;
	}

	(*tail)->link = newNode;
	*tail = newNode;
}
// HEAD,index
int read_value(Node* head, int index) {
	Node* curNode = head; int i = 0;
	while (curNode != NULL) {
		if (i == index) {
			return curNode->value;
		}
		curNode = curNode->link;
		i++;
	}
	return 0;
}
// HEAD, index
Node* delete_node(Node* head, int index) {
	Node* curNode = head; 
	Node* preNode = NULL; Node* nextNode = NULL;
	int i = 0;
	for (; curNode->link != NULL; curNode = curNode->link, i++) {
		if (i == index) {
			Node* removeNode = curNode;
			if (preNode == NULL) {
				head = removeNode->link;
			}
			else {
				preNode->link = removeNode->link;
			}
			free(removeNode);
			break;
		}
		preNode = curNode;
	}
	return head;
}
// HEAD
void free_linked(Node* head) {
	Node* curNode = head;
	while (curNode != NULL) {
		Node* nextNode = curNode->link;
		free(curNode);
		curNode = nextNode;
	}
}
Node* create_node(int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->link = NULL;
	newNode->value = value;
	return newNode;
}

// 삽입
void insert_linked(Node** head, Node** tail, int size) {
	for (int i = 0; i < size; i++) {
		insert_last(head, tail, i);
	}
}
void insert_arr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = i;
	}
}

// 랜덤 접근
void read_linked(Node* head, int size) {
	int sum = 0;
	for (int i = 0; i < (int)size / 10; i++) {
		int random_idx = rand() % size;
		sum += read_value(head, random_idx);
	}
	printf("Read Singly LinkedList Result : %d\n", sum);
}
void read_arr(int* arr, int size) {
	int sum = 0;
	for (int i = 0; i < (int)size / 10; i++) {
		int random_idx = rand() % size;
		sum += arr[random_idx];
	}
	printf("Read ArrayList Result : %d\n", sum);
}

// 랜덤 삭제
void delete_linked(Node** head, int size) {
	for (int i = 0; i < (int)size / 10; i++) {
		int random_idx = rand() % (size - i);
		*head = delete_node(*head, random_idx);
	}
}
void delete_arr(int* arr, int size) {
	for (int i = 0; i < (int)size / 10; i++) {
		int random_idx = rand() % (size - i);
		for (int j = random_idx; j < size - i - 1; j++) {
			arr[j] = arr[j + 1];
		}
	}
}