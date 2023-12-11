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

/* ѡȡ����Ԫ�ص���λ�� */
int getMedian(SeqList& seqList, int left, int mid, int right) {
	// �˴�ʹ������������򻯴���
	if ((seqList.getElement(left) < seqList.getElement(mid)) ^ (seqList.getElement(left) < seqList.getElement(right))) return left;
	else if ((seqList.getElement(mid) < seqList.getElement(left)) ^ (seqList.getElement(mid) < seqList.getElement(right))) return mid;
	else return right;
}
/* �ڱ����֣�����ȡ��ֵ�� */
int partition(SeqList& seqList, int left, int right) {
	// ѡȡ������ѡԪ�ص���λ��
	int median = getMedian(seqList, left, (left + right) / 2, right);
	// ��λ���ŵ������
	seqList.swapElement(left, median);
	// ����ָ��Ϊ��׼��
	int i = left, j = right;

	while (i < j) {
		while (i < j && seqList.getElement(j) >= seqList.getElement(left)) {
			j--; // �����������׸�С�ڻ�׼����Ԫ��
		}
			
		while (i < j && seqList.getElement(i) <= seqList.getElement(left)) {
			i++; // �����������׸����ڻ�׼����Ԫ��
		}

		seqList.swapElement(i, j);
	}

	seqList.swapElement(i, left);// �����ֽ���
	return i;            // ���ػ�׼��������
}
status QuickSort(SeqList& seqList, int left, int right) {
	// ���鳤��Ϊ 1 ʱ��ֹ
	while (left < right) {
		// �ڱ����ֲ���
		int pivot = partition(seqList, left, right);
		// �������������н϶̵��Ǹ�ִ�п�������
		if (pivot - left < right - pivot) {
			QuickSort(seqList, left, pivot - 1); // �ݹ�������������
			left = pivot + 1;                 // ʣ��δ��������Ϊ [pivot + 1, right]
		}
		else {
			QuickSort(seqList, pivot + 1, right); // �ݹ�������������
			right = pivot - 1;                 // ʣ��δ��������Ϊ [left, pivot - 1]
		}
	}
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

	cout << "ԭʼ����˳���:" << endl;
	seqList.printList();
	cout << endl;

	SeqList seqList1(seqList);
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	SelectionSort(seqList1);
	QueryPerformanceCounter(&t2);
	cout << "�����������ú�ʱ(uS)" << endl;
	cout << "ѡ������: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList1.printList();
	cout << endl;

	SeqList seqList2(seqList);
	QueryPerformanceCounter(&t1);
	BubbleSort(seqList2);
	QueryPerformanceCounter(&t2);
	cout << "�����������ú�ʱ(uS)" << endl;
	cout << "ð������: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList2.printList();
	cout << endl;

	SeqList seqList3(seqList);
	QueryPerformanceCounter(&t1);
	QuickSort(seqList3, 0, seqList3.getLength());
	QueryPerformanceCounter(&t2);
	cout << "�����������ú�ʱ(uS)" << endl;
	cout << "��������: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList3.printList();
	cout << endl;

	delete &seqList1;
	delete &seqList2;
	delete &seqList3;

	system("pause");

	return OK;
}

#pragma endregion

