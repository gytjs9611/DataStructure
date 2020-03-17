#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define INF 99999

typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	int weight;
	nodePointer link;
} tNode;

typedef struct element {
	int vertex, weight;
} element;

nodePointer** adjList;
int* distance;
int* previous;
int* flag;

nodePointer CreateNode(int, int);
void AppendNode(int, int, int);
void PrintAdjList(int);

void Dijkstra(int);

void AddHeap(element*, element, int);
element DeleteHeap(element*, int);
void SiftDown(element*, int, int);

void PrintPath(int, int, int);

int main(void) {
	FILE* fp = fopen("input.txt", "r");
	int vertex_size, edge_size;
	int vertex1, vertex2, weight;

	fscanf(fp, "%d %d", &vertex_size, &edge_size);

	adjList = (nodePointer**)malloc(sizeof(nodePointer*)*vertex_size);
	flag = (int*)malloc(sizeof(int)*vertex_size);
	distance = (int*)malloc(sizeof(int)*vertex_size);
	previous = (int*)malloc(sizeof(int)*vertex_size);

	for (int i = 0; i < vertex_size; i++) {
		adjList[i] = (nodePointer*)malloc(sizeof(nodePointer) * 2);
		adjList[i][0] = NULL;
		flag[i] = FALSE;
		distance[i] = INF;
		previous[i] = -1;
	}


	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d %d", &vertex1, &vertex2, &weight);
		AppendNode(vertex1, vertex2, weight);
	}
	PrintAdjList(vertex_size);
	printf("\n");

	printf("<<< Dijkstra >>>\n");
	Dijkstra(vertex_size);
	for (int i = 1; i < vertex_size; i++) {
		PrintPath(vertex_size, 0, i);
	}

}
void Dijkstra(int size){
	element* Heap = (element*)malloc(sizeof(element)*(size+1));
	element node;
	int heap_size = 0;
	int u, v, w;
	nodePointer ptr;

	distance[0] = 0;

	node.vertex = 0;
	node.weight = distance[0];
	AddHeap(Heap, node, ++heap_size);

	while (heap_size>0) { // delete할 게 있어야하니까
		node = DeleteHeap(Heap, heap_size--);
		u = node.vertex;
		if (!flag[u]) { // ★ 빼먹지 말기!!!!!!
			ptr = adjList[u][0];
			while (ptr) {
				v = ptr->vertex; w = ptr->weight;
				//printf("v = %d ", v);
				if (!flag[v] && distance[v] > distance[u] + w) {
					distance[v] = distance[u] + w;
					previous[v] = u;
					node.vertex = v; node.weight = distance[v];
					AddHeap(Heap, node, ++heap_size);
				}
				ptr = ptr->link;
			}
			flag[u] = TRUE;
		}
		
	}


}
void PrintPath(int size, int src, int dst) {
	int* result = (int*)malloc(sizeof(int)*size);
	int top = -1;
	int tmp = dst;
	printf("distance[0-%d] = %-2d : ", dst, distance[dst]);

	while (tmp != -1) {
		result[++top] = tmp;
		tmp = previous[tmp];
	}

	for (int i = top; i >= 0; i--) {
		printf("%d %s ", result[i], i == 0 ? "" : "->");
	}
	printf("\n");
}
void AddHeap(element* Heap, element data, int heap_size) {
	int cur = heap_size;
	int parent = cur / 2; // ★ parent는 나누기 2 해야함!!!

	Heap[heap_size] = data;

	while (cur > 1) { // cur가 1이되면 그냥 끝임
		if (Heap[parent].weight > Heap[cur].weight) {
			Heap[cur] = Heap[parent];
			Heap[parent] = data;
		}
		else {
			break;
		}
		cur = parent;
		parent = cur / 2;
	}
}
element DeleteHeap(element* Heap, int heap_size) {
	element keyout = Heap[1];
	Heap[1] = Heap[heap_size];
	Heap[heap_size] = keyout;
	SiftDown(Heap, 1, heap_size - 1);
	return keyout;
}
void SiftDown(element* Heap, int index, int heap_size) {
	element siftkey = Heap[index];
	int cur = index;
	int child = 2 * cur;

	while (child <= heap_size) {
		if (child == heap_size) {
			child++;
		}
		else if (Heap[child].weight > Heap[child + 1].weight) {
			child++;
		}
		
		if (Heap[child].weight < siftkey.weight) {
			Heap[cur] = Heap[child];
			Heap[child] = siftkey;
			cur = child;
			child = 2 * cur;
		}
		else {
			break;
		}
	}
	
}
void AppendNode(int ver1, int ver2, int weight) {
	nodePointer node1, node2;
	node1 = CreateNode(ver1, weight);
	node2 = CreateNode(ver2, weight);

	if (!adjList[ver1][0]) {
		adjList[ver1][0] = node2;
	}
	else {
		adjList[ver1][1]->link = node2;
	}
	adjList[ver1][1] = node2;

	if (!adjList[ver2][0]) {
		adjList[ver2][0] = node1;
	}
	else {
		adjList[ver2][1]->link = node1;
	}
	adjList[ver2][1] = node1;
}
nodePointer CreateNode(int ver, int weight) {
	nodePointer temp = (nodePointer)malloc(sizeof(*temp));
	temp->vertex = ver;
	temp->weight = weight;
	temp->link = NULL;
	return temp;
}
void PrintAdjList(int size) {
	nodePointer ptr;
	printf("<<< AdjList >>>\n");
	for (int i = 0; i < size; i++) {
		ptr = adjList[i][0];
		printf("%2d : ", i);
		while (ptr) {
			printf("(%d, %d) ", ptr->vertex, ptr->weight);
			ptr = ptr->link;
		}
		printf("\n");
	}
}