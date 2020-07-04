#include<stdio.h>
#include<stdlib.h>

typedef struct threadedTree* threadedPointer;

typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
}threadedTree;

void construct_tree(threadedPointer tree);
threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void insertRight(threadedPointer s, threadedPointer r);
void insert(threadedPointer s, char data);

int main(){
	/* initialize a head node */
	// type your code 
	threadedPointer root = (threadedPointer)malloc(sizeof(threadedTree));

	//root ����� �������� ������ �ڱ��ڽ��� ����Ű���� �ʱ�ȭ
	root->rightThread = 1;
	root->rightChild = root;

	/* ��� E�� C������, F�� D ������, G�� B�� D ���̿� ���� */
	construct_tree(root);
	insert(root->leftChild->rightChild, 'E');
	insert(root->leftChild->leftChild->rightChild, 'F');
	insert(root->leftChild->leftChild, 'G');

	/* ���� ��ȸ ��� */
	tinorder(root);
	getchar();
	return 0;
}

void construct_tree(threadedPointer tree)
{
	threadedPointer temp, temp_root;

	temp_root = tree;
	/* A�� root ���� ��忡 �߰� */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = 1;
	temp->leftChild = temp->rightChild = temp;
	temp->data = 'A';

	temp_root->leftChild = temp;
	temp_root->leftThread = 0;

	temp_root = tree->leftChild;
	/* B�� A ���� ��忡 �߰� */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->rightThread = temp->leftThread = 1;
	temp->leftChild = tree;
	temp->rightChild = temp;
	temp->data = 'B';

	temp_root->leftChild = temp;
	temp_root->leftThread = 0;

	/* C�� A ������ ��忡 �߰� */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = 1;
	temp->leftChild = temp_root;
	temp->rightChild = tree;
	temp->data = 'C';

	temp_root->rightChild = temp;
	temp_root->rightThread = 0;

	temp_root = temp_root->leftChild;
	/* D�� B ������ ��忡 �߰� */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = 1;
	temp->leftChild = temp_root;
	temp->rightChild = tree->leftChild;
	temp->data = 'D';

	temp_root->rightChild = temp;
	temp_root->rightThread = 0;
}

threadedPointer insucc(threadedPointer tree){
	threadedPointer temp = tree->rightChild;

	//�����ʿ� �ڽ��� �ִ� == ������ �����尡 ������ �ִ�.
	if (!tree->rightThread) {
		//���ʿ� �ڽ��� �ִ�. == ���� �����尡 ������ �ִ�.
		while (!temp->leftThread) {
			//��� �������� �������鼭 �� ���� ��带 ã��.
			temp = temp->leftChild;
		}
	}
	
	//ã�Ƴ� �� ���� ��带 ��ȯ
	return temp;
}

void tinorder(threadedPointer tree){

	//inoder ��ȸ�� ���� ���� ���� �ڽ��� ã�� ������
	threadedPointer temp=tree->leftChild;
	while (!temp->leftThread) temp = temp->leftChild;

	for(;;) {
		//���������� root�� �����Ͽ��ٸ� root�� ������ �ڽ��� �ڱ��ڽ�
		if (temp == tree) break;
		//�� ���� ����� ���� ���
		printf("%3c", temp->data);
		//��� �� ���� ��带 ã���� ������
		temp = insucc(temp);
	}
}

void insert(threadedPointer s, char d){
	/*�� ��带 �����Ҵ� �� �ʱ�ȭ�ϰ� insertRight �Լ� ȣ��*/
	threadedPointer temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->data = d;
	insertRight(s, temp);
}

void insertRight(threadedPointer s, threadedPointer r){
	threadedPointer temp;
	
	/*�ڽ� ����� ������� �ڽ� �ʱ�ȭ*/
	//�������� �θ��� ������ �ڽ��� ����Ű����
	r->rightThread = s->rightThread;
	r->rightChild = s->rightChild;
	
	//������ �θ� ����Ű����
	r->leftThread = 1;
	r->leftChild = s;

	//�θ� ����� ������ �ڽ��� ���� ���� �߰��� �ڽ� ���
	s->rightChild = r;
	s->rightThread = 0;


	//�θ� ����� ���� ������ �ڽ��� ���� ���� ���� ���� �߰��� ��带 ����Ű�� �ϱ�
	if (!r->rightThread) {
		temp = insucc(r);
		temp->leftChild = r;
	}

}
