/*
과제 감점 기준
- 잘못된 파일 양식
- 문제 의도와 다른 로직(ChatGPT Copy&Paste)
- 런타임 오류
- 로직 모순
*/


#include <stdio.h>

// 배열의 합을 구하는 함수
int sumArr(int*, int);

int main(void) {
	// 정적 배열 선언
	int arr[3][3] = { 0, };
	char in;

	int i, j, num = 1;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			arr[i][j] = num++;
		}
	}

	while (true) {
		printf("Select Index : ");
		// scanf 오류 시 scanf_s 사용
		// 버퍼에 남겨진 개행문자 \n를 삭제 위해 getchar() 사용 
		//           -> 문자열을 입력받아 예외처리하는 것이 가장 안전
		scanf_s("%c", &in); getchar();
		
		if ('1' <= in && '3' >= in) { // '1' = 48, '3' = 50
			int row_index = in - '1';
			int row_sum = sumArr(arr[row_index], 3);
			printf("Row Sum : %d\n", row_sum);
		}
		else if ('a' <= in && 'c' >= in) { // 'a' = 97, 'c' = 99
			int column_index = in - 'a';
			int column_arr[3] = {
				arr[0][column_index],
				arr[1][column_index],
				arr[2][column_index]
			};
			int column_sum = sumArr(column_arr, 3);
			printf("Column Sum : %d\n", column_sum);
		}
		else {
			printf("Unexpected Value : %c\n", in);
			break;
		}
	}
	return 0;
}

int sumArr(int* arr, int size) {
	int sum = 0;
	int i;
	for (i = 0; i < size; i++) {
		sum += arr[i];
	}
	return sum;
}