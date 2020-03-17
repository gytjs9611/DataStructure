/* MST(Minimum Spanning Tree) */
/* 
Spanning Tree
���� �׷����� �κ� �׷����μ� �� �׷����� ��� ������ ������ �κ� �������� �����Ǵ� Ʈ��. 
��� ���� ��� �ϳ��� ������ ����Ǿ� �־�� �Ѵ�.
Tree�� Ư¡�� cycle�� ���ٴ� ���ε�, �̸� ������Ű���� n-1���� ������ �ʿ��ϴ�.
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
			WeightedUnion(root1, root2); // �� root���� ��ģ�ٴ� ��� ��������
			printf("(%d, %d) %d\n", u, v, w);
			sum += w;

			if (++num_of_edge == ver_size - 1) { // �� ���Ե� edge�� ������ vertex��-1 �̸� ����
				break;
			}
		}

	}

	// �� Spanning Tree�� ��� ������ ����Ǿ��־���ϹǷ� �ּ� n-1���� edge�� ����
	// Tree�� Cycle�� ����� ��, edge�� n-1���� �ʰ��ϴ� ���� cycle�� ����Ƿ� �����ؾ���
	// n-1������ ������ ��� ������ ������� ���ϱ� ������ ���д�Ʈ���� ã��  �� ���� ��
	if (num_of_edge < ver_size - 1) {
		printf("No spanning tree\n");
		exit(1);
	}

	printf("�ּҺ�� = %d\n", sum);
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
	// �� �̷��� �ϸ� vertex�� parent���� �ٲ�� �����

	while (vertex != root) {
		temp = parent[vertex];
		parent[vertex] = root;
		vertex = temp;
	} // �� �̷��� �ؾ� vertex->root�� ���� ��λ��� ��� vertex�� parent ���� �ٲ�


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