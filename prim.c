#include<stdio.h>
#include<stdlib.h>
#define INF 99999
#define TRUE 1
#define FALSE 0

typedef struct node* nodePointer;
typedef struct node {
	int vertex, weight;
	nodePointer link;
} tNode;

typedef struct element {
	int vertex, weight;
} element;

nodePointer** adjList;
int* distance;
int* previous;
int* flag;

void AppendNode(int, int, int);
nodePointer CreateNode(int, int);

void Prim();
element DeleteHeap(element*, int);
void InsertHeap(element*, element, int);
void SiftDown(element*, int, int);

int main(void) {
	FILE* fp = fopen("input.txt", "r");
	int vertex_size, edge_size;
	int vertex1, vertex2, weight;

	fscanf(fp, "%d %d", &vertex_size, &edge_size);
	adjList = (nodePointer**)malloc(sizeof(nodePointer*)*vertex_size);
	distance = (int*)malloc(sizeof(int)*vertex_size);
	previous = (int*)malloc(sizeof(int)*vertex_size);
	flag = (int*)malloc(sizeof(int)*vertex_size);

	for (int i = 0; i < vertex_size; i++) {
		adjList[i] = (nodePointer*)malloc(sizeof(nodePointer)*2);
		adjList[i][0] = NULL;
		distance[i] = INF;
		previous[i] = -1;
		flag[i] = FALSE;

	}
	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d %d", &vertex1, &vertex2, &weight);
		AppendNode(vertex1, vertex2, weight);
	}
	/*for (int i = 0; i < vertex_size; i++) {
		nodePointer ptr = adjList[i][0];
		printf("%d : ", i);
		while (ptr) {
			printf("(%d %d) ", ptr->vertex, ptr->weight);
			ptr = ptr->link;
		}
		printf("\n");
	}*/

	Prim();

	int sum = 0;
	for (int i = 1; i < vertex_size; i++) {
		sum += distance[i];
	}
	printf("result = %d\n", sum);


}
void Prim() {
	element heap[100];
	int heap_size = 0;
	int u, v, w;
	element node;
	nodePointer ptr;

	distance[0] = 0;
	node.vertex = 0;
	node.weight = distance[0];

	InsertHeap(heap, node, ++heap_size);

	while (heap_size > 0) {
		u = DeleteHeap(heap, heap_size--).vertex;
		if (!flag[u]) { // ¡Ú »©¸ÔÁö ¸»±â!!!!!!!!!!!!
			ptr = adjList[u][0];
			while (ptr) {
				v = ptr->vertex, w = ptr->weight;
				if (!flag[v] && distance[v] > w) {
					distance[v] = w;
					previous[v] = u;
					node.vertex = v;
					node.weight = distance[v];
					InsertHeap(heap, node, ++heap_size);
				}
				ptr = ptr->link;
			}
			flag[u] = TRUE;
			printf("selected vertex = %d\n", u);
			for (int i = 0; i < 7; i++) {
				if (distance[i] == INF) {
					printf("INF ");
				}
				else {
					printf("%d ", distance[i]);
				}
			}
			printf("\n");

		}
		
	}

}
element DeleteHeap(element* H, int size) {
	element keyout = H[1];
	H[1] = H[size];
	H[size] = keyout;
	SiftDown(H, 1, size - 1);
	return keyout;
}
void InsertHeap(element* H, element data, int size) {
	int cur = size;
	int parent = cur / 2;

	while (cur > 1) {
		if (data.weight < H[parent].weight) {
			H[cur] = H[parent];
		}
		else {
			break;
		}
		cur = parent;
		parent = cur / 2;
	}
	H[cur] = data;
}
void SiftDown(element* H, int index, int size) {
	element siftkey = H[index];
	int parent = index;
	int child = 2 * parent;

	while (child <= size) {
		
		if (child!=size && H[child].weight > H[child + 1].weight) {
			child++;
		}

		if (H[child].weight < siftkey.weight) {
			H[parent] = H[child];
		}
		else {
			break;
		}
		parent = child;
		child = parent * 2;
	}
	H[parent] = siftkey;
}
void AppendNode(int src, int dst, int weight) {
	nodePointer node1, node2;
	node1 = CreateNode(src, weight);
	node2 = CreateNode(dst, weight);

	if (!adjList[src][0]) {
		adjList[src][0] = node2;
	}
	else {
		adjList[src][1]->link = node2;
	}
	adjList[src][1] = node2;

	if (!adjList[dst][0]) {
		adjList[dst][0] = node1;
	}
	else {
		adjList[dst][1]->link = node1;
	}
	adjList[dst][1] = node1;
}
nodePointer CreateNode(int ver, int weight) {
	nodePointer tmp = (nodePointer)malloc(sizeof(tNode));
	tmp->vertex = ver;
	tmp->weight = weight;
	tmp->link = NULL;
	return tmp;
}
