#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
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
	for (int i = 1; i < seqList.getLength(); i++) {
		ElementType key;
		seqList.getElement(i, &key);

		int j = i - 1;

		while (j >= 0 && seqList.getElement(j) > key) {
			ElementType element;
			seqList.getElement(j, &element);
			seqList.swapElement(j + 1, j);
			j--;
		}

		seqList.insertList(j + 1, key);
	}
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
	if (left < right) {
		// 哨兵划分操作
		int pivot = partition(seqList, left, right);
		// 对两个子数组中较短的那个执行快速排序
		if (pivot - left < right - pivot) {
			QuickSort(seqList, left, pivot - 1); // 递归排序左子数组
			QuickSort(seqList, pivot + 1, right); // 递归排序右子数组
		}
		else {
			QuickSort(seqList, pivot + 1, right); // 递归排序右子数组
			QuickSort(seqList, left, pivot - 1); // 递归排序左子数组
		}
	}
	return OK;
}

double calcTime(LARGE_INTEGER t1, LARGE_INTEGER t2, LARGE_INTEGER tc) {
	return (t2.QuadPart - t1.QuadPart) * 1000000.0 / (double)tc.QuadPart;
}
bool compare(const pair<string, int>& v1, const pair<string, int>& v2)
{
	return v1.second < v2.second;
}

#pragma endregion

#pragma region -- Main --

int main5() {
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

	double sort0, sort1, sort2, sort3;
	QueryPerformanceFrequency(&tc);

	const char* names[] = { "插入", "选择", "冒泡", "快速" };
	double times[4];

	for (int i = 0; i < 4; i++)
	{
		SeqList seqList_temp(seqList);
		QueryPerformanceCounter(&t1);

		switch (i)
		{
		case 0:
			InsertionSort(seqList_temp);
			break;
		case 1:
			SelectionSort(seqList_temp);
			break;
		case 2:
			BubbleSort(seqList_temp);
			break;
		case 3:
			QuickSort(seqList_temp, 0, seqList_temp.getLength() - 1);
			break;
		default:
			break;
		}

		QueryPerformanceCounter(&t2);
		times[i] = calcTime(t1, t2, tc);
		cout << names[i] << "排序所用耗时(uS): " << times[i] << endl;
		seqList_temp.printList(15);
		cout << endl;
	}

	map<string, int> sort_map;

	for (int i = 0; i < 4; i++) {
		sort_map.insert(pair<string, int>(names[i], times[i]));
	}

	vector<pair<string, int>> vector_map(sort_map.begin(), sort_map.end());
	sort(vector_map.begin(), vector_map.end(), compare);

	cout << "各类排序耗时比较(uS):" << endl;
	for (auto item : vector_map)
	{
		cout << item.first << "排序" << " : " << item.second << " < ";
	}
	cout << "NULL" << endl;
	system("pause");

	return OK;
}

#pragma endregion

