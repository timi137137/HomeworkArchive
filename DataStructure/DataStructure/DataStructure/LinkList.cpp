#include <iostream>

using namespace std;

#pragma region -- Define --

#define OK 1;
#define ERROR -1;
#define OVERFLOW -2;

typedef int status;

/// <summary>
/// Link List Node 
/// </summary>
typedef struct LNode {
	int value; // Node Value
	struct LNode* next; // Next Node
} LNode, *LinkList;

#pragma endregion

#pragma region -- Functions --

status InitList(LinkList& List) {
	List = new LNode;
	List->next = NULL;
	return OK;
}

status CreateList (LinkList& List, int Length) {
	InitList(List);
	if (List == NULL) return OVERFLOW;

	int i, input;
	LNode* previous;
	LNode* node;

	previous = List;
	for (i = 0; i < Length; i++) {
		cin >> input;
		node = new LNode;
		if (node == NULL) return OVERFLOW;

		node->next = NULL;
		node->value = input;
		previous->next = node;
		previous = node;
	}
	return OK;
}

status PrintList(LinkList List, int Length) {
	for (int i = 0; i < Length; i++) {
		List = List->next;
		cout << List->value << " -> ";
	}
	cout << "NULL" << endl;
	return OK;
}

status GetListLength(LinkList List) {
	int i = 0;

	while (List->next != NULL)
	{
		List = List->next;
		i++;
	}
	cout << "链表长度为：" << i;
	return OK;
}

status GetElement(LinkList& List, int index) {
	for (int i = 0; i < index; i++) {
		List = List->next;
	}
	cout << List->value;
	return OK;
}

status InsertElement(LinkList& List, int index, int input) {
	if (index < 1) return OVERFLOW;
	
	int i;
	LinkList list = List;

	for (i = 1; list && i < index; i++) {
		list = list->next;
	}

	if (!list || i > index) return ERROR;

	LinkList temp = new LNode;
	temp->value = input;
	temp->next = list->next;
	list->next = temp;

	return OK;
}

status DeleteElement(LinkList& List, int index) {
	int i;
	LinkList list = List;

	for (i = 0; list->next && i < index - 1; ++i) {
		list = list->next;
	}

	if (!list->next || i > index - 1) return OVERFLOW;

	LinkList Temp = list->next;
	list->next = Temp->next;
	delete Temp;

	return OK;
}

bool SearchElement(LinkList& List, int input) {
	LNode* list;
	list = List;
	while (list->value != input && list->next != NULL)
	{
		list = list->next;
		if (list->next == NULL) return false;
	}
	return true;
}

status SearchMaximumElement(LinkList& List, int input) {
	int max = 0;
	LNode* list;
	list = List;
	while (list->next != NULL)
	{
		if (list->value > max) {
			max = list->value;
		}

		list = list->next;
	}
	cout << "链表中最大的值为：" << max;
	return OK;
}

#pragma endregion

#pragma region -- Main --

int main() {
	LinkList List;
	int Length, Feature, Number1, SearchNumber;

	#pragma region -- Init --
	cout << "请输入链表的长度: " << endl;
	cin >> Length;
	cout << "请输入元素并回车，重复该操作以创建链表：" << endl;
	CreateList(List, Length);
	system("cls");
	cout << "创建的链表为: " << endl;
	PrintList(List, Length);
	cout << endl;
	GetListLength(List);
	cout << endl;
	system("pause");
	#pragma endregion

	system("cls");
	cout << "请选择功能: \n 1. 查询元素位置 \n 2. 查询元素是否存在 \n 3. 查找最大值 \n 4. 在指定位置新增元素 \n 5. 删除指定元素" << endl;
	cin >> Feature;

	return 0;
}

#pragma endregion

