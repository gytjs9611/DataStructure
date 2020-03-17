#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

// ★ 방문한 뒤 큐에 넣는 방식으로 진행

typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
} tNode;

nodePointer* adjList;
nodePointer front, rear;
int* visited;

void AppendNode(int, int);
nodePointer CreateNode(int);

void InitArray(int*, int);
void AddQueue(int);
nodePointer DeleteQueue();
void BFS(int);

int main(void) {
	FILE* fp = fopen("input.txt", "r");
	int vertex_size, edge_size;
	int vertex1, vertex2;

	fscanf(fp, "%d %d", &vertex_size, &edge_size);
	adjList = (nodePointer**)malloc(sizeof(nodePointer*)*vertex_size);
	visited = (int*)malloc(sizeof(int)*vertex_size);
	for (int i = 0; i < vertex_size; i++)
	{
		adjList[i] = NULL;
		visited[i] = FALSE;
	}


	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d", &vertex1, &vertex2);
		AppendNode(vertex1, vertex2);
	}
	for (int i = 0; i < vertex_size; i++) {
		nodePointer ptr = adjList[i];
		printf("%d : ", i);
		while (ptr) {
			printf("%d ", ptr->vertex);
			ptr = ptr->link;
		}
		printf("\n");
	}

	for (int i = 0; i < vertex_size; i++) {
		InitArray(visited, vertex_size);
		printf("BFS(%d) : ", i);
		BFS(i);
		printf("\n");
	}


}
void BFS(int i) {
	int u, v;
	nodePointer node;
	nodePointer ptr;

	front = NULL, rear = NULL;

	printf("%d ", i);
	visited[i] = TRUE;
	AddQueue(i);
	// ★ 방문한 뒤 큐에 넣는 방식으로 진행

	while (front) { // while queue is not empty
		u = DeleteQueue()->vertex;
		ptr = adjList[u];
		while (ptr) {
			v = ptr->vertex;
			if (!visited[v]) {
				printf("%d ", v);
				visited[v] = TRUE;
				AddQueue(v);
			}
			ptr = ptr->link;
		}
	}

}
void AddQueue(int ver) {
	nodePointer data = CreateNode(ver);
	if (!front) {
		front = data;
	}
	else {
		rear->link = data;
	}
	rear = data;
}
nodePointer DeleteQueue() {
	nodePointer temp = front;
	if (!temp) {
		fprintf(stderr, "Queue is empty, cannot delete data");
		exit(EXIT_FAILURE);
	}
	else {
		front = front->link;
	}
	return temp;
}
void InitArray(int* array, int size) {
	for (int i = 0; i < size; i++)
	{
		array[i] = FALSE;
	}
}
void AppendNode(int ver1, int ver2) {
	nodePointer node1 = CreateNode(ver1);
	nodePointer node2 = CreateNode(ver2);

	if (!adjList[ver1]) {
		adjList[ver1] = node2;
	}
	else {
		node2->link = adjList[ver1];
	}
	adjList[ver1] = node2;


	if (!adjList[ver2]) {
		adjList[ver2] = node1;
	}
	else {
		node1->link = adjList[ver2];
	}
	adjList[ver2] = node1;
}
nodePointer CreateNode(int ver) {
	nodePointer temp = (nodePointer)malloc(sizeof(*temp));
	temp->vertex = ver;
	temp->link = NULL;
	return temp;
}