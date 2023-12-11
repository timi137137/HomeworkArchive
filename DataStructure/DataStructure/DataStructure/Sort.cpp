#include <iostream>
#include <iomanip>
#include <windows.h>
#include "SequenceList.h"

using namespace std;

#pragma region -- Define --

#define OK 1;
#define ERROR -1;
#define OVERFLOW -2;

typedef int status;

#pragma endregion

#pragma region -- Functions --

status CreateSeqList(SeqList& seqList, int Maxsize) {
	int i, input;
	for (i = 0; i < Maxsize; i++) {
		cin >> input;
		seqList.appendList(input);
	}

	return OK;
}

status SelectionSort(SeqList& seqList) {
	if (seqList.isEmpty()) return OVERFLOW;

	int n = seqList.getLength();

	// ��ѭ����δ��������Ϊ [i, n-1]
	for (int i = 0; i < n - 1; i++) {
		// ��ѭ�����ҵ�δ���������ڵ���СԪ��
		int k = i;
		for (int j = i + 1; j < n; j++) {
			if (seqList.getElement(j) < seqList.getElement(k)) k = j; // ��¼��СԪ�ص�����
		}
		seqList.swapElement(i, k);
	}

	return OK;
}

status BubbleSort(SeqList& seqList) {
	if (seqList.isEmpty()) return OVERFLOW;

	int n = seqList.getLength();

	// ��ѭ����δ��������Ϊ [0, i]
	for (int i = n - 1; i > 0; i--) {
		bool flag = false; // �����¼����

		// ��ѭ������δ�������� [0, i] �е����Ԫ�ؽ���������������Ҷ�
		for (int j = 0; j < i; j++) {
			if (seqList.getElement(j) > seqList.getElement(j + 1)) {
				// ���� j�� j + 1
				seqList.swapElement(j, j + 1);

				flag = true; // �����¼���¼
			}
		}

		if (!flag) break; // δ�����κ�Ԫ�أ�ֱ������
	}

	return OK;
}

status InsertionSort(SeqList& seqList) {
	return OK;
}

status QuickSort(SeqList& seqList) {
	return OK;
}

status MergeSort(SeqList& seqList) {
	return OK;
}

#pragma endregion

#pragma region -- Main --

int main() {
	int Maxsize, Length;
	int input, result;

	LARGE_INTEGER t1, t2, tc; // ��ʱ������

	cout << "������˳���ĳ���: " << endl;
	cin >> Maxsize;
	SeqList seqList(Maxsize);
	cout << "������Ԫ�ز��س����ظ��ò����Դ���˳���" << endl;
	CreateSeqList(seqList, Maxsize);
	system("cls");

	seqList.printList();
	cout << endl;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	SelectionSort(seqList);
	QueryPerformanceCounter(&t2);
	cout << "�����������ú�ʱ(uS)" << endl;
	cout << "ѡ������: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList.printList();
	cout << endl;

	QueryPerformanceCounter(&t1);
	BubbleSort(seqList);
	QueryPerformanceCounter(&t2);
	cout << "�����������ú�ʱ(uS)" << endl;
	cout << "ð������: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList.printList();
	cout << endl;

	system("pause");

	return OK;
}

#pragma endregion

