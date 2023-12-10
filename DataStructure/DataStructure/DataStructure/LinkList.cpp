#include "LinkList.h"

#pragma region -- Functions --
// 构造函数
LinkList::LinkList()
{
	head = new LinkNode;
	head->next = nullptr;
}

// 析构函数
LinkList::~LinkList()
{
	delete head;
	head = nullptr;
}

// 判断是否为空操作
bool LinkList::isEmpty()
{
	return head == nullptr ? true : false;
}

// 获取链表长度操作
int LinkList::getLength()
{
	int count = 0;
	LinkNode* temp = head->next;

	while (temp != nullptr)
	{
		count++;
		temp = temp->next;
	}

	return count;
}

// 获取元素操作
bool LinkList::getElement(int index, ElementType* element)
{
	LinkNode* temp = head->next;

	if (temp == nullptr || index < 0 || index > getLength()) return false;

	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	*element = temp->value;
	return true;
}
int LinkList::getElement(int index)
{
	LinkNode* temp = head->next;

	if (temp == nullptr || index < 0 || index > getLength()) return -1;

	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp->value;
}

// 新增元素操作
bool LinkList::appendList(const ElementType element)
{
	if (head == nullptr) return false;

	LinkNode* per = head;
	for (int i = 0; i < getLength(); i++)
	{
		per = per->next;
	}
	LinkNode* newNode = new LinkNode;
	newNode->value = element;
	newNode->next = nullptr;
	per->next = newNode;

	return true;
}

// 插入元素操作
bool LinkList::insertList(int index, const ElementType element)
{
	if (index < 0 || index > getLength()) return false;

	LinkNode* per = head;
	for (int i = 0; i < index; i++)
	{
		per = per->next;
	}
	LinkNode* newNode = new LinkNode;
	newNode->value = element;
	newNode->next = per->next;
	per->next = newNode;

	return true;
}

// 删除元素操作
bool LinkList::deleteList(int index, ElementType* element)
{
	if (index < 0 || index > getLength()) return false;

	LinkNode* per = head;
	for (int i = 0; i < index; i++)
	{
		per = per->next;
	}
	LinkNode* temp = per->next;
	per->next = per->next->next;
	delete temp;

	return true;
}

// 清空链表操作
bool LinkList::clearList()
{
	while (head->next != NULL)
	{
		LinkNode* node = head->next;
		head->next = head->next->next;
		delete node;
	}

	return true;
}

// 遍历链表
void LinkList::printList()
{
	LinkNode* temp = head;
	while (temp->next != nullptr)
	{
		temp = temp->next;
		std::cout << temp->value << " -> ";
	}

	std::cout << "NULL" << std::endl;
}
#pragma endregion