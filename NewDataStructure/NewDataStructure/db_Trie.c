#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
	//��-�� �ڽ�
	int child[2];
	//������ input Ȯ��
	int count;
} NODE;
//�丮�� ��ġ�� ����Ű�� ������
NODE* head;

//csize �� ���� �ʿ��� ������, size�� �� ������
int csize, size = 2;

void checksize() {

	//���� �ʿ��� �迭���� �۴ٸ� �� ū ũ���� �迭 �Ҵ�
	if (csize + 1 >= size) {
		head = (NODE*)realloc(head, sizeof(NODE) * size * 2);
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
		if (head[index].count < 1) return 0;
		if (head[index].child[cbit] == -1) return 0;
	
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
	int outdes = dup(1);

	//FILE* fp1 = fopen(argv[1], "r");
	//FILE* fp1 = fopen("input.txt", "r");
	//freopen("input.txt", "r",stdin);
	freopen(argv[1], "r",stdin);
	//FILE* fp2 = fopen("db_result.txt", "w");
	freopen("db_result.txt", "w", stdout);
	

	time_t start = clock(),end;
	head = (NODE*)malloc(sizeof(NODE) * size);
	initate(0);

	while(scanf("%c %d", &ch, &x)!=EOF) {
		while ((a = getchar()) != '\n');
		if (ch == 'i') Insert(x);
		else if (ch == 'd') { 
			if (Delete(x)) puts("ignore"); 
		}
		else if (ch == 's') {
			if (Search(x)) puts("true");
			else puts("false");
		}
	}	
	end = clock();
	stdout = fdopen(outdes, "w");

	//��� �� ������ ���� ����
	free(head);
	
	printf("%.6lf\n", (double)(end-start)/CLOCKS_PER_SEC);
	
	return 0;
}
