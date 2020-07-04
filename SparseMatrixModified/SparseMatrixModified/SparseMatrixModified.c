/*
FastTranspose�� msub�� ���Ḯ��Ʈ ���·� �����ϴ� ���� ��ƴ�.
�׷��� ������ ������ ���Ḯ��Ʈ�� �Ǿ� �ִ� ������ �����ϰ�
������ �迭������ Matrix�� FastTranspose�� msub�� �̿��ϴ� ����
�ξ� �ӵ��鿡�� ������ ���ϴ�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101

typedef enum { head, entry }tagfield;
typedef struct matrix_node* matrix_pointer;

//�Ϲ� ��� ����ü
typedef struct entry_node {
	int row;
	int col;
	int value;
}entry_Node;

//��ũ�帮��Ʈ ����ü
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;

	//�߰��� �κ�
	/*entry_Node�� ����� �������� mSub�� mtranspose�� ����� �� �̷������ ������*/
	entry_Node* mT;


	union {
		matrix_pointer next; //head �϶� ���
		entry_Node entry; //node �϶� ���
	}u;
}matrixNode;


matrix_pointer hdnode[MAX_SIZE];

/*������ ����� ������ �迭�� ��ġ�� �Լ�*/
entry_Node* matrixRead(FILE* fp) {
	/*������ �迭 node*/
	entry_Node* node = (entry_Node*)malloc(sizeof(entry_Node) * (MAX_SIZE));
	int rows, cols, i, j, val, cnt = 0;

	//�⺻ rows�� cols �о����
	fscanf(fp, "%d %d", &rows, &cols);

	node[0].row = rows;
	node[0].col = cols;
	node[0].value = 0;

	//2���� �࿭�� �ϳ��� ���鼭 ī��Ʈ����
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			fscanf(fp, "%d", &val);

			//�о ���� 0�� �ƴ϶�� ������ �迭�� �߰�
			if (val != 0) {
				node[0].value++;
				node[node[0].value].row = i;
				node[node[0].value].col = j;
				node[node[0].value].value = val;
			}
		}
	}

	//������� ������ �迭 ��ȯ
	return node;
}

//���ο� matrixNode �����Ҵ� ������ ��ȯ�ϴ� �Լ�
matrix_pointer new_node() {
	return (matrix_pointer)malloc(sizeof(matrixNode));
}

matrix_pointer mMake(matrix_pointer node, entry_Node* preT) {
	int num_rows, num_cols, num_terms = 0, num_heads, i;
	int row, col, value, current_row;
	matrix_pointer temp, last;

	/*������� ������ �迭 ��ȯ*/
	entry_Node* t = preT;
	num_rows = t[0].row; num_cols = t[0].col; num_terms = t[0].value;

	/*�� ū���� �������� ��� ��� ����Ʈ�� ����*/
	num_heads = (num_cols > num_rows) ? num_cols : num_rows;

	node->mT = t; // �߰��� �κ�


	node->tag = entry;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;

	if (!num_heads) node->right = node;
	else {
		/*��� ��� ����Ʈ�� ���� ��� ������ ���� �� �ʱ�ȭ*/
		for (i = 0; i < num_heads; i++) {
			temp = new_node();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next = temp;
		}

		//�� ���� ���� ��ġ �� ���� ������ ��带 ����Ű�� ���� �ʱ�ȭ
		current_row = 0;
		last = hdnode[0];

		/*������ sparse matrix�������� �����͸� �о�帮�� ���Ḯ��Ʈ�� ����*/
		for (i = 1; i <= num_terms; i++) {

			//������ �迭�� ���� ������ ���Ḯ��Ʈ�� ��� �̾��ֱ�
			row = node->mT[i].row; col = node->mT[i].col; value = node->mT[i].value;

			if (row > current_row) {
				last->right = hdnode[current_row];
				current_row = row; last = hdnode[row];
			}

			temp = new_node(); temp->tag = entry;
			temp->u.entry.row = row; temp->u.entry.col = col;
			temp->u.entry.value = value; last->right = temp; last = temp;
			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}

		// ���������� ������ �迭���� ���� ������ ����
		last->right = hdnode[current_row];
		for (i = 0; i < num_cols; i++)
			hdnode[i]->u.next->down = hdnode[i];

		for (i = 0; i < num_heads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];

		hdnode[num_heads - 1]->u.next = node;
		node->right = hdnode[0];
	}

	return node;
}

