#include<stdio.h>
#include<stdlib.h>
#define INPUT 0
#define HEAD 1
typedef struct edge* edgePointer;
typedef struct edge {
	int vertex1;
	int vertex2;
	edgePointer link1;
	edgePointer link2;
} tEdge;

edgePointer* adj_list;

edgePointer CreateEdge(int, int);
void AppendNode(edgePointer, int, int);
void PrintEdge(int, int);

int main(void) {
	FILE* fp = fopen("input.txt", "r");
	int vertex_size, edge_size;
	int vertex1, vertex2;
	edgePointer input;

	fscanf(fp, "%d %d", &vertex_size, &edge_size);

	adj_list = (edgePointer*)malloc(sizeof(edgePointer)*vertex_size);
	for (int i = 0; i < vertex_size; i++) {
		adj_list[i] = NULL;
	}

	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d", &vertex1, &vertex2);
		input = CreateEdge(vertex1, vertex2);
		AppendNode(input, vertex1, vertex2);
	}


	PrintEdge(vertex_size, INPUT);
	printf("\n");
	PrintEdge(vertex_size, HEAD);
	printf("\n");


}
void PrintEdge(int size, int choice) {
	edgePointer ptr;

	if (choice == INPUT) {
		printf("Order of the vertex : same as input\n");
		for (int i = 0; i < size; i++) {
			ptr = adj_list[i];
			printf("vertex %d : ", i);
			while (ptr) {
				printf("(%d, %d) ", ptr->vertex1, ptr->vertex2);
				if (i == ptr->vertex1) {
					ptr = ptr->link1;
				}
				else {
					ptr = ptr->link2;
				}
			}
			printf("\n");
		}
	}
	else if (choice == HEAD) {
		printf("Order of the vertex : head first\n");
		for (int i = 0; i < size; i++) {
			ptr = adj_list[i];
			printf("vertex %d : ", i);
			while(ptr) {
				if (i == ptr->vertex1) {
					printf("(%d, %d) ", ptr->vertex1, ptr->vertex2);
					ptr = ptr->link1;
				}
				else {
					printf("(%d, %d) ", ptr->vertex2, ptr->vertex1);
					ptr = ptr->link2;
				}	
			}
			printf("\n");
		}
	}
	else {
		fprintf(stderr, "wrong parameter\n");
		exit(EXIT_FAILURE);
	}
}
void AppendNode(edgePointer input, int ver1, int ver2) {
	edgePointer ptr;

	ptr = adj_list[ver1];
	if (ptr == NULL) {
		adj_list[ver1] = input;
	}
	else {
		while (1) {
			if (ptr->vertex1 == ver1) {
				if (!ptr->link1) {
					ptr->link1 = input;
					break;
				}
				else {
					ptr = ptr->link1;
				}
			}
			else {
				if (!ptr->link2) {
					ptr->link2 = input;
					break;
				}
				else {
					ptr = ptr->link2;
				}
			}
		}
	}


	ptr = adj_list[ver2];
	if (ptr == NULL) {
		adj_list[ver2] = input;
	}
	else {
		while (1) {
			if (ptr->vertex1 == ver2) {
				if (!ptr->link1) {
					ptr->link1 = input;
					break;
				}
				else {
					ptr = ptr->link1;
				}
			}
			else {
				if (!ptr->link2) {
					ptr->link2 = input;
					break;
				}
				else {
					ptr = ptr->link2;
				}
			}
		}
	}

}
edgePointer CreateEdge(int ver1, int ver2) {
	edgePointer temp = (edgePointer)malloc(sizeof(tEdge));
	temp->vertex1 = ver1;
	temp->vertex2 = ver2;
	temp->link1 = NULL;
	temp->link2 = NULL;
	return temp;
}