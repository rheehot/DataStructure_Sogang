#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ll long long

typedef struct node* nodePtr;
typedef struct node {
	nodePtr leftChild, rightChild, parent;
	ll data;
	int count;
}node;
nodePtr root;

void rotate(nodePtr x);
void splay(nodePtr x);
void insert(int data);
int search(int data);
void deleteNode(int data);

//x�� �������� ȸ��
void rotate(nodePtr x) {
	nodePtr p = x->parent; //ȸ���� ����� �θ� ���
	nodePtr b = NULL; // x ����� ���� �� �� ���� ��� ���� ����
	if (!p) return; //x�� ��Ʈ ����̸� ����

	if (x == p->leftChild) {
		p->leftChild = b = x->rightChild;
		x->rightChild = p;
	}
	else {
		p->rightChild = b = x->leftChild;
		x->leftChild = p;
	}

	x->parent = p->parent;
	p->parent = x;
	if (b) b->parent = p;

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
	while (x->parent) {
		nodePtr p = x->parent;
		nodePtr g = p->parent;

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

int modifiedsearch(int data) {
	nodePtr p = root;
	if (!p) return 0;

	while (p) {
		if (data == p->data) return 1;
		if (data < p->data) {
			if (!p->leftChild) break;
			p = p->leftChild;
		}
		else {
			if (!p->rightChild) break;
			p = p->rightChild;
		}
	}

	return 0;
}

int search(int data) {
	nodePtr p = root;
	if (!p) return 0;

	while (p) {
		if (data == p->data) break;
		if (data < p->data) {
			if (!p->leftChild) break;
			p = p->leftChild;
		}
		else {
			if (!p->rightChild) break;
			p = p->rightChild;
		}
	}

	splay(p);
	return data == p->data;
}

void insert(int data) {
	nodePtr p = root, * pp;
	nodePtr x = (nodePtr)malloc(sizeof(node));
	x->data = data;
	x->count = 1;
	x->leftChild=x->rightChild=x->parent = NULL;

	if (!p) {
		root = x;
		return;
	}

	while (1) {
		if (data == p->data) {
			p->count++;
			free(x);
			return;
		}
		if (data < p->data) {
			if (!p->leftChild) {
				pp = &p->leftChild;
				break;
			}
			p = p->leftChild;
		}
		else {
			if (!p->rightChild) {
				pp = &p->rightChild;
				break;
			}
			p = p->rightChild;
		}
	}

	*pp = x;
	x->parent = p;
	splay(x);
}



void deleteNode(int data) {
	nodePtr p = root;
	nodePtr x;
	if (p->leftChild) {
		if (p->rightChild) {
			root = p->leftChild;
			root->parent = NULL;
			x = root;
			while (x->rightChild) x = x->rightChild;
			x->rightChild = p->rightChild;
			p->rightChild->parent = x;
			splay(x);
			free(p);
			return;
		}

		root = p->leftChild;
		root->parent = NULL;
		free(p);
		return;
	}
	if (p->rightChild) {
		root = p->rightChild;
		root->parent = NULL;
		free(p);
		return;
	}

	free(p);
	root = NULL;
}

int main(int argc,char * argv[]) {
	FILE* fp1 = fopen(argv[1], "r");
	//FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("db_result.txt", "w");

	char op;
	int x;
	clock_t start_time = clock();
	while (1) {
		if ((op = fgetc(fp1)) == EOF) break;
		fscanf(fp1,"%d", &x);


		//���� �ߺ� �����Ͷ�� ����� count ���� ����
		if (op == 'i') {
			insert(x);
		}
		//�����͸� ã�� ���� ������ ã�� �������� ������ 0�̶�� ����
		else if (op == 'd') {
			if (search(x)) {
				(root->count)--;
				if (root->count == 0) deleteNode(x);
			}
			else {
				fprintf(fp2,"ignore\n");
			}
		}
		//������ ã��
		else if (op == 's') {
			if (modifiedsearch(x)) {
				fprintf(fp2,"true\n");
			}
			else {
				fprintf(fp2,"false\n");
			}
		}
	}
	printf("%lf\n", (double)(clock()- start_time) / CLOCKS_PER_SEC);

	fclose(fp1);
	fclose(fp2);
}