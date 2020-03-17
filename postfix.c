#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> //isalpha �Լ� ��� ����
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

typedef struct tree* treePointer;
typedef struct tree {
	char data;
	treePointer leftchild, rightchild;
} tTree;

treePointer stack[MAX_STACK_SIZE];
int top = -1;

treePointer queue[MAX_QUEUE_SIZE];
int front = -1, rear = -1;
// front�� ���� ù��°�� �ٷ� ������ ����Ű����, rear�� ���� ������ �� ����Ű����

treePointer CreateNode(char);
void CreateBinTree(char);

void StackPush(nodePointer);
treePointer StackPop();

void AddQueue(nodePointer);
treePointer DeleteQueue();

void inorder(treePointer);
void preorder(treePointer);
void postorder(treePointer);

void IterativeInorder(treePointer);
void levelorder(treePointer);



int main(void) {
	FILE* fp = fopen("input.txt", "r");
	char input;
	treePointer root = NULL;
	
	while (!feof(fp)) {
		fscanf(fp, "%c", &input);
		if (feof(fp)) {
			break;
		}
		CreateBinTree(input);
	}

	root = StackPop();

	printf("inorder traversal : ");
	inorder(root);
	printf("\npreorder traversal : ");
	preorder(root);
	printf("\npostorder traversal : ");
	postorder(root);
	printf("\niterative inorder traversal : ");
	IterativeInorder(root);
	printf("\nlevelorder traversal : ");
	levelorder(root);
	printf("\n");

}
void CreateBinTree(char data) {
	treePointer new_node = CreateNode(data);

	if (isalpha(data)) { // operand�� ��� stack�� push
		StackPush(new_node);
	}
	else { // operator�� ��� stack�� �ִ� �� operand�� pop�Ͽ� child�� �ְ� stack�� push
		new_node->rightchild = StackPop();
		new_node->leftchild = StackPop();
		//printf("new_node = %c, right = %c, left = %c\n", new_node->rightchild->data, new_node->leftchild->data);
		StackPush(new_node);
	}

}
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftchild);
		printf("%c", ptr->data);
		inorder(ptr->rightchild);
	}
}
void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftchild);
		preorder(ptr->rightchild);
	}
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftchild);
		postorder(ptr->rightchild);
		printf("%c", ptr->data);
	}
}
void IterativeInorder(treePointer ptr) {

	while (1) {
		while (ptr) { // leftchild�� ��� ���ÿ� �־���
			StackPush(ptr);
			ptr = ptr->leftchild;
		}
		if (top == -1)
		{
			break;
		}
		ptr = StackPop(); // pop�ϰ� �� ����� rightchild�� ���ؼ� ���� �۾� �ݺ�
		printf("%c", ptr->data);
		ptr = ptr->rightchild;
	}
	


}
void levelorder(treePointer ptr) {
	
	AddQueue(ptr);
	while (front != rear) {
		ptr = DeleteQueue();
		printf("%c", ptr->data);
		if (ptr->leftchild) {
			AddQueue(ptr->leftchild);
		}
		if (ptr->rightchild) {
			AddQueue(ptr->rightchild);
		}
	}
}
void AddQueue(treePointer ptr) {
	rear = (rear + 1) % MAX_QUEUE_SIZE;

	if (rear == front) {
		fprintf(stderr, "Queue if Full, cannot add\n");
		exit(EXIT_FAILURE);
	}
	else {
		queue[rear] = ptr;
	}
}
treePointer DeleteQueue() { // ť�� FIFO!!!!!!!!!!!!!!!!! �̰� �Ǽ��ϳ�;

	if (front == rear) {
		fprintf(stderr, "Queue is Empty, cannot delete\n");
		exit(EXIT_FAILURE);
	}
	else {
		front = (front + 1) % MAX_QUEUE_SIZE;
		return queue[front];
	}
}
void StackPush(treePointer ptr) {
	if (top == MAX_STACK_SIZE - 1) {
		fprintf(stderr, "Stack is Full, Cannot add\n");
		exit(EXIT_FAILURE);
	}
	else {
		stack[++top] = ptr;
	}
}
treePointer StackPop() {
	if (top==-1) {
		fprintf(stderr, "Stack is empty, Cannot delete\n");
		exit(EXIT_FAILURE);
	}
	else {
		return stack[top--]; // --top���� �ʰ� ����;; �̰� �Ǽ��ϳ�;;
	}
}
treePointer CreateNode(char data) {
	treePointer tmp = (treePointer)malloc(sizeof(tTree));
	tmp->data = data;
	tmp->leftchild = NULL;
	tmp->rightchild = NULL;
	return tmp;
}