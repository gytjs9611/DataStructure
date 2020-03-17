#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 100

typedef enum {
	lparen, rparen, and, not, or, operand, eos
} precedence;

int icp[] = { 10, 0, 1, 2, 1, 0, 0 }; // precedence 선언 개수랑 꼭 맞추기!!!
int isp[] = { 0, 0, 1, 2, 1, 0, 0 };

FILE* ff;
char result[MAX];
int result_top = -1;

precedence stack[MAX];
int top = -1;

void InfixToPostfix(char);
precedence ReturnType(char);
char ToChar(precedence);
void PushOperator(precedence);
precedence PopOperator();

int main(void) {
	FILE* fp = fopen("input.txt", "r");
	char input;

	stack[++top] = eos;

	while (!feof(fp)) {
		fscanf(fp, "%c", &input);
		if (feof(fp)) {
			break;
		}
		InfixToPostfix(input);
	}

	while (stack[top]!=eos) {
		result[++result_top] = ToChar(PopOperator());
	}
	
	for (int i = 0; i <= result_top; i++) {
		printf("%c", result[i]);
	}
	printf("\n");

}
void InfixToPostfix(char data) {
	precedence data_type = ReturnType(data);
	precedence temp;

	if (data_type==operand) { // operand
		result[++result_top] = data;
	}
	else { // operator
		if (data_type == rparen) {
			while ((temp=PopOperator())!=lparen) {
				result[++result_top] = ToChar(temp);
			}
			return;
		}
		if (isp[stack[top]] < icp[data_type]) { // isp[top] <= icp[data_type] 으로 자꾸 실수하네;;;;;;;;; '<='가 아니고 '<'임!!!!
			PushOperator(data_type);
		}
		else {
			temp = PopOperator();
			result[++result_top] = ToChar(temp);
			PushOperator(data_type);
		}
	}

}
void PushOperator(precedence data) {
	if (top == MAX - 1) {
		fprintf(stderr, "Stack is Full, cannot push an element\n");
		exit(EXIT_FAILURE);
	}
	else {
		stack[++top] = data;
	}
}
precedence PopOperator() {
	if (top == -1) {
		fprintf(stderr, "Stack is Empty, cannot pop an element\n");
		exit(EXIT_FAILURE);
	}
	else {
		return stack[top--];
	}
}
precedence ReturnType(char data) {
	switch (data) {
	case '(' :
		return lparen;
	case ')' :
		return rparen;
	case '&':
		return and;
	case '|':
		return or;
	case '~':
		return not;
	default :
		return operand;
	}
}
char ToChar(precedence data) {
	switch (data) {
	case lparen:
		return '(';
	case rparen:
		return ')';
	case and:
		return '&';
	case or:
		return '|';
	case not:
		return '~';
	}
}