matrix_pointer mread(FILE* fp) {
	int num_rows, num_cols, num_terms = 0, num_heads, i;
	int row, col, value, current_row;
	matrix_pointer temp, last, node = NULL;

	/*������� ������ �迭 ��ȯ*/
	entry_Node* t = matrixRead(fp);

	/*���ο� ��带 ������� ���Ḯ��Ʈȭ �ϱ�*/
	node = new_node();
	node = mMake(node, t);
	
	return node;
}

// sparse matrix�� ����ϴ� �Լ�
void mwrite(matrix_pointer node) {
	int i;
	matrix_pointer temp, head = node->right;

	printf("\n numRows = %d, numCols = %d\n",
		node->u.entry.row, node->u.entry.col);

	/*�� ���� �� ������ ��� �� �� ���� ������ �̵� */
	for (i = 0; i < node->u.entry.row; i++) {
		for (temp = head->right; temp != head; temp = temp->right)
			printf("%5d%5d%5d \n",
				temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);

		/*�� ���� ��� ��µ� ��� �� ���� ������ �̵�*/
		head = head->u.next;
	}
}

/*��� ���Ḯ��Ʈ ������ �����ϴ� �Լ�*/
void merase(matrix_pointer* node) {
	int i, num_heads;
	matrix_pointer x, y, head = (*node)->right;

	/*�� ���� ��� ���� ���鼭 ��� ������ ��������*/
	for (i = 0; i < (*node)->u.entry.row; i++) {
		y = head->right;
		while (y != head) {
			x = y; y = y->right; free(x);
		}
		x = head; head = head->u.next; free(x);
	}

	// ���������� ���� ��� ������ ����
	y = head;
	while (y != *node) {
		x = y; y = y->u.next; free(x);
	}

	//entry ��带 ����
	free(*node);

	//������ ���� �� ��� �Ҵ�
	*node = new_node();
	node[0]->u.entry.row = node[0]->u.entry.col = 0;
}


/*
////////////////////////////////////////////
////////////////////////////////////////////
///         Subtraction Function         ///
////////////////////////////////////////////
////////////////////////////////////////////
*/
matrix_pointer msub(matrix_pointer nodeA, matrix_pointer nodeB) {
	//���� ������ �ٸ��ٸ� return 
	if (nodeA->mT[0].col != nodeB->mT[0].col || nodeA->mT[0].row != nodeB->mT[0].row) {
		fprintf(stderr, "Can't subtraction\n");
		return NULL;
	}


	//nodeA �� nodeB�� �ε����� �ϳ��� ������ ����
	int idxA, idxB,idxD;

	/*��� ������ ���� ��� ����. �ʱ�ȭ*/
	matrix_pointer d = new_node();
	d->mT = (entry_Node*)malloc(sizeof(entry_Node) * MAX_SIZE);

	d->mT[0].col = nodeA->mT[0].col;
	d->mT[0].row = nodeA->mT[0].row;


	/*
	1. nodeA�� nodeB�� �ప�� ���� �� ���� �ప�� ���� ����� ������ ���ο� ��� d�� ����
	2. nodeA�� nodeB�� ������ ���� �� ���� ������ ���� ���� ������ d�� ����
	3. ��� ���� ������
	 3-1. nodeA�� nodeB�� ���� d�� ����
	 3-2. nodeA�� nodeB�� ���� 0�̶�� �������� �ʰ� �� �������� �̵�
	*/
	for (idxA=1,idxB=1,idxD=1; idxA <= nodeA->mT[0].value && idxB<= nodeB->mT[0].value; idxD++) {

		/*���� ��ġ�� �ٸ� ���*/
		if (nodeA->mT[idxA].row < nodeB->mT[idxB].row) {
			d->mT[idxD].row = nodeA->mT[idxA].row;
			d->mT[idxD].col = nodeA->mT[idxA].col;
			d->mT[idxD].value = nodeA->mT[idxA].value;
			idxA++;
			continue;
		}
		else if (nodeA->mT[idxA].row > nodeB->mT[idxB].row) {
			d->mT[idxD].row = nodeB->mT[idxB].row;
			d->mT[idxD].col = nodeB->mT[idxB].col;
			d->mT[idxD].value = -(nodeB->mT[idxB].value);
			idxB++;
			continue;
		}


		/*���� ��ġ�� �ٸ� ���*/
		if (nodeA->mT[idxA].col < nodeB->mT[idxB].col) {
			d->mT[idxD].row = nodeA->mT[idxA].row;
			d->mT[idxD].col = nodeA->mT[idxA].col;
			d->mT[idxD].value = nodeA->mT[idxA].value;
			idxA++;
			continue;
		}
		else if (nodeA->mT[idxA].col > nodeB->mT[idxB].col) {
			d->mT[idxD].row = nodeB->mT[idxB].row;
			d->mT[idxD].col = nodeB->mT[idxB].col;
			d->mT[idxD].value = -(nodeB->mT[idxB].value);
			idxB++;
			continue;
		}

		/*��� ���� ��ġ�� ��ġ�ϴ� ���*/
		//���̰� 0�� �ƴ� �̻� ����
		if (((nodeA->mT[idxA].value) - (nodeB->mT[idxB].value)) != 0) {
			d->mT[idxD].row = nodeA->mT[idxA].row;
			d->mT[idxD].col = nodeA->mT[idxA].col;
			d->mT[idxD].value = ((nodeA->mT[idxA].value) - (nodeB->mT[idxB].value));
			idxA++;
			idxB++;
		}
		else {
			idxD--;
			idxA++;
			idxB++;
		}
	}



	/*���� ���� ��� ����*/
	while (idxA <= nodeA->mT[0].value) {
		d->mT[idxD].row = nodeA->mT[idxA].row;
		d->mT[idxD].col = nodeA->mT[idxA].col;
		d->mT[idxD].value = nodeA->mT[idxA].value;
		idxD++;
		idxA++;
	}

	while (idxB <= nodeB->mT[0].value) {
		d->mT[idxD].row = nodeB->mT[idxB].row;
		d->mT[idxD].col = nodeB->mT[idxB].col;
		d->mT[idxD].value = -(nodeB->mT[idxB].value);
		idxD++;
		idxB++;
	}

	/*��� d�� ���Ḯ��Ʈ�� ����*/
	d->mT[0].value = (idxD-1);
	d=mMake(d,d->mT);

	//���۵� sparse_matrix�� ��ȯ
	return d;
}


