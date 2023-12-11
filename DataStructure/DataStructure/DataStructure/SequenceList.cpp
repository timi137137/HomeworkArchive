#include "SequenceList.h"

#pragma region -- Functions --
// 构造函数
SeqList::SeqList(int size)
{
	p_maxSize = size;
	p_DataArray = new ElementType[p_maxSize];
	p_length = 0;
}
SeqList::SeqList(const SeqList &seqList)
{
	p_maxSize = seqList.p_maxSize;
	p_length = seqList.p_length;

	p_DataArray = new ElementType[p_maxSize];

	for (int i = 0; i < p_length; i++) {
		p_DataArray[i] = seqList.p_DataArray[i];
	}
}

// 析构函数
SeqList::~SeqList()
{
	delete[] p_DataArray;
}

// 判断是否为空操作
bool SeqList::isEmpty()
{
	return p_length == 0 ? true : false;
}

// 获取顺序表长度操作
int SeqList::getLength()
{
	return p_length;
}

// 获取元素操作
bool SeqList::getElement(int index, ElementType* element)
{
	if (p_length == 0 || index < 0 || index > p_length) return false;

	*element = p_DataArray[index];
	return true;
}
int SeqList::getElement(int index)
{
	if (p_length == 0 || index < 0 || index > p_length) return -1;

	return p_DataArray[index];
}

// 交换元素操作
bool SeqList::swapElement(int index1, int index2) {
	try
	{
		ElementType temp = p_DataArray[index2];
		p_DataArray[index2] = p_DataArray[index1];
		p_DataArray[index1] = temp;
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

// 新增元素操作
bool SeqList::appendList(const ElementType element)
{
	if (p_length >= p_maxSize) return false;

	p_DataArray[p_length] = element;
	p_length++;

	return true;
}

// 插入元素操作
bool SeqList::insertList(int index, const ElementType element)
{
	if (p_length >= p_maxSize || index<0 || index>p_length) return false;

	if (index <= p_length - 1)
	{
		for (int k = p_length - 1; k >= index; k--)
		{
			p_DataArray[k + 1] = p_DataArray[k];
		}
	}

	p_DataArray[index] = element;
	p_length++;

	return true;
}

// 删除元素操作
bool SeqList::deleteList(int index, ElementType* element)
{
	if (p_length == 0 || index<0 || index>p_length - 1) return false;

	*element = p_DataArray[index];

	if (index != p_length - 1)
	{
		for (int k = index; k < p_length - 1; k++) {
			p_DataArray[k] = p_DataArray[k + 1];
		}
	}

	p_length--;

	return true;
}

// 遍历顺序表
void SeqList::printList()
{
	if (p_DataArray == nullptr || p_length == 0) return;

	for (int index = 0; index < p_length; index++)
	{
		std::cout << p_DataArray[index] << " -> ";
	}
	std::cout << "NULL" << std::endl;
}
#pragma endregion