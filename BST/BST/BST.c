#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TERMS 100

typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
}treeNode;

void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);

/*Remove�� ���� �Լ���*/
treePtr RemoveLeftSubTree(treePtr bt);
treePtr RemoveRightSubTree(treePtr bt);
void ChangeLetSubTree(treePtr main, treePtr sub);
void ChangeRightSubTree(treePtr main, treePtr sub);
int CheckLevel(treePtr bt);
treePtr delete(treePtr* pRoot, int target);

/*ascending�� ���� �Լ���*/
void rangeSearch(treePtr, int, int);

int main(void) {
	int i, n, A[MAX_TERMS];
	treePtr tree = NULL;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	for (i = 0; i < n; ++i) {fscanf(fp, "%d", &A[i]);}

	for (i = 0; i < n; ++i) {insert(&tree, A[i]);}

	/*�ϼ� �� Ʈ�� ���*/
	printf("inorder : ");
	inorder(tree);
	printf("\npreorder : ");
	preorder(tree);

	/*2 ���� ����*/
	delete(&tree, 2);
	printf("\ninorder : ");
	inorder(tree);
	printf("\npreorder : ");
	preorder(tree);

	/*5 ���� ����*/
	delete(&tree, 5);
	printf("\ninorder : ");
	inorder(tree);
	printf("\npreorder : ");
	preorder(tree);

	/*�������� ���*/
	printf("\nascending : ");
	rangeSearch(tree, 3, 10);
}

void inorder(treePtr tree) {
	if (tree) {
		inorder(tree->lchild);
		printf("%d ", tree->data);
		inorder(tree->rchild);
	}
}

void rangeSearch(treePtr tree, int s, int e) {
	/*start ���� end ������ ū ���*/
	if (s > e) {
		fprintf(stderr, "Start is over than end number\n");
		return;
	}
	/*�׿��� ���� inorder �Լ��� �״�� �����ϴ�.*/
	if (tree) {
		rangeSearch(tree->lchild, s, e);
		if(tree->data>=s && tree->data<=e) printf("%d ", tree->data);
		rangeSearch(tree->rchild, s, e);
	}
}

void preorder(treePtr tree) {
	if (tree) {
		printf("%d ", tree->data);
		preorder(tree->lchild);
		preorder(tree->rchild);
	}
}

treePtr modifiedSearch(treePtr tree, int data) {
	treePtr temp = NULL;
	while (tree) {
		temp = tree;
		//���� ������
		if (data < tree->data) tree = tree->lchild;
		else if (tree->data < data) tree = tree->rchild;
		//���� ���� ���� NULLL
		else if (tree->data == data) return NULL;
	}
	//��带 ������ ���� �θ� ��带 ��ȯ
	return temp;
}

void insert(treePtr* tree, int data) {
	treePtr ptr; //��� ������
	treePtr temp = modifiedSearch(*tree, data); //���� ��ġ Ž���� �Լ�

	//tree�� NULL �̰ų� temp ��ġ�� ã�� ��� ����
	if (!(*tree) || temp) {
		/*��� ����, �ʱ�ȭ*/
		ptr = (treePtr)malloc(sizeof(treeNode));
		ptr->data = data;
		ptr->lchild = ptr->rchild = NULL;


		//Ʈ���� ��尡 �����ϴ� ���
		if (*tree) {
			if (data < temp->data) temp->lchild = ptr;
			else temp->rchild = ptr;
		}
		//Ʈ���� ��尡 �������� �ʴ� ���
		else *tree = ptr;
	}
}


/*/////////////////////////
//// Remove Function ////
/////////////////////////*/

/*���� ��带 �����ϴ� ����*/
treePtr RemoveLeftSubTree(treePtr bt) {
	treePtr dNode=NULL;

	if (bt != NULL) {
		dNode = bt->lchild;
		bt->lchild = NULL;
	}
	return dNode;
}

/*������ ��带 �����ϴ� ����*/
treePtr RemoveRightSubTree(treePtr bt) {
	treePtr dNode=NULL;

	if (bt != NULL) {
		dNode = bt->rchild;
		bt->rchild = NULL;
	}
	return dNode;
}

/*���� ��带 �ٲٴ� ����*/
void ChangeLetSubTree(treePtr main, treePtr sub) {
	main->lchild = sub;
}

/*������ ������ �ٲٴ� ����*/
void ChangeRightSubTree(treePtr main, treePtr sub) {
	main->rchild = sub;
}

/*Ʈ���� ��� ���� Ȯ���ϴ� �Լ�*/
int CheckLevel(treePtr bt) {
	int max = 0;

	/*NULL �ΰ�� �������� �����߱� ������ return 1*/
	if (bt == NULL) {
		return 1;
	}
	/*���ʰ� ������ ���� ��� �̵��ϸ� ����� ���� �����ϰ� ��ȯ�մϴ�.*/
	max += CheckLevel(bt->lchild);
	max += CheckLevel(bt->rchild);
	return max;
}