/*
////////////////////////////////////////////
////////////////////////////////////////////
///          Transpose Function          ///  
////////////////////////////////////////////
////////////////////////////////////////////
*/
void fastTranspose(matrix_pointer a, matrix_pointer b) {
	int rowTerms[MAX_SIZE], startingPos[MAX_SIZE];
	int i, j, numCols = a->mT[0].col, numTerms = a->mT[0].value;

	b->mT[0].row = numCols;
	b->mT[0].col = a->mT[0].row;
	b->mT[0].value = numTerms;

	if (numTerms > 0) { /*0�� �ƴ� ��쿡�� ����*/
		for (i = 0; i < numCols; ++i) rowTerms[i] = 0;
		for (i = 1; i <= numTerms; ++i) rowTerms[a->mT[i].col]++;

		startingPos[0] = 1;

		//��� ���� �� ��ġ�� ����
		for (i = 1; i < numCols; ++i) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		}

		//��� ���� transpose�� ���ο� ��� b�� ����
		for (i = 1; i <= numTerms; ++i) {
			j = startingPos[a->mT[i].col]++;
			b->mT[j].row = a->mT[i].col; 
			b->mT[j].col = a->mT[i].row;
			b->mT[j].value = a->mT[i].value;
		}
	}	
}


matrix_pointer mtranspose(matrix_pointer node) {
	/*Traspose �� ����� ���� ���ο� ��� ����*/
	matrix_pointer newMatrix = new_node();
	newMatrix->mT = (entry_Node*)malloc(sizeof(entry_Node) * MAX_SIZE);
	
	//fastTranspose Ȱ��
	fastTranspose(node, newMatrix);

	//���Ḯ��Ʈ SparseMatrix ����
	newMatrix=mMake(newMatrix,newMatrix->mT);
	
	//���۵� Matrix ��ȯ
	return newMatrix;
}




int main(void) {
	matrix_pointer a, b, d;// = new_node();

	FILE* fp1 = fopen("A.txt", "r");
	FILE* fp2 = fopen("B.txt", "r");

	/*Sparse Matrix*/
	a = mread(fp1);
	b = mread(fp2);
	mwrite(a);
	mwrite(b);


	d = msub(a, b);
	mwrite(d);
	merase(&d);
	d = mtranspose(a);
	
	/*�������ֽ� main������ mtranspose�� ����� �� �� ���⿡
	�� �κ��� �ּ��� ������ �ֽø� ����� ���� �� �����ʴϴ�.*/
	//mwrite(d);
	

	/*��� ��ġ*/
	mwrite(a);
	merase(&d);
	merase(&a);
	merase(&b);

	mwrite(a);
	mwrite(b);
	mwrite(d);

	return 0;
}