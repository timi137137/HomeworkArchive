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
	cout << "������Ϊ��" << i;
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

status DeleteElement(LinkList& List, int index, int& Length) {
	int i;
	LinkList list = List;

	for (i = 0; list->next && i < index - 1; ++i) {
		list = list->next;
	}

	if (!list->next || i > index - 1) return OVERFLOW;

	LinkList Temp = list->next;
	list->next = Temp->next;
	delete Temp;
	Length -= 1;

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

status SearchMaximumElement(LinkList& List) {
	int max = 0;
	LNode* list;
	list = List;
	do
	{
		if (list->value > max) {
			max = list->value;
		}

		list = list->next;
	} while (list && list->value != NULL);
	cout << "����������ֵΪ��" << max;
	return OK;
}

#pragma endregion

#pragma region -- Main --

int main() {
	LinkList List;
	int Length, Feature, Number1, SearchNumber;

	#pragma region -- Init --
	cout << "����������ĳ���: " << endl;
	cin >> Length;
	cout << "������Ԫ�ز��س����ظ��ò����Դ�������" << endl;
	CreateList(List, Length);
	system("cls");
	cout << "����������Ϊ: " << endl;
	PrintList(List, Length);
	cout << endl;
	GetListLength(List);
	cout << endl;
	system("pause");
	#pragma endregion

	#pragma region -- Select --

	while (true)
	{
		system("cls");
		cout << "��ѡ����: \n 1. ��ѯԪ��λ�� \n 2. ��ѯԪ���Ƿ���� \n 3. �������ֵ \n 4. ��ָ��λ������Ԫ�� \n 5. ɾ��ָ��Ԫ�� \n 9. �˳�" << endl;
		cout << "���������: ";
		cin >> Feature;

		switch (Feature)
		{
		case 1:
			cout << "������ҪѰ�ҵ�Ԫ��λ��:" << endl;
			cin >> Number1;
			GetElement(List, Number1);
			cout << endl;
			break;
		case 2:
			cout << "������ҪѰ�ҵ�Ԫ��:" << endl;
			cin >> SearchNumber;
			cout << "��Ҫ���ҵ�Ԫ��" << (SearchElement(List, SearchNumber) ? "����" : "������") << endl;
			break;
		case 3:
			SearchMaximumElement(List);
			cout << endl;
			break;
		case 4:
			int element;
			cout << "������Ҫ��ӵ�Ԫ��:" << endl;
			cin >> element;
			cout << "������Ҫ�����λ��:" << endl;
			cin >> Number1;
			InsertElement(List, Number1, element);
			PrintList(List, Length);
			break;
		case 5:
			cout << "������Ҫɾ����Ԫ��λ��:" << endl;
			cin >> Number1;
			DeleteElement(List, Number1, Length);
			PrintList(List, Length);
			break;
		case 9:
			return 0;
		default:
			cout << "����Ĺ����������������룺" << endl;
			break;
		}

		system("pause");
	}

	#pragma endregion


	return 0;
}

#pragma endregion

