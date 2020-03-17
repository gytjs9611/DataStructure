#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 500
#define DUPLICATED 1
#define SUCCESS 0
#define NOT_FOUND -99999

typedef int iType;
typedef struct node* treePointer;
typedef struct node {
	int key;
	iType item;
	treePointer leftchild, rightchild;
} tNode;

treePointer root = NULL;

int CreateBST(int); // BST는 중복 데이터가 있으면 안됨, 중복될 경우 DUPLICATED값을 리턴함
treePointer CreateNode(int);
int SearchKey(int); // 찾은 key에 해당하는 item을 반환
int RecSearchKey(treePointer, int);

void inorder(treePointer);


int main(void) {
	int num, seed, key;
	int new_data;
	int search_result;

	printf("num >> ");
	scanf("%d", &num);
	printf("seed >> ");
	scanf("%d", &seed);
	srand(seed);

	printf("input data : ");
	for (int i = 0; i < num; i++) {
		new_data = (rand() % MAX_SIZE) + 1;
		printf("%d ", new_data);
		if (CreateBST(new_data) == DUPLICATED) {
			i--;
		}
	}
	printf("\n");

	printf("Key to find >> ");
	scanf("%d", &key);
	printf("\n");
	
	search_result = SearchKey(key);
	if (search_result == NOT_FOUND) {
		printf("Error : Key is not found\n");
	}
	else {
		printf("Key %d's Item : %d\n", key, search_result);
	}	

	// ★ 오름차순으로 정렬하려면 중위순회하면 된다는 사실 기억
	printf("\ninorder traversal : ");
	inorder(root);
	printf("\n");


}
int SearchKey(int key) {
	treePointer ptr = root;

	while (ptr) {
		if (key==ptr->key) {
			return ptr->item;
		}
		else {
			if (key<ptr->key) {
				ptr = ptr->leftchild;
			}
			else {
				ptr = ptr->rightchild;
			}
		}
	}
	
	return NOT_FOUND;
}
int RecSearchKey(treePointer ptr, int key) {
	if (!ptr) {
		return NOT_FOUND;
	}
	if (ptr->key == key) {
		return ptr->item;
	}
	else if (ptr->key < key) {
		return RecSearchKey(ptr->rightchild, key);
	}
	else {
		return RecSearchKey(ptr->leftchild, key);
	}
}
int CreateBST(int data) {
	treePointer new_node = CreateNode(data);
	treePointer ptr = root;

	if (!ptr) {
		root = new_node;
		return;
	}

	while (ptr) {
		if (new_node->key == ptr->key)
		{
			return DUPLICATED;
		}
		if (new_node->key < ptr->key) {
			if (!ptr->leftchild) {
				ptr->leftchild = new_node;
				return SUCCESS;
			}
			else {
				ptr = ptr->leftchild;
			}
		}
		else {
			if (!ptr->rightchild) {
				ptr->rightchild = new_node;
				return SUCCESS;
			}
			else {
				ptr = ptr->rightchild;
			}
		}
	}

}
treePointer CreateNode(int data) {
	treePointer temp = (treePointer)malloc(sizeof(tNode));
	temp->item = data;
	temp->key = data;
	temp->leftchild = NULL;
	temp->rightchild = NULL;
	return temp;
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftchild);
		printf("%d ", ptr->key);
		inorder(ptr->rightchild);
	}
}