#pragma once
#include "clsMyQueueArr.h"

template <class T>
class MyStackArr : public clsMyQueueArr <T>
{
	protected:

	clsMyDynamicArray <T> _MyList;
public:

	void Push(T Item)
	{
		_MyList.InsertAtBeginning(Item);
	}

	T Top()
	{
		return clsMyQueueArr<T>::Front();
	}

	T Bottom()
	{
		return clsMyQueueArr<T>::Back();
	}

};

