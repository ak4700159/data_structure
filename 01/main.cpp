#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Github TEST3
int main(void) {
	int max = 0;
	// 
	int arr[100] = { 0 };

	printf("arr memory address = %p\n", (void*)arr);
	// 난수 생성기의 시드 초기화 -> 초기화 시드는 현재 운영체제 시간으로 초기화(Unix timestamp 기준)
	unsigned int sec = (unsigned int)time(NULL);
	printf("Seconds : %d\n", sec);
	srand(sec);

	//(초기화식; 조건식; 증감식)
	// 1. 초기화식 실행
	// 2. 조건식 실행
	// 3. for문 내용 실행
	// 4. 증감식 실행
	// 5. 조건식 실행
	// 6. for문 내용 실행
	// ...
	for (int i = 0; i < 100; i++) {
		arr[i] = rand() % 101; // 0 ~ 100
	}

	for (int i = 0; i < 10; i++) {
		int temp = arr[rand() % 100];
		printf("Selected Number : %d\n", temp);
		if (temp > max) {
			max = temp;
		}
	}

	// 2차원 배열 이해하기
	int arr2[10][10] = { 0 };
	printf("arr2[2][2] : %p\n", &((arr2 + 2)[0][1]));
	printf("arr2[2][2] : %p\n", &(arr2[2][1]));
	return 0;
}