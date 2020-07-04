#include "Array.h"

Array::Array(int size) {
	data = new int[size+1];
	len = size;
}

Array::~Array() {
}

int Array::length() const {
	return len;
}
/*������ �����ε��� �Ű������� �迭�� ũ�⸦ ���� ���
  �����޽����� �Բ� �Ϻη� ����� ���� �迭�� ������ ��ġ�� ��ȯ�Ѵ�
  �� ���� ��쿡 ���ؼ��� ����ڰ� ��û�ϴ� �ε��� ��ġ�� ��ȯ*/
int& Array::operator[](int index) {
	if (index < 0 || index >= len) {
		cout << "Array bound error!\n";
		return data[len+1];
	}
	return *(data + index);
}

int Array::operator[] (int index) const {
	if (index < 0 || index >= len) {
		cout << "Array bound error!\n";
		return data[len+1];
	}
	return data[index];
}

//�迭�� ó������ ������ ���
void Array::print() {
	cout << "[ ";
	for (int i = 0; i < len; ++i) {
		cout << data[i] << ' ';
	}
	cout << "]" << '\n';
}