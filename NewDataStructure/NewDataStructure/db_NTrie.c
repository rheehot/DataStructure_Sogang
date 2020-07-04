#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	//��-�� �ڽ�
	int child[2];
	//������ input Ȯ��
	int count;
} NODE;
typedef NODE* NODEPtr;
//�丮�� ��ġ�� ����Ű�� ������
NODEPtr head;

//csize �� ���� �ʿ��� ������, size�� �� ������
int csize, size = 2;

void checksize() {

	//���� �ʿ��� �迭���� �۴ٸ� �� ū ũ���� �迭 �Ҵ�
	if (csize + 1 >= size) {
		head = (NODEPtr)realloc(head, sizeof(NODE) * size * 2);
		size *= 2;
	}
}

//�迭 �ʱ�ȭ : ���� ��ġ��
void initate(int cPos) {
	checksize();
	head[cPos].child[0] = head[cPos].child[1] = -1;
	head[cPos].count = 0;
}

//������ ��Ʈ ���� Ʈ���� �������� ������ Ž��
int Search(int data) {
	int cbit, index = 0, i;
	for (i = 31; i >= 0; i--) {
		cbit = (data >> i) & 1;

		//���� �ڽ��� �ϳ��� -1�� �ִٸ� �ش� ���ڴ� ���� ������ ����
		if (head[index].child[cbit] == -1) return 0;
		if (head[index].count < 1) return 0;
		index = head[index].child[cbit];
	}

	//�ڽ� �� �ϳ��� �ִٸ� ������ �ε����� 0���� ū ����
	return 1;
}

void Insert(int data) {
	int i,index = 0,cbit;

	for (i = 31; i >= 0; i--) {

		//��Ʈ�� 31��°���� 0���� ���� �˻��ϸ� child Ž��
		cbit = (data >> i) & 1;


		//���� �ڽ��� �ʱ�ȭ ���� ���� ��� - ũ�� ���� �� �ڽ���ġ ����
		if (head[index].child[cbit] == -1) {
			checksize();
			initate(++csize);

			head[csize].count++;
			index = head[index].child[cbit] = csize;
		}
		//�̹� �ڽ��� ������ ��� �� ���� �ڽ����� �̵�
		else {
			head[index].count++;
			index = head[index].child[cbit];
		}
	}
}

int Delete(int data) {
	//�� ã�� ���
	if (!Search(data)) {
		return 1;
	}

	//ã�� ��� - �ڽĵ��� �������� count �� ���̱�
	int  i,cbit, index = 0;
	for (i = 31; i >= 0; i--) {
		cbit = (data >> i) & 1;
		index = head[index].child[cbit];
		head[index].count--;
	}
	return 0;
}

int main(int argc,char *argv[]) {
	char ch,a;
	int x;
	csize = 0;

	FILE* fp1 = fopen(argv[1], "r");
	FILE* fp2 = fopen("db_result.txt", "w");
	

	time_t start = clock();
	head = (NODE*)malloc(sizeof(NODE) * size);
	initate(0);

	while(fscanf(fp1,"%c %d\n", &ch, &x)!=EOF) {
		if (ch == 'i') Insert(x);
		else if (ch == 'd') { if (Delete(x)) fprintf(fp2, "ignore\n");}
		else if (ch == 's') {
			if (Search(x)) fprintf(fp2, "true\n");
			else fprintf(fp2, "false\n");
		}
	}	

	fclose(fp1);
	fclose(fp2);

	//��� �� ������ ���� ����
	free(head);

	printf("%.6lf\n", (double)(clock()-start)/CLOCKS_PER_SEC);
	
	return 0;
}
