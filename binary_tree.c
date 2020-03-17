#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> // toupper, tolower 함수 사용 위해 선언

#define MAX_DATA_SIZE 100
#define MAX_QUEUE_SIZE 100

#define TRUE 1
#define FALSE 0

#define EMPTY 0
#define LEFT 1
#define FULL 2

typedef struct node* treePointer;
typedef struct node {
	char data;
	treePointer leftchild, rightchild;
}tNode;

treePointer root = NULL;

treePointer queue[MAX_QUEUE_SIZE]; //circular queue로 구현
int front = -1, rear = -1;


void inorder(treePointer);
void preorder(treePointer);
void postorder(treePointer);
void CreateBinTree(char);
treePointer CreateNode(char);
int ChildState(treePointer);
void AddQueue(treePointer);
treePointer DeleteQueue();
treePointer ReturnFront();

int main(void) {
	char input[MAX_DATA_SIZE];
	int data_size = 0;

	scanf("%s", input);
	data_size = strlen(input);

	for (int i = 0; i < data_size; i++) {
		CreateBinTree(input[i]);
	}

	printf("inorder traversal : ");
	inorder(root);
	printf("\npreorder traversal : ");
	preorder(root);
	printf("\npostorder traversal : ");
	postorder(root);
	printf("\n");

}
void CreateBinTree(char data) {
	treePointer ptr, temp;
	treePointer new_node = CreateNode(data);

	if (!root) {
		AddQueue(new_node);
		root = new_node;
		return;
	}

	ptr = ReturnFront();
	if (ChildState(ptr) == LEFT) {
		ptr->rightchild = new_node;
		AddQueue(ptr->rightchild);
		DeleteQueue();
	}
	else if (ChildState(ptr) == EMPTY) {
		ptr->leftchild = new_node;
		AddQueue(ptr->leftchild);
	}


}
void AddQueue(treePointer ptr) {
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (rear == front) {
		fprintf(stderr, "Queue is full, cannot add\n");
		exit(EXIT_FAILURE);
	}
	else {
		queue[rear] = ptr;
	}
}
treePointer DeleteQueue() {

	if (front == rear) {
		fprintf(stderr, "Queue is empty, cannot delete\n");
		exit(EXIT_FAILURE);
	}
	else {
		front = (front + 1) % MAX_QUEUE_SIZE;
		return queue[front];
	}
}
treePointer ReturnFront() {
	return queue[front + 1];
}
int ChildState(treePointer ptr) {
	if (ptr->leftchild && ptr->rightchild) {
		return FULL;
	}
	else if (ptr->leftchild) {
		return LEFT;
	}
	else {
		return EMPTY;
	}
}
treePointer CreateNode(char data) {
	treePointer temp = (treePointer)malloc(sizeof(tNode));
	temp->data = data;
	temp->leftchild = NULL;
	temp->rightchild = NULL;
	return temp;
}
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftchild);
		printf("%c", toupper(ptr->data));
		inorder(ptr->rightchild);
	}
}
void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", toupper(ptr->data));
		preorder(ptr->leftchild);
		preorder(ptr->rightchild);
	}
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftchild);
		postorder(ptr->rightchild);
		printf("%c", toupper(ptr->data));
	}
}