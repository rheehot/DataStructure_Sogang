#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
vector<int> failure;

int pmatch(string str, string pat) {
	int i, j=0;
	int lens = str.size();
	int lenp = pat.size();

	//str���� 0��°���� �����Ͽ� pat�� ���� ���ڸ� ã�� �˰���
	for (i = 0; i < lens; ++i) {
		while (str[i] != pat[j] && j > 0) j = failure[j - 1];
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
void fail(string pat) {
	int i, j=0;
	int lens = pat.size();

	for (i = 1;i < lens; ++i) { //j�� pat �迭�� ��ȸ�ϸ� ���̻�� ���λ��� ���� ���ϼ��� üũ�մϴ�.
		//i = failure[j - 1]; //�� �� �迭�� ��ġ���� ����
		while (pat[j] != pat[i] && j > 0) j = failure[j-1]; 
		//���ڰ� �ٸ� ���, ���� ���������� ���� ���ڰ� �־��� index ����, ���� ��� -1 ��ġ ����
		if (pat[j] == pat[i]) failure[i] = ++j;
		//���ڰ� ������ ���, failure�� ���° ���ڰ� ���Ҵ����� ����
	}
}

int main(void){
	ifstream file("kmp.txt");

	if (!file) {
		fprintf(stderr, "There is No File");
		return 0;
	}

	string str;
	string pat;

	//getline�Լ��� �̿��ؼ� ���๮�� �������� ���ڿ� �б�
	getline(file, str);
	getline(file, pat);
	
	// vector �Լ��� failure�� �ʿ��� ������� ����
	failure.resize(pat.size(),0);

	//�Լ� ����
	fail(pat);
	int pos = pmatch(str, pat);
	cout << pos << '\n';
}