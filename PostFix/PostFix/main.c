#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EXPR_SIZE 100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }
precedence;

//���Ḯ��Ʈ�� ���� node ����ü
typedef struct node {
	precedence data;
	struct node* link;
}node;

//���Ḯ��Ʈ�� �����ϴ� ������
node* stack;

char expr[MAX_EXPR_SIZE]; //�������� ����� �迭

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 }; // ������ 3.6�� pp. 136 ����
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

//������ ��� �ִ��� Ȯ��
int IsEmpty() {
	return (stack->data == eos)? 1 : 0;
}

//�ֻ�� ��� ����, ���
precedence pop() {
	if (IsEmpty() == 1) return eos;

	precedence data = stack->data;
	node* temp = stack;
	stack = stack->link;

	free(temp);
	return data;
}

//�ֻ�� ��� ���
precedence top(void) {
	if (IsEmpty() == 0) return stack->data;
	else return eos;
}

//�����ڸ� ���ÿ� ����
void push(precedence d) {
	node* newNode = (node*)malloc(sizeof(node));

	//��ũ�� ����Ʈ�� �������� ������ �ִ� ��쿡�� ��� �Ҵ�
	if (newNode != NULL) {
		newNode->data = d;
		newNode->link = NULL;

		//�Ӹ� ������� Ȯ��
		if (stack != NULL) newNode->link = stack;

		stack = newNode;
	}
}

/*������ ���*/
void printToken(precedence t) {
	switch (t) {
	case lparen:
		printf("(");
		break;
	case rparen:
		printf(")");
		break;
	case plus:
		printf("+");
		break;
	case minus:
		printf("-");
		break;
	case times:
		printf("*");
		break;
	case divide:
		printf("/");
		break;
	case mod:
		printf("%");
		break;
	}
}

/*postfix�� ��ġ�� �Լ�*/
void postfix() {
	char symbol; //getToken���� switch �Ǻ� ����
	precedence token; //�о ���ڸ� ����
	int n = 0; //���� ���� ����

	//stack�� ���� ������ ��忡 eos ����
	push(eos);

	/*�Ź� �����Ŀ� �ִ� ���ڸ� �о����� ó��*/
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		//�׳� ���ڶ�� �ٷ� ���
		if (token == operand) printf("%c", symbol);
		//���ڰ� �ƴ� '('�� ���
		else if (token == rparen) {
			// ')' �� stack���� ���ö����� pop
			while (top(stack)!= lparen) {
				printToken(pop());
			}

			//������ ')' ���
			pop();

		//��ȣ�� �ƴ� �ٸ� �����ڵ�
		}else{
			//�켱������ ����� �迭�� �������� stack�� �ִ� ���� ���
			while (isp[top(stack)] >= icp[token]) {
				printToken(pop());
			}
			//�̹��� �о���� ���� push
			push(token);
		}
	}

	//���ÿ� �����ִ� ��� �����ڵ� ���
	while ((token = pop()) != eos) {
		printToken(token);
	}
	printf("\n");
}

//�����Ŀ��� �ϳ��� ���ĸ��� �������� �Լ�
precedence getToken(char* s, int* n) {
	*s = expr[(*n)++];
	switch (*s) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case ' ': return eos;
	default: return operand; // �ǿ�����
	}
}

/*���Ͽ��� �������� �о���� �Լ�*/
void rExpr(FILE* name, char* expr) {
	freopen(name, "r", stdin);

	char temp;
	int i = 0;

	//������ ��� �Է� ����
	while (scanf("%c", &temp) != EOF) {
		if (temp == ' ') continue;
		else expr[i++] = temp;
	}
	//���� �Է��� ����Ǿ����� �˸��� ��ĭ
	expr[i] = ' ';
}

/*�������� ���������� ����� ������ Ȯ���ϴ� �Լ�*/
int check() {
	int ans=0;

	// '(' �̸� +1 , ')' �̸� -1
	for (int i = 0; expr[i] != ' '; ++i) {
		if (expr[i] == '(') ans++;
		else if (expr[i] == ')') ans--;
	}

	//���� ans�� 0�� �ƴ϶�� ������ ���� �� ���� ���� �ǹ�
	return (ans == 0) ? 1 : 0;
}
int main(void) {
	rExpr("expr.txt",expr);
	if (!check()) printf("No Solution\n");
	else postfix();
}