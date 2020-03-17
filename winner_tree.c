#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
#define INF 99999

int** winner; // data의 주소들을 넣어줌

void GenerateData(int*, int);
int* InitWinner(int, int);
void AdjustWinner(int*, int);
void inorder(int, int);

int main(void) {
	int k, seed;
	int* data, *sorted;
	int* min_address;
	int root = 1;

	printf("seed >> ");
	scanf("%d", &seed);
	srand(seed);

	printf("num of data >> ");
	scanf("%d", &k);

	data = (int*)malloc(sizeof(int)*(k + 1)); // 인덱스 1~k까지 사용
	sorted = (int*)malloc(sizeof(int)*(k + 1));  // 정렬결과를 저장할 배열
	for (int i = 0; i < k + 1; i++) {
		sorted[i] = NULL;
	}

	winner = (int**)malloc(sizeof(int*)*(2 * k)); // 인덱스 1~2*k-1 까지 사용
	for (int i = 0; i < 2 * k; i++) {
		winner[i] = (int*)malloc(sizeof(int));
		winner[i] = NULL;
	}

	GenerateData(data, k);

	for (int i = k; i < 2 * k; i++) {
		printf("%d ", data[i - k + 1]);
		winner[i] = &data[i - k + 1];
	}
	printf("\n");

	InitWinner(1, k);
	printf("\ninorder traversal : ");
	inorder(root, k);
	printf("\n");

	for (int i = 1; i <= k; i++) {
		min_address = InitWinner(1, k);
		sorted[i] = *min_address;
		AdjustWinner(min_address, k);
	}

	printf("sorted : ");
	for (int i = 1; i <= k; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\n");


}
void AdjustWinner(int* address, int size) {
	int i, target_index;
	int ptr;

	for (i = size; i < 2*size; i++) {
		if (winner[i] == address) {
			break;
		}
	}
	target_index = i;

	ptr = target_index;
	while (ptr) {
		*winner[ptr] = INF;
		ptr /= 2;
	}

}
int* InitWinner(int cur, int size) {
	int leftchild = 2 * cur;
	int leftwinner, rightwinner;

	if (leftchild >= 2 * size) {
		return winner[cur];
	}

	leftwinner = *InitWinner(leftchild, size);
	rightwinner = *InitWinner(leftchild + 1, size);

	if (leftwinner < rightwinner) {
		winner[cur] = winner[leftchild]; // ★ InittWinner(leftchild, size)로 하면 함수 두번이나 불러오는 거니깐
	}
	else {
		winner[cur] = winner[leftchild + 1];
	}
	return winner[cur]; // ★리턴 꼭 하기!!! 리턴 안하면 아무거나 리턴될 수 있음
}
void inorder(int cur, int size) {
	if (cur < size * 2) {
		inorder(cur * 2, size);
		printf("%d ", *winner[cur]);
		inorder(cur * 2 + 1, size);
	}
}
void GenerateData(int* data, int size) {
	int temp;

	data[0] = 0;
	for (int i = 1; i <= size; i++) {
		temp = (rand() % MAX_SIZE) + 1;
		data[i] = temp;
	}
}