/*

2.	Make a doubly linked list data structure with the following functions:
	a.	Empty() – returns true if the list is empty
	b.	Size() – returns the size of the list
	c.	PushBack() – inserts a new element at the end of the list
	d.	PopBack() – remove last element
	e.	PushFront () – inserts a new element at the end of the list
	f.	PopFront () – remove last element
	g.	At() – gets the element at a certain index
	h.	operator[] – gets the element at a certain index
	i.	Resize() – resizes the vector
	j.	Clear() – empties the vector
	k.	Insert() – inserts a new element at a certain spot in the vector
	l.	Erase() – removes an element at a certain spot in the vector
	m.	Merge() – Merges 2 lists
	n.	Splice() – Give me a bit I will explain it later

*/

#include <iostream>
#include <optional>

struct Node
{
	int mData;
	struct Node* mPrev;
	struct Node* mNext;
};

struct DoublyLinkedList
{
	Node* mHead = nullptr;
	Node* mTail = nullptr;

	bool Empty() const
	{
		return mHead == nullptr;
	}

	int GetSize(Node* node) const
	{
		int size = 0;
		while (node)
		{
			size++;
			node = node->mNext;
		}
		return size;
	}

	Node* GetNodeAtIndex(int index)
	{
		Node* current = mHead;
		int count = 0;

		while (current && count < index)
		{
			current = current->mNext;
			count++;
		}

		return current;
	}

	void PushBack(int data)
	{
		Node* newNode = new Node;
		newNode->mData = data;
		newNode->mPrev = nullptr;
		newNode->mNext = nullptr;

		if (!mHead)
		{
			mHead = newNode;
		}

		if (mTail)
		{
			newNode->mPrev = mTail;
			mTail->mNext = newNode;
		}

		mTail = newNode;
	}


	void PopBack()
	{
		if (mTail)
		{
			Node* nodeToDelete = mTail;
			mTail = mTail->mPrev;

			if (mTail)
			{
				mTail->mNext = nullptr;
			}
			else
			{
				mHead = nullptr;
			}

			delete nodeToDelete;
		}
	}

	void PushFront(int data)
	{
		Node* newNode = new Node;
		newNode->mData = data;
		newNode->mPrev = nullptr;
		newNode->mNext = nullptr;

		if (!mHead)
		{
			mHead = newNode;
			mTail = newNode;
		}
		else
		{
			newNode->mNext = mHead;
			mHead->mPrev = newNode;
			mHead = newNode;
		}
	}

	void PopFront()
	{
		if (!mHead)
		{
			return;
		}

		if (mHead == mTail)
		{
			delete mHead;
			mHead = nullptr;
			mTail = nullptr;
			return;
		}

		Node* nextNode = mHead->mNext;
		nextNode->mPrev = nullptr;

		delete mHead;
		mHead = nextNode;
	}

	std::optional<int> At(int index)
	{
		Node* current = GetNodeAtIndex(index);

		if (!current)
		{
			return std::nullopt;
		}
		else
		{
			return current->mData;
		}
	}

	std::optional<int> operator[](int index)
	{
		return At(index);
	}

	void Resize(int newSize)
	{
		int currentSize = GetSize(mHead);

		if (newSize == currentSize)
		{
			return;
		}
		else if (newSize < currentSize)
		{
			int elementsToRemove = currentSize - newSize;
			for (int i = 0; i < elementsToRemove; i++)
			{
				PopBack();
			}
		}
		else
		{
			int elementsToAdd = newSize - currentSize;
			for (int i = 0; i < elementsToAdd; i++)
			{
				PushBack(0);
			}
		}
	}

	void Clear()
	{
		Node* current = mHead;

		while (current)
		{
			Node* next = current->mNext;
			delete current;
			current = next;
		}

		mHead = nullptr;
		mTail = nullptr;
	}

	void Insert(Node* prevNode, int data)
	{
		if (!prevNode)
		{
			Node* newNode = new Node();
			newNode->mData = data;
			newNode->mPrev = nullptr;
			newNode->mNext = nullptr;
			prevNode = newNode;
			return;
		}

		Node* newNode = new Node();
		newNode->mData = data;

		newNode->mNext = prevNode->mNext;
		newNode->mPrev = prevNode;

		if (prevNode->mNext)
		{
			prevNode->mNext->mPrev = newNode;
		}

		prevNode->mNext = newNode;
		mTail = newNode;
	}

