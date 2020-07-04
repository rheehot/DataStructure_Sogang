#define _CRT_OBSOLETE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

//���� �ٲٴ� �Լ�
void swap(long long* a, long long* b) {
	long long temp = *a;
	*a = *b;
	*b = temp;
}

//��������
void selectSort(long long* d, int n) {
	int i, j=0;
	for (i = 0; i < n - 1; ++i) {
		int min = i;
		for (j = i + 1; j < n; ++j) {
			_sleep(1); // �ð� ������ ����
			if (d[min] > d[j]) min = j;
		}
		swap(&d[min], &d[i]);
	}

	//��º�
	cout << "Output : ";
	for (i = 0; i < n; ++i) {
		cout << d[i];
		if (i != n - 1) cout << " ";
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ifstream File("lab1.dat");
	ofstream out("result1.dat");
	clock_t start,end;

	//���� Ȯ��
	if (!File) {
		cout << "NOT OPEN" << '\n';
		return 0;
	}

	//���� ���� �ð� ���� �˰���
	for (int n = 1; n <= 100; ++n) {
		cout << "Input : ";
		long long* d = new long long[n+1];
		for (int i = 0; i < n; ++i) {
			File >> d[i];
			cout << d[i];
			if (i != n - 1) cout << ' ';
		}
		cout << '\n';


		//�Լ� ����, �ð� ����
		start = clock();
		selectSort(d, n);
		
		// �۵� �ð� �ʴ��� ���
		double temp = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		out << temp<<'\n';
		cout << '\n'<<"Time : "<< temp << "s"<<'\n'<<'\n';
		delete(d);
	}
}