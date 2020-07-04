#ifndef __RANGE_ARRAY_H__
#define __RANGE_ARRAY_H__
#include "Array.h"

class RangeArray :public Array {
protected:
	int low; //�迭�� ù���� �ε��� ����
	int high; //�迭�� ������ �ε��� ����
public:
	RangeArray(int, int); 
	//�迭�� ������ high-low+1 ��ŭ ArrayŬ������ �����ڸ� ȣ���Ͽ� �����Ҵ�, 
	//������ �� �� �� �߰��ϴ� ������ ���� �ε����� �Ѿ�� ��ġ�� ���� �䱸�� ��� ��ȯ�� ������ ������ ����
	~RangeArray();
	//�����Ҵ� ������ �����ϴ� �Լ�

	int baseValue(); //low���� ��ȯ�ϴ� �Լ�
	int endValue(); //high���� ��ȯ�ϴ� �Լ�

	//�迭�� ���� �� ���Կ� �Լ�
	int& operator[](int);
	int operator[](int) const;
	//�˰��� : ArrayŬ������ ������ ���۷����͸� ȣ���ϵ�, ȣ���� �ε����� ���� low��ŭ�� ���� ���� ȣ��
	//low��ŭ�� ���� �����ν� �迭���� ������ Ư���� �Լ� ���� ���� �� �� ����.
};

#endif