/*���� �Լ�*/
treePtr delete(treePtr* pRoot, int target) {
	/*pRoot �Լ��� �����Ǵ� ��츦 ���� pRoot �� ����Ű�� ������*/
	treePtr pVRoot = (treePtr)malloc(sizeof(treeNode));

	/*cNode�� root ����̰� pNode�� cNode�� ���� �� ����� �θ� ���*/
	treePtr pNode = pVRoot;
	treePtr cNode = *pRoot;
	/*dNode�� �����Ǵ� ��带 ����ŵ�ϴ�.*/
	treePtr dNode;

	/*�ڽ��� �ϳ��϶��� ���� ������*/
	treePtr dcNode;

	/*�ڽ��� �ΰ� �϶��� ���� ������*/
	int r;
	int lMax;
	int rMax;
	treePtr mNode;
	treePtr mpNode;
	int delData;

	/*���� ����� �����ʿ� root ��带 ���� �����մϴ�.*/
	ChangeRightSubTree(pVRoot, *pRoot);

	/*���ϴ� ��带 ã�� ������ Ʈ���� �������ϴ�.*/
	while (cNode!=NULL && cNode->data != target) {
		pNode = cNode;
		if (target > cNode->data) cNode = cNode->rchild;
		else cNode = cNode->lchild;
	}
	
	/*ã�� ���ߴٸ� ���� �޽����� ����մϴ�.*/
	if (cNode == NULL) {
		fprintf(stderr, "\nThere is No removable date : %d",target);
		return NULL;
	}

	/*���� ��� dNode�� ã�Ƴ� ��� cNode�� �����ϰ� ������ �����մϴ�.*/
	dNode = cNode;

	/*�ڽ��� �ΰ��� ���� leaf Node �� ���*/
	if (dNode->lchild == NULL && dNode->rchild == NULL) {
		/*�ڽ� ��常 �ٲپ��ִ� ������ �����մϴ�.*/
		if (pNode->lchild == dNode) RemoveLeftSubTree(pNode);
		else RemoveRightSubTree(pNode);
	}
	/*�ڽ� �� �ϳ��� �ִ� ���*/
	else if (dNode->lchild == NULL || dNode->rchild == NULL) {

		/*���� �Ǵ� ����� ��/�� ��带 ���� ������ �Ӵϴ�.*/
		if (dNode->lchild != NULL) dcNode = dNode->lchild;
		else dcNode = dNode->rchild;

		/*dNode �� �θ��忡 dNode�� �ڽ��� ���Դϴ�.*/
		if (pNode->lchild == dNode) ChangeLetSubTree(pNode, dcNode);
		else ChangeRightSubTree(pNode, dcNode);
	}
	/*�ڽ��� ��� �ִ� ���*/
	else {
		/*�켱������ �¿� ����Ʈ���� ������ Ȯ���մϴ�.*/
		lMax = CheckLevel(dNode->lchild);
		rMax = CheckLevel(dNode->rchild);

		mpNode = dNode;

		/*�޿� �� ������ ��ġ�� �����ϴ� �˰���*/
		//1. ���ʰ� ������ �ڽ��� subtree�� ���� ��� ��������
		if (lMax == rMax) {
			srand((unsigned int)time(NULL));
			r = rand() % 2;
			mNode = (r == 0) ? dNode->lchild : dNode->rchild;
		}
		/*�� ��尡 ���� ���� �������� �����Ǵ� ��忡 �� ��带 ã���ϴ�.*/
		else { 
			mNode = (lMax > rMax) ? dNode->lchild : dNode->rchild; 
		}

		/*�������� �������� ��� ���� ū ���� ã�Ƽ� Ʈ���� �������ϴ�*/
		if (mNode == dNode->lchild) {
			while (mNode->rchild != NULL) {
				mpNode = mNode;
				mNode = mNode->rchild;
			}

			delData = dNode->data;
			dNode->data = mNode->data;

			/*ã�� ����� ���� �ڽ��� mpNode�� ��/���� ���Դϴ�.*/
			if (mpNode->lchild == mNode) ChangeLetSubTree(mpNode, mNode->lchild);
			else ChangeRightSubTree(mpNode, mNode->lchild);
		}
		/*���������� �������� ��� ���� ���� ���� ã�Ƽ� Ʈ���� ������*/
		else {
			while (mNode->lchild != NULL) {
				mpNode = mNode;
				mNode = mNode->lchild;
			}

			delData = dNode->data;
			dNode->data = mNode->data;

			/*ã�� ����� ������ �ڽ��� mpNode�� ��/���� ���Դϴ�.*/
			if (mpNode->lchild == mNode) ChangeLetSubTree(mpNode, mNode->rchild);
			else ChangeRightSubTree(mpNode, mNode->rchild);
		}

		/*���� �����Ǵ� ��带 �����ִ� ���� �ƴϱ� ������ dNode�� �ű� ��带 �־��ݴϴ�.*/
		dNode = mNode;
		dNode->data = delData;
	}

	/*���������� ���� root ��尡 ������ ��쿡�� ���� Ʈ���� ��Ʈ�� ó�� �������� ���� ���� �ٲپ� �ݴϴ�.*/
	if (pVRoot->rchild != *pRoot) *pRoot = pVRoot->rchild;
	free(pVRoot);
	return dNode;
}
