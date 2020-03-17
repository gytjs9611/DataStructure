/* MST(Minimum Spanning Tree) */
/* 
Spanning Tree
연결 그래프의 부분 그래프로서 그 그래프의 모든 정점과 간선의 부분 집합으로 구성되는 트리. 
모든 노드는 적어도 하나의 간선에 연결되어 있어야 한다.
Tree의 특징은 cycle이 없다는 것인데, 이를 만족시키려면 n-1개의 간선이 필요하다.
*/
#include<stdio.h>
#include<stdlib.h>
#define INF 99999

typedef struct element {
	int vertex1, vertex2;
	int weight;
} element;

element* input;
int top = -1;
int* distance;
int* parent;

void Sort(int);
void PrintEdges(int);
void Kruskal(int, int);

int CollapsingFind(int);
void WeightedUnion(int, int);


int main(void) {
	FILE* fp;
	int vertex_size, edge_size;
	int vertex1, vertex2, weight;
	element node;

	if (!(fp = fopen("input.txt", "r"))) {
		fprintf(stderr, "cannot open the file\n");
	}
	fscanf(fp, "%d %d", &vertex_size, &edge_size);

	input = (element*)malloc(sizeof(element)*edge_size);
	distance = (int*)malloc(sizeof(int)*vertex_size);
	parent = (int*)malloc(sizeof(int)*vertex_size);

	for (int i = 0; i < vertex_size; i++) {
		distance[i] = INF;
		parent[i] = -1;
	}

	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d %d", &vertex1, &vertex2, &weight);
		node.vertex1 = vertex1, node.vertex2 = vertex2, node.weight = weight;
		input[++top] = node;
	}
	Sort(edge_size);
	printf("<<< Sorted Edges >>>\n");
	PrintEdges(edge_size);

	printf("\n<<< Kruskal's Algorithm >>>\n");
	Kruskal(vertex_size, edge_size);


}
void Kruskal(int ver_size, int edge_size) {
	int u, v, w;
	int root1, root2;
	int num_of_edge = 0;
	int sum = 0;

	for (int i = 0; i < edge_size; i++) {
		u = input[i].vertex1;
		v = input[i].vertex2;
		w = input[i].weight;

		root1 = CollapsingFind(u);
		root2 = CollapsingFind(v);

		if (root1 != root2) {
			WeightedUnion(root1, root2); // ★ root끼리 합친다는 사실 잊지말기
			printf("(%d, %d) %d\n", u, v, w);
			sum += w;

			if (++num_of_edge == ver_size - 1) { // ★ 삽입된 edge의 개수가 vertex수-1 이면 종료
				break;
			}
		}

	}

	// ★ Spanning Tree는 모든 정점이 연결되어있어야하므로 최소 n-1개의 edge를 가짐
	// Tree는 Cycle이 없어야 함, edge가 n-1개를 초과하는 순간 cycle이 생기므로 종료해야함
	// n-1개보다 적으면 모든 간선이 연결되지 못하기 때문에 스패닝트리를 찾을  수 없게 됨
	if (num_of_edge < ver_size - 1) {
		printf("No spanning tree\n");
		exit(1);
	}

	printf("최소비용 = %d\n", sum);
}
int CollapsingFind(int vertex) {
	int i;
	int index, root;
	int temp;

	/*for (i = vertex; parent[i] >= 0; i = parent[i]);
	root = i;*/

	index = vertex;
	while (parent[index]>=0) {
		index = parent[index];
	}
	root = index;
	
	/*while (vertex != root) {
		parent[vertex] = root;
		vertex = parent[vertex];
	}*/
	// ★ 이렇게 하면 vertex의 parent값만 바뀌고 종료됨

	while (vertex != root) {
		temp = parent[vertex];
		parent[vertex] = root;
		vertex = temp;
	} // ★ 이렇게 해야 vertex->root로 가는 경로상의 모든 vertex의 parent 값이 바뀜


	return root;
}
void WeightedUnion(int root1, int root2) {
	int temp = parent[root1] + parent[root2];

	if (parent[root1] < parent[root2]) {
		parent[root2] = root1;
		parent[root1] = temp;
	}
	else {
		parent[root1] = root2;
		parent[root2] = temp;
	}
}
void Sort( int size) {
	element temp;

	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (input[i].weight > input[j].weight) {
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}
	}
}
void PrintEdges(int size) {
	element ptr;
	for (int i = 0; i < size; i++) {
		ptr = input[i];
		printf("%d %d %d\n", ptr.vertex1, ptr.vertex2, ptr.weight);
	}
}