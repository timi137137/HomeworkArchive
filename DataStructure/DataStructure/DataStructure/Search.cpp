#include <iostream>
#include <windows.h>
#include "SequenceList.h"
#include "LinkList.h"

using namespace std;

#pragma region -- Define --

#define OK 1;
#define ERROR -1;
#define OVERFLOW -2;

typedef int status;

#pragma endregion

#pragma region -- Functions --

status CreateList(SeqList& seqList, int Maxsize) {
	int i, input;
	for (i = 0; i < Maxsize; i++) {
		cin >> input;
		seqList.appendList(input);
	}

	return OK;
}

status CreateLinkList(LinkList& linkList, int Length) {
	int i, input;
	for (i = 0; i < Length; i++) {
		cin >> input;
		linkList.appendList(input);
	}

	return OK;
}

int SequentialSearch(SeqList& seqList, int element) {
	int i = 0, result = NULL;

	while (result != element)
	{
		i++;
		if (!seqList.getElement(i, &result)) return -1;
	}

	return i;
}
int SequentialSearch(LinkList& linkList, int element) {
	int i = 0, result = NULL;

	while (result != element)
	{
		i++;
		result = linkList.getElement(i);
		if (result == -1) return -1;
	}

	return i;
}

int BinarySearch(SeqList& seqList, int element) {
	int low = 1, high = seqList.getLength(), mid = 0;

	if (seqList.getElement(low) == element) return low;
	if (seqList.getElement(high) == element) return high;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (element < seqList.getElement(mid))
			high = mid - 1;
		else if (element > seqList.getElement(mid))
			low = mid + 1;
		else
			return mid;
	}
	return 0;
}

#pragma endregion

#pragma region -- Main --

int main() {
	LinkList linkList;
	int Maxsize, Length;
	int input, result;

	LARGE_INTEGER t1, t2, tc; // ��ʱ������

	#pragma region -- SeqList --

	cout << "������˳���ĳ���: " << endl;
	cin >> Maxsize;
	SeqList seqList(Maxsize);
	cout << "������Ԫ�ز��س����ظ��ò����Դ���˳���" << endl;
	CreateList(seqList, Maxsize);
	system("cls");

	cout << "������Ҫ��˳�����в��ҵ�Ԫ��: " << endl;
	cin >> input;

	cout << endl;
	cout << "��������-1��Ԫ�ز�����:" << endl;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	result = SequentialSearch(seqList, input);
	QueryPerformanceCounter(&t2);
	cout << "˳����� - �������Ϊ: " << result << " �� ��ʱ(uS):" << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;

	QueryPerformanceCounter(&t1);
	result = BinarySearch(seqList, input);
	QueryPerformanceCounter(&t2);
	cout << "���ֲ��� - �������Ϊ: " << result << " �� ��ʱ(uS):" << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;

	#pragma endregion

	#pragma region -- LinkList --

	cout << "����������ĳ���: " << endl;
	cin >> Length;
	cout << "������Ԫ�ز��س����ظ��ò����Դ�������" << endl;
	CreateLinkList(linkList, Length);
	system("cls");

	cout << "������Ҫ��������в��ҵ�Ԫ��: " << endl;
	cin >> input;

	cout << endl;
	cout << "��������-1��Ԫ�ز�����:" << endl;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	result = SequentialSearch(linkList, input);
	QueryPerformanceCounter(&t2);
	cout << "˳����� - �������Ϊ: " << result << " �� ��ʱ(uS):" << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;

	#pragma endregion

	system("pause");

	return OK;
}

#pragma endregion

