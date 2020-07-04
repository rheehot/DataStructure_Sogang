#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n; //����ڰ� ���ϴ� ü���� ũ�� ����
int *b; //ü������ �����ϴ� �迭

//���ո��� ��ġ��ų �� �ִ��� Ȯ���ϴ� �Լ�
int Can_Pos(int line){
    //ù��° ������ ���� �������� �������� �̵����� ������ �ɸ����� Ȯ��
    for (int i = 0; i < line; i++){
        if (b[i] == b[line] || abs(b[line] - b[i]) == line - i) return 0;
    }

    //�ɸ��� �� ���ٸ� true ��ȯ
    return 1;
}

//BackTracking �� ����� DFS �˰���
int DFS(int line){
    //���� ��� line�� ���� ���� �ξ��ٸ� ���� ��ġ�� ���
    if (line == (n)){
        for (int i = 0; i < n; ++i) {
            printf("%d ", b[i]);
        }
        //�ϼ��Ǿ����� �˸��� true ��ȯ
        return 1;
    }

    //��� ������ �ξ����� �ʾҴٸ� �̹� ������ ���� �ϳ��� Ž��
    for (int i = 0; i < n; i++) {

        /*������ ��Ŀ������ ������ �迭*/
        b[line] = i; //���� �� ���� ���� �迭�� ����

        //���� �� �� �ִ� ��ġ�� ���
        if (Can_Pos(line) == 1) {
            //�״��� ���� �̵�, ���� ��� ���� �ξ��ٸ� true�� ��ȯ
            if (DFS(line + 1)) return 1;
        }
    }
    
    //�ƿ� ����� ������ �ʾҴٸ� false��ȯ
    return 0;
}

int main(void){

    printf("Input N: ");
    scanf("%d", &n);
    if(n>0) b = (int*)malloc(sizeof(int) * n); //����ڰ� ��û�� ��ŭ�� ü���� ����

    //ü������ �ϼ��ȵȰ�� No solution ���
    if(DFS(0) == 0 || n<=0) printf("No solution\n");

    return 0;
}