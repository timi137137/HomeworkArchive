#include "LinkList.h"

#pragma region -- Functions --
// ���캯��
LinkList::LinkList()
{
	head = new LinkNode;
	head->next = nullptr;
}

// ��������
LinkList::~LinkList()
{
	delete head;
	head = nullptr;
}

// �ж��Ƿ�Ϊ�ղ���
bool LinkList::isEmpty()
{
	return head == nullptr ? true : false;
}

// ��ȡ�����Ȳ���
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

// ��ȡԪ�ز���
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

// ����Ԫ�ز���
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

// ����Ԫ�ز���
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

// ɾ��Ԫ�ز���
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

// ����������
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

// ��������
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