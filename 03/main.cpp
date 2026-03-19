// 보안 무시, {}_s 함수 사용을 강제하지 않음
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

/*
	char* str is char str[]
	char* str is NOT char str[100]
*/

void reverse(char*, int);

int main(void) {
	char str[MAX_SIZE];
	while (true) {
		printf("Input String : ");
		// 기존 scanf 함수는 입력값의 크기가 정해져 있지 않아(개행문자를 만날 때까지 읽음) 
		//											입력버퍼 속 오버플로우 발생 가능 -> 취약점 발생
		// 단일 문자만 입력 받을 경우(%c) 해당, %s로 문자열을 받을 경우 입력 버퍼에 있는 공백('\t', '\n', ' ')을 전부 지움
		scanf_s("%s", str, MAX_SIZE); 
		// fgets 함수 추천, fgets 함수 사용시 개행문자가 포함되어 문자열에 저장됨
		// fgets(str, MAX_SIZE, stdin); 

		// 문자열이 서로 동일하면 0, 다르다면 0이 아닌 값 반환
		if (strcmp(str, "q") == 0) {
			printf("While loop exited");
			break;
		}
		printf("Before : %s\n", str);
		reverse(str, strlen(str));
		printf("After : %s\n", str);
	}
	return 0;
}

void reverse(char* str, int size) {
	char temp[MAX_SIZE]; int temp_index = 0;
	for (int i = size - 1; i >= 0; i--) {
		if ('0' <= str[i] && '9' >= str[i]) {
			continue;
		}
		temp[temp_index++] = str[i];
	}
	// str에 temp(temp의 최대 크기 MAX_SIZE 명시)의 temp_index 크기만큼 복사
	strncpy_s(str, MAX_SIZE, temp, temp_index);
}
