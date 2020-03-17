#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
} tNode;

nodePointer* graph;
int* flag;

void AppendNode(int, int);
nodePointer CreateNode(int);

void DFS(int);
void PrintDFS(int);
void InitFlag(int);

int main(void) {
	FILE* fp = fopen("input.txt", "r");
	int vertex_size, edge_size;
	int vertex1, vertex2;

	fscanf(fp, "%d %d", &vertex_size, &edge_size);
	graph = (nodePointer*)malloc(sizeof(nodePointer)*vertex_size);
	flag = (int*)malloc(sizeof(int)*vertex_size);

	for (int i = 0; i < vertex_size; i++) {
		graph[i] = NULL;
		flag[i] = FALSE;
	}
	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d", &vertex1, &vertex2);
		AppendNode(vertex1, vertex2);
	}

	/*for (int i = 0; i < vertex_size; i++) {
		printf("%d : ", i);
		nodePointer ptr = graph[i];
		while (ptr) {
			printf("%d ", ptr->vertex);
			ptr = ptr->link;
		}
		printf("\n");
	}*/

	PrintDFS(vertex_size);


}
void DFS(int i) {
	nodePointer ptr = graph[i];
	int v;

	printf("%d ", i);
	flag[i] = TRUE;

	while (ptr) {
		v = ptr->vertex;
		if (!flag[v]) {
			DFS(v);
		}
		ptr = ptr->link;
	}
}
void PrintDFS(int size) {
	for (int i = 0; i < size; i++) {
		printf("DFS(%d) : ", i);
		InitFlag(size);
		DFS(i);
		printf("\n");
	}
}
void InitFlag(int size) {
	for (int i = 0; i < size; i++) {
		flag[i] = FALSE;
	}
}
void AppendNode(int ver1, int ver2) {
	nodePointer node1, node2;
	node1 = CreateNode(ver1);
	node2 = CreateNode(ver2);

	if (!graph[ver1]) {
		graph[ver1] = node2;
	}
	else {
		node2->link = graph[ver1];
		graph[ver1] = node2;
	}

	if (!graph[ver2]) {
		graph[ver2] = node1;
	}
	else {
		node1->link = graph[ver2];
		graph[ver2] = node1;
	}
}
nodePointer CreateNode(int data) {
	nodePointer tmp = (nodePointer)malloc(sizeof(*tmp));
	tmp->vertex = data;
	tmp->link = NULL;
	return tmp;
}