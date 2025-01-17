#pragma once
#include <iostream>
#include "clsMyDynamicArray.h"
using namespace std;

template <class T>
class clsMyQueueArr
{

protected:

	clsMyDynamicArray <T> _MyList;

public:

	void Push(T Item)
	{
		_MyList.InsertAtEnd(Item);
	}

	void Pop()
	{
		_MyList.DeleteFirstItem();
	}

	void Print()
	{
		_MyList.PrintList();
	}

	int Size()
	{
		return _MyList.Size();
	}

	T Front()
	{
		return _MyList.GetItem(0);
	}

	T Back()
	{
		return _MyList.GetItem(Size() - 1);
	}

	bool IsEmpty()
	{
		return _MyList.IsEmpty();
	}

	T GetItem(int Index)
	{
		return	_MyList.GetItem(Index);
	}

	void Reverse()
	{
		_MyList.Reverse();
	}

	bool UpdateItem(int Index, T NewValue)
	{
		return	_MyList.SetItem(Index, NewValue);
	}

	void InsertAfter(int Index, T InsertedValue)
	{
		_MyList.InsertAfter(Index, InsertedValue);
	}

	void InsertAtFront(T Value)
	{
		_MyList.InsertAtBeginning(Value);
	}

	void InsertAtBack(T Value)
	{
		_MyList.InsertAtEnd(Value);
	}

	void Clear()
	{
		_MyList.Clear();
	}
};

