#include <iostream>

#ifndef SEQLIST_H
	#define SEQLIST_H

	template <typename ElementType> //数据类型
	class SeqList {
	public:
		SeqList(int size = 0);
		SeqList(const SeqList<ElementType> &seqList);
		~SeqList();

		bool isEmpty();
		int getLength();
		bool getElement(int index, ElementType* element);
		ElementType getElement(int index);
		bool swapElement(int index1, int index2);
		bool appendList(const ElementType element);
		bool insertList(int index, const ElementType element);
		bool deleteList(int index, ElementType* element);
		void printList();
		void printList(int limit);
		void printList(const char* filename);

	private:
		ElementType* p_DataArray; // 指向存放顺序表元素的数组
		int p_length; // 顺序表的当前长度
		int p_maxSize; // 顺序表的最大容量
	};
#endif
