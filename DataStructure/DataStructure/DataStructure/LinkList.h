#include <iostream>

#ifndef LINKLIST_H
	#define LINKLIST_H

	typedef int ElementType; // 数据类型

	class LinkNode {
		friend class LinkList;
	private:
		ElementType value;
		LinkNode* next;
	};

	class LinkList {
	public:
		LinkList();
		~LinkList();

		bool isEmpty();
		int getLength();
		bool getElement(int index, ElementType* element);
		int getElement(int index);
		bool appendList(const ElementType element);
		bool insertList(int index, const ElementType element);
		bool deleteList(int index, ElementType* element);
		bool clearList();
		void printList();

	private:
		LinkNode* head;
	};
#endif