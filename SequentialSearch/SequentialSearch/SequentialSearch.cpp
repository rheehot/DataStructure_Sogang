#define _CRT_OBSOLETE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ofstream out("lab1.data"); //������ ���� ��ġ
	clock_t start, end; //�ð� ���� �Լ�
	int len; //���� �Ҵ�� �迭 ����

	cout << "Input: ";
	cin >> len;

	while (len) { //len�� 0�� �ƴ� �̻� ���α׷� ����
		long long* d = new long long[len + 1]; // �����Ҵ� �迭 ����
		int snum;
		for (int i = 0; i < len; ++i) {
			d[i]= rand() % len; // ���ڴ� ������ len ������ ���ڸ� �Է�
		}

		//ã���� �ϴ� �� �˻�
		cout << "Search number: ";
		cin >> snum;

		//�Լ� ����
		start = clock();
		int index = -1; // ���� ã�� ���� ���ٸ� -1 ���
		for (int i = 0; i < len; ++i) {
			_sleep(0.1); //�۵��ð��� ������ ������ ���� ������ �Լ� �߰�
			if (d[i] == snum) {
				index = i;
				break;
			}
		}

		//�Լ� ��� ���
		cout << "Searched: " << index<<'\n';
		end = clock();
		cout << "Time: " << ((double)(end - start)) / CLOCKS_PER_SEC<<"sec \n";
		out << ((double)(end - start)) / CLOCKS_PER_SEC<<"\n";

		//��ó��
		delete(d);
		cout << "Input: ";
		cin >> len;
	}
}