	void Erase(int index)
	{
		if (index < 0 || index >= GetSize(mHead))
		{
			std::cout << "Invalid index!" << std::endl;
			return;
		}

		if (index == 0)
		{
			PopFront();
			return;
		}
		else if (index == GetSize(mHead) - 1)
		{
			PopBack();
			return;
		}

		Node* current = GetNodeAtIndex(index);

		if (!current)
		{
			std::cout << "Invalid index!" << std::endl;
			return;
		}

		Node* previousNode = current->mPrev;
		Node* nextNode = current->mNext;

		previousNode->mNext = nextNode;
		nextNode->mPrev = previousNode;

		delete current;
	}

	void Merge(DoublyLinkedList& otherList)
	{
		if (this == &otherList)
		{
			std::cout << "Cannot merge a list with itself!" << std::endl;
			return;
		}

		if (otherList.Empty())
		{
			return;
		}

		if (Empty())
		{
			mHead = otherList.mHead;
			mTail = otherList.mTail;
			return;
		}

		mTail->mNext = otherList.mHead;
		otherList.mHead->mPrev = mTail;
		mTail = otherList.mTail;
	}

	void Splice(Node* insertAfter, DoublyLinkedList& other, Node* beginSeq, Node* endSeq)
	{
		if (!other.mHead || !beginSeq || !endSeq)
			return;

		if (beginSeq->mPrev)
		{
			beginSeq->mPrev->mNext = endSeq->mNext;
		}
		else
		{
			other.mHead = endSeq->mNext;
		}

		if (endSeq->mNext)
		{
			endSeq->mNext->mPrev = beginSeq->mPrev;
		}
		else
		{
			other.mTail = beginSeq->mPrev;
		}

		if (insertAfter->mNext)
		{
			insertAfter->mNext->mPrev = endSeq;
		}
		else
		{
			other.mTail = endSeq;
		}

		endSeq->mNext = insertAfter->mNext;
		insertAfter->mNext = beginSeq;
		beginSeq->mPrev = insertAfter;
	}

	void PrintList() const
	{
		Node* current = mHead;

		while (current)
		{
			std::cout << current->mData;

			if (current->mNext)
			{
				std::cout << " -> ";
			}

			current = current->mNext;
		}

		std::cout << std::endl;
	}

};

int main()
{
	DoublyLinkedList l1;

	// Checking an empty list
	if (l1.At(0).has_value())
	{
		std::cout << l1.At(0).value() << std::endl;
	}
	else
	{
		std::cout << "Invalid index!" << std::endl;
	}
	std::cout << "Is the list empty? " << std::boolalpha << bool(l1.Empty()) << std::endl;

	// PushBack() and PushFront()
	l1.PushBack(47);
	l1.PushBack(48);
	l1.PushFront(46);
	l1.PushFront(45);

	// PrintList()
	std::cout << "List 1: ";
	l1.PrintList();

	// GetSize()
	std::cout << "Size of List 1: " << l1.GetSize(l1.mHead) << std::endl;

	// At()
	std::cout << "Element at index 2: " << l1.At(2).value() << std::endl;

	// operator[]
	std::cout << "Element at index 0: " << l1[0].value() << std::endl;

	// Resize()
	l1.Resize(6);
	std::cout << "List 1 after resize: ";
	l1.PrintList();

	// Erase()
	l1.Erase(2);
	std::cout << "List 1 after erasing element at index 2: ";
	l1.PrintList();

	// Insert()
	l1.Insert(l1.mTail, 47);
	std::cout << "List 1 after inserting 47 after tail node: ";
	l1.PrintList();

	// PopFront() and PopBack()
	l1.PopFront();
	l1.PopBack();
	std::cout << "List 1 after popping front and back: ";
	l1.PrintList();

	DoublyLinkedList l2;
	l2.PushBack(99);
	l2.PushBack(100);
	std::cout << "List 2: ";
	l2.PrintList();

	// Merge()
	l1.Merge(l2);
	std::cout << "List 1 after merging with List 2: ";
	l1.PrintList();

	// Splice()
	Node* insertAfter = l1.mHead->mNext;
	Node* beginSeq = l2.mHead;
	Node* endSeq = l2.mTail;
	l1.Splice(insertAfter, l2, beginSeq, endSeq);

	std::cout << "List 1 after splicing List 2: ";
	l1.PrintList();
	std::cout << "List 2 after splicing: ";
	l2.PrintList();

	// Clear()
	l1.Clear();
	std::cout << "List 1 after clearing: ";
	l1.PrintList();

	return 0;
}