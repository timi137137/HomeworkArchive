#include "SequenceList.h"

#pragma region -- Functions --
// ���캯��
template <typename ElementType>
SeqList<ElementType>::SeqList(int size)
{
	p_maxSize = size;
	p_DataArray = new ElementType[p_maxSize];
	p_length = 0;
}
template <typename ElementType>
SeqList<ElementType>::SeqList(const SeqList &seqList)
{
	p_maxSize = seqList.p_maxSize;
	p_length = seqList.p_length;

	p_DataArray = new ElementType[p_maxSize];

	for (int i = 0; i < p_length; i++) {
		p_DataArray[i] = seqList.p_DataArray[i];
	}
}

// ��������
template <typename ElementType>
SeqList<ElementType>::~SeqList()
{
	delete[] p_DataArray;
}

// �ж��Ƿ�Ϊ�ղ���
template <typename ElementType>
bool SeqList<ElementType>::isEmpty()
{
	return p_length == 0 ? true : false;
}

// ��ȡ˳����Ȳ���
template <typename ElementType>
int SeqList<ElementType>::getLength()
{
	return p_length;
}

// ��ȡԪ�ز���
template <typename ElementType>
bool SeqList<ElementType>::getElement(int index, ElementType* element)
{
	if (p_length == 0 || index < 0 || index > p_length) return false;

	*element = p_DataArray[index];
	return true;
}
template <typename ElementType>
int SeqList<ElementType>::getElement(int index)
{
	if (p_length == 0 || index < 0 || index > p_length) return -1;

	return p_DataArray[index];
}

// ����Ԫ�ز���
template <typename ElementType>
bool SeqList<ElementType>::swapElement(int index1, int index2) {
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

// ����Ԫ�ز���
template <typename ElementType>
bool SeqList<ElementType>::appendList(const ElementType element)
{
	if (p_length >= p_maxSize) return false;

	p_DataArray[p_length] = element;
	p_length++;

	return true;
}

// ����Ԫ�ز���
template <typename ElementType>
bool SeqList<ElementType>::insertList(int index, const ElementType element)
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

// ɾ��Ԫ�ز���
template <typename ElementType>
bool SeqList<ElementType>::deleteList(int index, ElementType* element)
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

// ����˳���
template <typename ElementType>
void SeqList<ElementType>::printList()
{
	if (p_DataArray == nullptr || p_length == 0) return;

	for (int index = 0; index < p_length; index++)
	{
		std::cout << p_DataArray[index] << " -> ";
	}
	std::cout << "NULL" << std::endl;
}
template <typename ElementType>
void SeqList<ElementType>::printList(int limit)
{
	if (p_DataArray == nullptr || p_length == 0) return;

	for (int index = 0; index < (p_length > limit ? limit : p_length); index++)
	{
		std::cout << p_DataArray[index] << " -> ";
	}
	std::cout << "LIMIT" << std::endl;
}
#pragma endregion