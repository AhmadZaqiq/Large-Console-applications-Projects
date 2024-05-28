#pragma once
#include <iostream>
using namespace std;

template <class T>
class clsMyDynamicArray
{
protected:

	int	_Size;
	T* _TempArray;

public:

	T* OriginalArray;

	clsMyDynamicArray(int Size=0)
	{
		if (Size < 0) Size = 0;

		_Size = Size;

		OriginalArray = new T[_Size];
	}

	~clsMyDynamicArray()
	{
		delete[] OriginalArray;
	}

	bool SetItem(int Index, T Value)
	{
		if (Index >= _Size || _Size < 0) return false;

		OriginalArray[Index] = Value;
		return true;
	}

	int Size()
	{
		return _Size;
	}

	bool IsEmpty()
	{
		return _Size == 0 ? true : false;
	}

	void PrintList()
	{
		cout << "\n\n";

		for (short i = 0; i < _Size; i++)
			cout << OriginalArray[i] << " ";

		cout << "\n\n";
	}

	void ReSize(int NewSize)
	{
		if (NewSize < 0) NewSize = 0;

		if (NewSize == _Size) return;

		_TempArray = new T[NewSize];

		if (NewSize < _Size) _Size = NewSize;

		for (short i = 0; i < _Size; i++) _TempArray[i] = OriginalArray[i];

		_Size = NewSize;

		delete[] OriginalArray;
		OriginalArray = _TempArray;

	}

	void Reverse()
	{
		if (_Size == 0) return;

		_TempArray = new T[_Size];

		for (short i = 1; i <= _Size; i++)
		{
			_TempArray[i - 1] = OriginalArray[_Size - i];
		}

		delete[] OriginalArray;

		OriginalArray = _TempArray;
	}

	T GetItem(int Index)
	{
		return OriginalArray[Index];
	}

	void Clear()
	{
		_Size = 0;
		_TempArray = new T[0];
		delete[] OriginalArray;
		OriginalArray = _TempArray;
	}

	bool DeleteItemAt(int Index)
	{
		if (Index >= _Size || Index < 0) return false;

		_Size--;

		_TempArray = new T[_Size];

		for (short i = 0; i < Index; i++) _TempArray[i] = OriginalArray[i];

		for (short i = Index + 1; i < _Size + 1; i++) _TempArray[i - 1] = OriginalArray[i];

		delete[] OriginalArray;

		OriginalArray = _TempArray;
		return true;

	}

	void DeleteFirstItem()
	{
		DeleteItemAt(0);
	}

	void DeleteLastItem()
	{
		DeleteItemAt(_Size - 1);
	}

	T FindItem(T Value)
	{
		for (short i = 0; i < _Size; i++)
		{
			if (OriginalArray[i] == Value)
			{
				return i;
			}
		}

		return -1;
	}

	bool DeleteItem(T Value)
	{
		short Index = FindItem(Value);

		if (Index == -1) return false;

		DeleteItemAt(Index);
		return true;
	}

	bool InsertAt(int Index, T Value)
	{

		if (Index > _Size || Index < 0) return false;

		_Size++;

		_TempArray = new T[_Size];

		for (short i = 0; i < Index; i++) _TempArray[i] = OriginalArray[i];

		for (short i = Index; i < _Size - 1; i++) _TempArray[i + 1] = OriginalArray[i];

		_TempArray[Index] = Value;

		delete[] OriginalArray;

		OriginalArray = _TempArray;
		return true;

	}

	void InsertAtBeginning(T Value)
	{
		InsertAt(0, Value);
	}

	bool InsertBefore(int Index, T Value)
	{
		if (Index < 1) return  InsertAt(0, Value);

		return InsertAt(Index - 1, Value);
	}

	bool InsertAfter(int Index, T Value)
	{
		if (Index >= 1) return  InsertAt(_Size-1, Value);

		return InsertAt(Index + 1, Value);
	}

	void InsertAtEnd(T Value)
	{
		InsertAt(_Size, Value);
	}
};

