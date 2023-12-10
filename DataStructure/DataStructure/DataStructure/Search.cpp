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

	LARGE_INTEGER t1, t2, tc; // 计时器函数

	#pragma region -- SeqList --

	cout << "请输入顺序表的长度: " << endl;
	cin >> Maxsize;
	SeqList seqList(Maxsize);
	cout << "请输入元素并回车，重复该操作以创建顺序表：" << endl;
	CreateList(seqList, Maxsize);
	system("cls");

	cout << "请输入要在顺序表进行查找的元素: " << endl;
	cin >> input;

	cout << endl;
	cout << "如结果等于-1则元素不存在:" << endl;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	result = SequentialSearch(seqList, input);
	QueryPerformanceCounter(&t2);
	cout << "顺序查找 - 搜索结果为: " << result << " — 耗时(uS):" << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;

	QueryPerformanceCounter(&t1);
	result = BinarySearch(seqList, input);
	QueryPerformanceCounter(&t2);
	cout << "二分查找 - 搜索结果为: " << result << " — 耗时(uS):" << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;

	#pragma endregion

	#pragma region -- LinkList --

	cout << "请输入链表的长度: " << endl;
	cin >> Length;
	cout << "请输入元素并回车，重复该操作以创建链表：" << endl;
	CreateLinkList(linkList, Length);
	system("cls");

	cout << "请输入要在链表进行查找的元素: " << endl;
	cin >> input;

	cout << endl;
	cout << "如结果等于-1则元素不存在:" << endl;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	result = SequentialSearch(linkList, input);
	QueryPerformanceCounter(&t2);
	cout << "顺序查找 - 搜索结果为: " << result << " — 耗时(uS):" << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;

	#pragma endregion

	system("pause");

	return OK;
}

#pragma endregion

