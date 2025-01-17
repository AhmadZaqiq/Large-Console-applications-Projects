#pragma once
#include <iostream>
using namespace std;

//ÏÇÆãÇ ÈÚÑİ ßÑäÊ æÈÎáíå íÓÇæí ÇáåíÏ æÈãÔí ÈÇáßÑäÊ ÚÔÇä ãÇ ÇÚÏá ŞíãÉ ÇáåíÏ æíÙáæ ÏÇíãÇ íÇÔÑ Úá ÈÏÇíÉ

template <class T>

class clsDblLinkedList
{

protected:

	int _Size = 0;

public:

	class Node
	{
	public:

		T Value;
		Node* Next;
		Node* Prev;
	};

	Node* Head = NULL;

	void InsertAtBeginning(T Value)
	{
		Node* NewNode = new Node();
		NewNode->Value = Value;
		NewNode->Next = Head;
		NewNode->Prev = NULL;

		if (Head != NULL)
		{
			Head->Prev = NewNode;
		}

		Head = NewNode;

		_Size++;
	}

	void PrintList()
	{
		Node* Current = Head;

		while (Current != NULL)
		{
			cout << Current->Value << " ";
			Current = Current->Next;
		}

		cout << "\n\n";

	}

	Node* Find(T Value)
	{
		Node* Current = Head;

		while (Current != NULL)
		{
			if (Current->Value == Value)
			{
				return Current;
			}
			Current = Current->Next;
		}
		return NULL;
	}

	void InsertAfter(Node*& Current, T Value)
	{
		Node* New_Node = new Node();

		New_Node->Value = Value;

		New_Node->Next = Current->Next;
		New_Node->Prev = Current;

		if (New_Node->Next != NULL)
			Current->Next->Prev = New_Node;

		Current->Next = New_Node;

		_Size++;
	}

	void InsertAtEnd(T Value)
	{
		Node* New_Node = new Node();
		New_Node->Value = Value;
		New_Node->Next = NULL;

		if (Head == NULL)
		{
			New_Node->Prev = NULL;
			Head = New_Node;
			_Size++;
			return;
		}

		Node* Current = Head;

		while (Current->Next != NULL)
		{
			Current = Current->Next;
		}

		Current->Next = New_Node;
		New_Node->Prev = Current;

		_Size++;
	}

	void DeleteNode(Node*& NodeToDelete)
	{

		if (Head == NULL || NodeToDelete == NULL) return;

		if (Head == NodeToDelete) Head = NodeToDelete->Next;

		if (NodeToDelete->Next != NULL) NodeToDelete->Next->Prev = NodeToDelete->Prev;

		if (NodeToDelete->Prev != NULL) NodeToDelete->Prev->Next = NodeToDelete->Next;

		delete NodeToDelete;

		_Size--;
	}

	void DeleteFirstNode()
	{
		if (Head == NULL) return;

		Node* Temp = Head;

		Head = Head->Next;

		if (Head != NULL)
		{
			Head->Prev = NULL;
		}

		delete Temp;

		_Size--;
	}

	void DeleteLastNode()
	{
		if (Head == NULL) return;

		if (Head->Next == NULL)
		{
			delete Head;
			Head = NULL;
			return;
		}

		Node* Current = Head;

		while (Current->Next->Next != NULL) Current = Current->Next;

		Node* Temp = Current->Next;
		Current->Next = NULL;

		delete Temp;

		_Size--;
	}

	int Size()
	{
		return _Size;
	}

	bool IsEmpty()
	{
		return !(_Size);
	}

	void Clear()
	{
		while (_Size > 0)
		{
			DeleteFirstNode();
		}
	}

	void Reverse()
	{
		Node* Current = Head;
		Node* Temp = nullptr;

		while (Current != nullptr)
		{
			Temp = Current->Prev;
			Current->Prev = Current->Next;
			Current->Next = Temp;
			Current = Current->Prev;
		}

		if (Temp != nullptr)
		{
			Head = Temp->Prev;
		}
	}

	Node* GetNode(int Index)
	{
		Node* Current = Head;
		short Counter = 0;

		if (Index > _Size - 1 || Index < 0) return NULL;



		while (Current != NULL && (Current->Next != NULL))
		{
			if (Counter == Index) break;

			Current = Current->Next;
			Counter++;
		}

		return Current;
	}

	T GetItem(int Index)
	{
		return (GetNode(Index) == NULL) ? NULL : GetNode(Index)->Value;
	}

	bool UpdateItem(int Index, T NewValue)
	{
		Node* ItemNode = GetNode(Index);

		if (ItemNode)
		{
			ItemNode->Value = NewValue;
			return true;
		}

		else
			return false;
	}

	bool InsertAfter(int Index, T InsertedValue)
	{
		Node* CurrentNode = GetNode(Index);

		if (CurrentNode)
		{
			InsertAfter(CurrentNode, InsertedValue);
			return true;
		}

		else
			return false;
	}

	

};
