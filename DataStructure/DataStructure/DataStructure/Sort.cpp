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
	if (left < right) {
		// �ڱ����ֲ���
		int pivot = partition(seqList, left, right);
		// �������������н϶̵��Ǹ�ִ�п�������
		if (pivot - left < right - pivot) {
			QuickSort(seqList, left, pivot - 1); // �ݹ�������������
			QuickSort(seqList, pivot + 1, right); // �ݹ�������������
		}
		else {
			QuickSort(seqList, pivot + 1, right); // �ݹ�������������
			QuickSort(seqList, left, pivot - 1); // �ݹ�������������
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

	double sort0, sort1, sort2, sort3;
	QueryPerformanceFrequency(&tc);

	const char* names[] = { "����", "ѡ��", "ð��", "����" };
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
		cout << names[i] << "�������ú�ʱ(uS): " << times[i] << endl;
		seqList_temp.printList(15);
		cout << endl;
	}

	map<string, int> sort_map;

	for (int i = 0; i < 4; i++) {
		sort_map.insert(pair<string, int>(names[i], times[i]));
	}

	vector<pair<string, int>> vector_map(sort_map.begin(), sort_map.end());
	sort(vector_map.begin(), vector_map.end(), compare);

	cout << "���������ʱ�Ƚ�(uS):" << endl;
	for (auto item : vector_map)
	{
		cout << item.first << "����" << " : " << item.second << " < ";
	}
	cout << "NULL" << endl;
	system("pause");

	return OK;
}

#pragma endregion

