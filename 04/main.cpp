#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct {
	char* name;
	int age;
	double score;
} Student;

typedef struct {
	Student* arr;	// 학생 배열(동적 할당)
	int len;		// 입력된 학생의 수 
	int capacity;	// 할당된 학생의 수
} Students;

int init(Students*);				// 학생 배열 초기화 함수
void menu(void);					// 메뉴 출력 함수
void insert_students(Students*);	// 학생 입력 함수
void insert_student(Students*, char*, int, double); 
int print_student(Students*, char*);// 학생 출력 함수
double avg_total(Students*);		// 점수 평균 계산 함수
int save(Students*);				// 학생 배열 저장 함수
void clean_input_buffer();			// 입력 버퍼 비우는 함수

int main(void) {
	Students students = { NULL, 0, 0 }; init(&students);
	char input;
	while (1) {
		menu();
		// 문자열을 입력한 경우 버퍼속 문자를 전부 비워야됨
		scanf(" %c", &input);
		switch (input) {
			case '1': {
				insert_students(&students);
				break;
			}
			case '2': {
				char name[MAX_SIZE];
				printf("Find name : "); scanf(" %s", name);
				print_student(&students, name);
				break;
			}
			case '3': {
				double avg = avg_total(&students);
				printf("Average score: %f\n\n", avg);
				break;
			}
			case '4': {
				save(&students);
				break;
			}
			case '5': return 0;
			default: printf("Wrong input number: -%c-\n\n", input);
		}
	}
	return 0;
}

int init(Students* students) {
	students->capacity = 1;
	students->arr = (Student*)malloc(sizeof(Student) * students->capacity);
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL) {
		printf("File open failed\n");
		return 1;
	}

	char line[MAX_SIZE];
	char name[MAX_SIZE]; int age; double score;
	while (fgets(line, sizeof(line), fp) != NULL) {
		line[strcspn(line, "\n")] = '\0';   // 문자 배열 속 개행 문자를 널 문자로
		if (sscanf(line, "%s %d %lf", name, &age, &score) == 3) { // 배열 문자열을 지정된 포맷에 맞게 변형
			printf("name=%s, age=%d, score=%.1f Read\n", name, age, score);
			insert_student(students, name, age, score);
		}
		else {
			printf("Wrong Format: %s\n", line);
		}
	}
	fclose(fp);
}

void menu(void) {
	printf("===Menu===\n");
	printf("1. Insert Students\n");
	printf("2. Print Stuent\n");
	printf("3. Total Average Stuent\n");
	printf("4. Save Students\n");
	printf("5. Exit\n");
	printf("(input): ");
}

void insert_students(Students* students) {
	printf("Insert Student Information, format=name age score, quit=q: \n");
	while (1) {
		char name[MAX_SIZE]; int age; double score;
		scanf(" %s", name);
		if (strcmp(name, "q") == 0) {
			break;
		}
		scanf("%d %lf", &age, &score);
		insert_student(students, name, age, score);
	}
}

void insert_student(Students* students, char* name, int age, double score) {
	if (students->len == students->capacity) {
		students->capacity *= 2;
		students->arr = (Student*)realloc(students->arr, sizeof(Student) * students->capacity);
	}
	students->arr[students->len].name = (char*)malloc(strlen(name) + 1); // 마지막 널문자 포함
	strcpy(students->arr[students->len].name, name);
	students->arr[students->len].age = age;
	students->arr[students->len].score = score;
	students->len++;
}

int print_student(Students* students, char* name) {
	int select = -1;
	for (int i = 0; i < students->len; i++) {
		if (strcmp(students->arr[i].name, name) == 0) {
			select = i;
			break;
		}
	}
	if (select == -1) {
		printf("Not found %s student", name);
		return 1;
	}
	printf("name: %s, age: %d, score: %lf\n\n", 
		students->arr[select].name,
		students->arr[select].age, 
		students->arr[select].score);
	return 0;
}

double avg_total(Students* students) {
	double avg = 0.;
	for (int i = 0; i < students->len; i++) {
		avg += students->arr[i].score;
	}
	if (students->len == 0) return 0.0;
	return avg / students->len;
}

int save(Students* students) {
	FILE* fp = fopen("student.txt", "w");
	if (fp == NULL) {
		printf("File open failed\n");
		return 1;
	}

	for(int i = 0; i < students->len; i++) {
		fprintf(fp, "%s %d %f\n", 
			students->arr[i].name,
			students->arr[i].age, 
			students->arr[i].score);
	}
	fclose(fp);
	return 0;
}

void clean_input_buffer() {
	int ch;
	while (1) {
		ch = getchar();
		// 개행문자 또는 읽기 불가능한 상태일 경우 종료
		if (ch == '\n' || ch == EOF) {
			return;
		}
	}
}