#include<stdio.h>
#include<stdlib.h>
#define MAX_DATA_SIZE 100
#define ARRAY_SIZE 10
#define INF 99999

int** keys;
int* key_pointer; // key array의 인덱스 알려주는 배열
int** winner; // keys data의 주소를 저장하는 포인터 배열

int* sorted;


void GenerateKeys(int);
void PrintKeys(int);

int* InitWinner(int, int); // cur, size
// winner data의 주소값을 반환
void AdjustWinner(int*, int);

int main(void) {
	int seed, num_of_arrays;
	int num_of_data;
	int* min_address;

	printf("seed >> ");
	scanf("%d", &seed);
	printf("the number of arrays >> ");
	scanf("%d", &num_of_arrays);
	printf("\n");

	srand(seed);

	num_of_data = num_of_arrays * ARRAY_SIZE;

	keys = (int**)malloc(sizeof(int*) * num_of_arrays);
	key_pointer = (int*)malloc(sizeof(int)*num_of_arrays);
	winner = (int**)malloc(sizeof(int*) * 2 * num_of_arrays);
	//1~2n-1까지 인덱스 사용
	sorted = (int*)malloc(sizeof(int)*num_of_data); // sort 결과저장

	for (int i = 0; i < num_of_arrays; i++) {
		keys[i] = (int*)malloc(sizeof(int)*ARRAY_SIZE);
		key_pointer[i] = 0;
	}
	for (int i = 0; i < 2 * num_of_arrays; i++) {
		winner[i] = NULL;
	}
	for (int i = 0; i < num_of_data; i++) {
		sorted[i] = NULL;
	}

	GenerateKeys(num_of_arrays);
	PrintKeys(num_of_arrays);
	printf("\n");


	for (int i = 0; i < num_of_data; i++) {
		min_address = InitWinner(1, num_of_arrays);
		sorted[i] = *winner[1];
		AdjustWinner(min_address, num_of_arrays);
	}

	for (int i = 0; i < num_of_data; i++) {
		printf("%3d", sorted[i]);
		if ((i + 1) % ARRAY_SIZE == 0)
		{
			printf("\n");
		}
	}

		
}
int* InitWinner(int cur, int num) { // 1~2*num-1까지 인덱스존재
	int leftchild, rightchild;
	int leftwinner, rightwinner;

	leftchild = 2 * cur;
	rightchild = leftchild + 1;

	if (leftchild > 2 * num - 1) { // child가 존재하지 않는 말단
		return winner[cur];
	}
	
	leftwinner = *InitWinner(leftchild, num);
	rightwinner = *InitWinner(rightchild, num);

	if (leftwinner < rightwinner) {
		winner[cur] = winner[leftchild];
	}
	else {
		winner[cur] = winner[rightchild];
	}
	return winner[cur];
}
void AdjustWinner(int* address, int num) {
	int winner_index;
	int key_index, array_index;

	for (int i = num; i < 2*num; i++) {
		if (address == winner[i]) {
			winner_index = i;
			break;
		}
	}
	key_index = winner_index - num;

	array_index = ++key_pointer[key_index]; // key 내의 index 변경

	if (array_index == ARRAY_SIZE) { // no more data in keys[i]
		*winner[winner_index] = INF;
	}
	else {
		winner[winner_index] = &keys[key_index][array_index];
	}

}
void GenerateKeys(int num) {
	int temp;

	for (int i = 0; i < num; i++) {
		temp = 1 + rand() % MAX_DATA_SIZE;
		for (int j = 0; j < ARRAY_SIZE; j++) {
			keys[i][j] = (temp + j);
		}
	}

	for (int i = num; i < 2 * num; i++) {
		winner[i] = &keys[i - num][0];
	}
}
void PrintKeys(int num) {
	for (int i = 0; i < num; i++) {
		printf("keys[%d] : ", i);
		for (int j = 0; j < ARRAY_SIZE; j++) {
			printf("%d ", keys[i][j]);
		}
		printf("\n");
	}
}