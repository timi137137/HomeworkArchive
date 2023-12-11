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

/* 选取三个元素的中位数 */
int getMedian(SeqList& seqList, int left, int mid, int right) {
	// 此处使用异或运算来简化代码
	if ((seqList.getElement(left) < seqList.getElement(mid)) ^ (seqList.getElement(left) < seqList.getElement(right))) return left;
	else if ((seqList.getElement(mid) < seqList.getElement(left)) ^ (seqList.getElement(mid) < seqList.getElement(right))) return mid;
	else return right;
}
/* 哨兵划分（三数取中值） */
int partition(SeqList& seqList, int left, int right) {
	// 选取三个候选元素的中位数
	int median = getMedian(seqList, left, (left + right) / 2, right);
	// 中位数放到最左边
	seqList.swapElement(left, median);
	// 以左指针为基准数
	int i = left, j = right;

	while (i < j) {
		while (i < j && seqList.getElement(j) >= seqList.getElement(left)) {
			j--; // 从右向左找首个小于基准数的元素
		}
			
		while (i < j && seqList.getElement(i) <= seqList.getElement(left)) {
			i++; // 从左向右找首个大于基准数的元素
		}

		seqList.swapElement(i, j);
	}

	seqList.swapElement(i, left);// 交换分界线
	return i;            // 返回基准数的索引
}
status QuickSort(SeqList& seqList, int left, int right) {
	// 数组长度为 1 时终止
	while (left < right) {
		// 哨兵划分操作
		int pivot = partition(seqList, left, right);
		// 对两个子数组中较短的那个执行快速排序
		if (pivot - left < right - pivot) {
			QuickSort(seqList, left, pivot - 1); // 递归排序左子数组
			left = pivot + 1;                 // 剩余未排序区间为 [pivot + 1, right]
		}
		else {
			QuickSort(seqList, pivot + 1, right); // 递归排序右子数组
			right = pivot - 1;                 // 剩余未排序区间为 [left, pivot - 1]
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

	LARGE_INTEGER t1, t2, tc; // 计时器函数

	cout << "请输入顺序表的长度: " << endl;
	cin >> Maxsize;
	SeqList seqList(Maxsize);
	cout << "请输入元素并回车，重复该操作以创建顺序表：" << endl;
	CreateSeqList(seqList, Maxsize);
	system("cls");

	cout << "原始输入顺序表:" << endl;
	seqList.printList();
	cout << endl;

	SeqList seqList1(seqList);
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	SelectionSort(seqList1);
	QueryPerformanceCounter(&t2);
	cout << "各类排序所用耗时(uS)" << endl;
	cout << "选择排序: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList1.printList();
	cout << endl;

	SeqList seqList2(seqList);
	QueryPerformanceCounter(&t1);
	BubbleSort(seqList2);
	QueryPerformanceCounter(&t2);
	cout << "各类排序所用耗时(uS)" << endl;
	cout << "冒泡排序: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList2.printList();
	cout << endl;

	SeqList seqList3(seqList);
	QueryPerformanceCounter(&t1);
	QuickSort(seqList3, 0, seqList3.getLength());
	QueryPerformanceCounter(&t2);
	cout << "各类排序所用耗时(uS)" << endl;
	cout << "快速排序: " << (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart << endl;
	seqList3.printList();
	cout << endl;

	delete &seqList1;
	delete &seqList2;
	delete &seqList3;

	system("pause");

	return OK;
}

#pragma endregion

