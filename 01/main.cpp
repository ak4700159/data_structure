#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Github TEST2
int main(void) {
	int max = 0;
	int arr[100] = { 0 };
	printf("arr memory address = %p\n", (void*)arr);
	// 난수 생성기의 시드 초기화 -> 초기화 시드는 현재 운영체제 시간으로 초기화(Unix timestamp 기준)
	unsigned int sec = (unsigned int)time(NULL);
	printf("Seconds : %d\n", sec);
	srand(sec);

	for (int i = 0; i < 100; i++) {
		arr[i] = rand() % 101;
	}

	for (int i = 0; i < 10; i++) {
		int temp = arr[rand() % 100];
		printf("Selected Number : %d\n", temp);
		if (temp > max) {
			max = temp;
		}
	}
	return 0;
}