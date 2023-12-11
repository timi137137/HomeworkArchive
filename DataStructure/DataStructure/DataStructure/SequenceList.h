#include <iostream>

#ifndef SEQLIST_H
	#define SEQLIST_H

	typedef int ElementType; // ��������

	class SeqList {
	public:
		SeqList(int size = 0);
		SeqList(const SeqList &seqList);
		~SeqList();

		bool isEmpty();
		int getLength();
		bool getElement(int index, ElementType* element);
		int getElement(int index);
		bool swapElement(int index1, int index2);
		bool appendList(const ElementType element);
		bool insertList(int index, const ElementType element);
		bool deleteList(int index, ElementType* element);
		void printList();

	private:
		ElementType* p_DataArray; // ָ����˳���Ԫ�ص�����
		int p_length; // ˳���ĵ�ǰ����
		int p_maxSize; // ˳�����������
	};
#endif
