#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct node* nodePtr;
typedef struct node {
	nodePtr leftChild,rightChild,parent;
	int key,cnt;
}node;
nodePtr root;

void rotate(nodePtr x);
void splay(nodePtr x);
void Insert(int key);
int search(int key);
void Delete(int key);

//x�� �������� ȸ��
void rotate(nodePtr x) {
	nodePtr p = x->parent; //ȸ���� ����� �θ� ���
	nodePtr b = NULL; // x ����� ���� �� �� ���� ��� ���� ����
	if (!p) return; //x�� ��Ʈ ����̸� ����
	
	/*x ��带 ��Ʈ ���� �̵���Ŵ*/
	if (x == p->leftChild) {
		p->leftChild = b = x->rightChild;
		x->rightChild = p;
	}
	else {
		p->rightChild = b = x->leftChild;
		x->leftChild = p;
	}

	//�θ� �缳��
	x->parent = p->parent;
	p->parent = x;
	if (b) b->parent = p;


	//���� Ʈ���� �θ� ����� �ڽ� ����
	if (x->parent) {
		if (p == x->parent->leftChild) {
			x->parent->leftChild = x;
		}
		else {
			x->parent->rightChild = x;
		}
	}
	else {
		root = x;
	}
}

void splay(nodePtr x) {
	/*x�� �θ� ���� x == x �� ��Ʈ�� �� ������ �ݺ�*/
	while (x->parent) {
		nodePtr p = x->parent;
		nodePtr g = p->parent;
		
		/*g�� �����Ҷ� ���� �����ִٸ� RL Ȥ�� LR ȸ��*/
		if (g) {
			//zig-zig
			if ((x == p->leftChild) == (p == g->leftChild)) rotate(p);
		}
		//zig-zag
		else rotate(x);

		//zig
		rotate(x);
	}
}

void Insert(int key) {
	nodePtr p = root, * pp;
	nodePtr x = (nodePtr)malloc(sizeof(node));
	x->key = key;
	x->cnt = 1;
	x->leftChild->rightChild->parent = NULL;

	if (!p) {
		root = x;
		return;
	}

	while (1) {
		if (key == p->key) {
			free(x);
			return;
		}
		//Ű ���� �� ���� ���
		if (key < p->key) {
			//���� ��ġ�� ã���� ��
			if (!p->leftChild) {
				pp = &p->leftChild;
				break;
			}
			p = p->leftChild;
		}
		else {
			//���� ��ġ�� ã���� ��
			if (!p->rightChild) {
				pp = &p->rightChild;
				break;
			}
			p = p->rightChild;
		}
	}

	//��带 �ʿ��� ��ġ�� ����
	*pp = x;
	x->parent = p;
	splay(x);
}

int search(int key) {
	nodePtr p = root;
	//�����Ͱ� ���� ���
	if (!p) return 0;
	while (p) {
		if (key == p->key) break;
		if (key < p->key) {
			if (!p->leftChild) break;
			p = p->leftChild;
		}
		else {
			if (!p->rightChild) break;
			p = p->rightChild;
		}
	}
	splay(p);
	return key == p->key;
}

void Delete(int key) {
	/*if (!search(key)) {
		printf("ignore\n");
		return;
	}*/
	nodePtr p = root;
	nodePtr x;
	if (p->leftChild) {
		//���� ������ ��� �����ϴ� ���
		if (p->rightChild) {
			/*���� ������ ��尡 �ֻ�� ��忡 ����*/
			root = p->leftChild;
			root->parent = NULL;
			/*���ʿ��� ���� ū ���� ã�� ��*/
			x = root;
			while (x->rightChild) x = x->rightChild;
			/*�� ���� root�� �� ��尡 Ʈ�� �ֻ������ �ö�*/
			x->rightChild = p->rightChild;
			p->rightChild->parent = x;
			splay(x);
			free(p);
			return;
		}

		/*�ڽ��� �ϳ��̰ų� ���� ��� �׳� �������ָ� ��*/
		root = p->leftChild;
		root->parent = NULL;
		free(p);
		return;
	}
	/*�����ʿ� �ڽ��� �ϳ��� ���*/
	if (p->rightChild) {
		root = p->rightChild;
		root->parent = NULL;
		free(p);
		return;
	}

	/*������ ����� ���*/
	free(p);
	root = NULL;
}

int main(void) {
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	char op;
	int x;
	while (1) {
		fscanf(fp1, "%c", &op);
		if (op == EOF) break;
		fscanf(fp1, "%d", &x);

		if (op == 'i') {
			if (search(x)) (root->cnt)++;
			else insert(x);
		}
		else if (op == 'd') {
			if (search(x)) {
				(root->cnt)--;
				if (root->cnt == 0) Delete(x);
			}
			else {
				printf("ignore\n");
			}
		}
		else if (op == 's') {
			if (search(x)) {
				printf("true\n");
			}
			else {
				printf("false\n");
			}
		}
	}
}