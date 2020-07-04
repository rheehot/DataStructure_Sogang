#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_string_size 100
#define max_pattern_size 100
int failure[max_pattern_size];
char str[max_string_size];
char pat[max_pattern_size];

int pmatch(char str[], char pat[]) {
	int i, j = 0;
	int lens = strlen(str);
	int lenp = strlen(pat);

	//str���� 0��°���� �����Ͽ� pat�� ���� ���ڸ� ã�� �˰���
	for (i = 0; i < lens; ++i) {
		while (str[i] != pat[j] && j > 0) j = failure[i - 1] + 1;
		/* ���ڰ� ���� �ʰ� pat�� index, j�� ������ ���� �ʴ� �� ���� ���������� ��ġ�ߴ� ���ڷ� ����*/
		if (str[i] == pat[j]) { //���ڰ� ���� ���
			if (j == lenp - 1) return i - lenp + 1;
			/*���� j�� pat�� ���̸�ŭ Ŀ�����ٸ� ������ ���ڿ��̶�� ���̱� ������ ������ġ ��ȯ*/
			else j++;
			//���� ���ڰ� �ƴ϶�� pat������ ���� ���ڷ� �̵�
		}
	}
	return -1; //���� ���ڿ��� ���ٸ� -1 ��ȯ
}

//pmatch�Լ����� ������ ���� ���ڿ������� Ȯ���ϴ� �迭�� ����� ���� fail�Լ�
void fail(char str[]) { 
	int i, j;
	int lens = strlen(str);

	for (j = 1; j < lens; ++j) { //j�� pat �迭�� ��ȸ�ϸ� ���̻�� ���λ��� ���� ���ϼ��� üũ�մϴ�.
		i = failure[j - 1]; //i = failure[j - 1]; //�� �� �迭�� ��ġ���� ����
		while (str[j] != str[i + 1] && i >= 0) i = failure[i];
		//���ڰ� �ٸ� ���, ���� ���������� ���� ���ڰ� �־��� index ����, ���� ��� -1 ��ġ ����
		if (str[j] == str[i + 1]) failure[j] = i + 1;
		//���ڰ� ������ ���, failure�� ���° ���ڰ� ���Ҵ����� ����
	}
}

int main(void) {
	FILE* fp = fopen("kmp.txt", "rt");

	if (!fp) {
		fprintf(stderr, "There is No File");
		return 0;
	}

	//fgets�Լ��� �̿��ؼ� ���๮�� �������� ���ڿ� �б�
	fgets(str, sizeof(str), fp);
	fgets(pat, sizeof(str), fp);


	//�Լ� ����
	fail(pat);
	int pos = pmatch(str, pat);
	printf("%d\n", pos);
}