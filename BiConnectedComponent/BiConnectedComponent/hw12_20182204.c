#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define MIN2(x,y) ((x)<(y)?(x):(y))
short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
int num;
int n; //sizeof graph


typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	struct node* link;
}node;
nodePointer graph[MAX_VERTICES];

typedef struct stack {
	int current;
	int nextNode;
	struct stack* next;
}stack;

typedef stack* stackPointer;
stackPointer head;

void init();
void bicon(int, int);

int main(void) {

	nodePointer temp;
	nodePointer* cNode;
	char ch;


	freopen("input.txt","r",stdin);

	scanf("%d", &n);
	getchar();


	for (int i = 0; i < n; ++i) {
		cNode = &graph[i];

		getchar();
		while ((ch=getchar()) != '\n' && ch!=EOF) {
			if (ch == ' ') continue;

			temp = (node*)malloc(sizeof(node));
			temp->vertex = ch-'0';
			temp->link = NULL;

			/*��� ��尡 ����ִ� ���*/
			if (graph[i] == NULL) {
				*cNode = temp;
			}
			/*��� ��尡 ������� ���� ��*/
			else {
				(*cNode)->link = temp;
				cNode = &(*cNode)->link;
			}
		}
	}

	init();
	bicon(0, -1);


	printf("\nDFN : ");
	for (int i = 0; i < n; ++i) {
		printf("%d ", dfn[i]);
	}

	printf("\nLOW : ");
	for (int i = 0; i < n; ++i) {
		printf("%d ", low[i]);
	}
}


/*���Ḯ��Ʈ�� ������ ������ push*/
void push(int current, int nextNode) {
	stackPointer temp = (stackPointer)malloc(sizeof(stack));
	temp->current = current;
	temp->nextNode = nextNode;

	/*head �� ����ִ� ���*/
	if (head == NULL) {
		temp->next = NULL;
		head = temp;
	}
	/*���ÿ� ��� �ϳ��� ���� �� �ִ� ���*/
	else {
		temp->next = head;
		head = temp;
	}
}

/*���ÿ��� ���� ���ʿ� �ִ� ������ �̾Ƴ���*/
void pop(int *x, int *y) {
	stackPointer chead = head;

	/*x�� y�� �ֻ�� ������ ������ �����մϴ�.*/
	*x = chead->current;
	*y = chead->nextNode;

	head = head->next;
	free(chead);
}

/*��� dfn�� low�� -1 �׸��� dfn �� ī��Ʈ�� num �� 0���� �ʱ�ȭ �մϴ�.*/
void init() {
	int i;
	for (i = 0; i < n; ++i) {dfn[i] = low[i] = -1;}
	num = 0;
}

void dfnlow(int u, int v) {
	nodePointer ptr;
	int w;
	dfn[u] = low[u] = num++;

	for (ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		if (dfn[w] < 0) {
			dfnlow(w, u);
			low[u] = MIN2(low[u], low[w]);
		}
		else if (w != v) {
			low[u] = MIN2(low[u], dfn[w]);
		}
	}
}

/*current ������ �θ� ����� ��� ���� ������ �Լ��� �����մϴ�. */
void bicon(int current, int ancestor) {
	nodePointer ptr;
	/*w : x : y : */
	int nextNode, x, y;

	/*�켱������ dfn�� low�� ���� ���Դϴ�.*/
	dfn[current] = low[current] = num++;

	for (ptr = graph[current]; ptr; ptr = ptr->link) {
		nextNode = ptr->vertex;

		/*���� �湮�� ��尡 ������ �湮�� ��尡(ex> 2 : 1-4 �� �̾��� �ֱ⿡ 2-1 �� �������� �ʽ��ϴ�.)
		�ƴϸ鼭 �� ���� ��尡 �湮���� ���� ��� ����*/
		if (ancestor != nextNode && dfn[nextNode] < dfn[current]) {
			push(current, nextNode);

			/*���� �湮���� ��� �ΰ�� ���� ���� DFS*/
			if (dfn[nextNode] < 0) {
				bicon(nextNode, current);

				/*DFS �� ������ ���� : �״��� ���� ���� ����� dfn �񱳽� �״��� ����� dfn�� �� ū ���*/
				/*�˰��򿡼� min(low(w)) �� �ش��ϴ� �κ�*/
				low[current] = MIN2(low[current], low[nextNode]);

				/*low[nextNode] >= dfn[current] �� ���� ����Ŭ�� ����ų� Articulation Point �� ����̱� ����*/
				/*�˰��򿡼� low(u) = min{low(u),min{low(w)},min{dfn(w)}} �� �ش��ϴ� �κ�*/
				if (low[nextNode] >= dfn[current]) {
					printf("NEW biconnexted component :");

					/*�θ� ���������� ��� ������ָ� �ϳ��� BCC�� �����ϰ� �˴ϴ�.*/
					do {
						pop(&x, &y);
						printf(" <%d, %d>", x, y);
					} while (!((x == current) && (y == nextNode)));
					printf("\n");
				}
			}
			/*���� ��尡 �湮�߰�, �� ��尡 ���� ��尡 �ƴ� ��� : 
			Back Edge�̱� ������ Back Edge�� Ÿ�� �ö� ���� ���� dfn�� ã�� low[current]�� ����*/
			//�˰��򿡼� min{dfn(w) | (u,w)�� �� ����} �� �ش��ϴ� �κ�
			else if (nextNode != ancestor) low[current] = MIN2(low[current], dfn[nextNode]); 
		}
	}
}