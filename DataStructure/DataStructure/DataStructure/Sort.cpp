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

	// 外循环：未排序区间为 [i, n-1]
	for (int i = 0; i < n - 1; i++) {
		// 内循环：找到未排序区间内的最小元素
		int k = i;
		for (int j = i + 1; j < n; j++) {
			if (seqList.getElement(j) < seqList.getElement(k)) k = j; // 记录最小元素的索引
		}
		seqList.swapElement(i, k);
	}

	return OK;
}

status BubbleSort(SeqList& seqList) {
	if (seqList.isEmpty()) return OVERFLOW;

	int n = seqList.getLength();

	// 外循环：未排序区间为 [0, i]
	for (int i = n - 1; i > 0; i--) {
		bool flag = false; // 交换事件标记

		// 内循环：将未排序区间 [0, i] 中的最大元素交换至该区间的最右端
		for (int j = 0; j < i; j++) {
			if (seqList.getElement(j) > seqList.getElement(j + 1)) {
				// 交换 j和 j + 1
				seqList.swapElement(j, j + 1);

				flag = true; // 交换事件记录
			}
		}

		if (!flag) break; // 未交换任何元素，直接跳出
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

	LARGE_INTEGER t1, t2, tc; // 计时器函数

	cout << "请输入顺序表的长度: " << endl;
	cin >> Maxsize;
	SeqList seqList(Maxsize);
	cout << "请输入元素并回车，重复该操作以创建顺序表：" << endl;
	CreateSeqList(seqList, Maxsize);
	system("cls");

	seqList.printList();
	cout << endl;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	SelectionSort(seqList);
	QueryPerformanceCounter(&t2);
	cout << "各类排序所用耗时(uS)" << endl;
	cout << "选择排序: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList.printList();
	cout << endl;

	QueryPerformanceCounter(&t1);
	BubbleSort(seqList);
	QueryPerformanceCounter(&t2);
	cout << "各类排序所用耗时(uS)" << endl;
	cout << "冒泡排序: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList.printList();
	cout << endl;

	system("pause");

	return OK;
}

#pragma endregion

