#include "RangeArray.h"

/* �˰��� : �迭�� �Ҵ��� �޴� �Ͱ� ������ ���� Array Ŭ������ ����� �̿��ϵ�
   ȣ��� ����ϴ� ���ڸ� ������ ���� ȣ��*/
RangeArray::RangeArray(int low, int high) 
	: Array(high-low+1){ 
	//�迭�� �Ҵ��� high-low+1 ���·� Array Ŭ�������� �Ҵ��ߴ��Ͱ� �����ϰ� �� ĭ �� �߰�
	this->low = low;
	this->high = high;
}

RangeArray::~RangeArray() {}

int RangeArray::baseValue() {
	return low;
}
int RangeArray::endValue() {
	return high;
}

/*�迭�� Ư�� �ε��� ������ ���� ȣ���� �ε����� ������ ������ ���� �Ű������� ����
  �̷��� �����ν�, Array Ŭ������ ����� �״�� �̿��ϵ�, �ڵ�� �� ��������*/
int& RangeArray::operator[](int index) {
	return Array::operator[] (index - low);
}
int RangeArray::operator[](int index) const {
	return Array::operator[] (index - low);
}