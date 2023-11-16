/*

1.	Make a vector data structure with the following functions. Does not have to be templated it :
	a.	Empty() – returns true if the list is empty
	b.	Size() – returns the size of the vector
	c.	Capacity() – returns the capacity of the vector
	d.	PushBack() – inserts a new element at the end of the vector. If not capacity is allocated,
		double it
	e.	PopBack() – remove last element
	f.	At() – gets the element at a certain index
	g.	operator[] – gets the element at a certain index
	h.	Resize() – resizes the vector
	i.	Reserve() – allocates capacity for the vector
	j.	Clear() – empties the vector
	k.	Insert() – inserts a new element at a certain spot in the vector
	l.	Erase() – removes an element at a certain spot in the vector

*/

#include <iostream>

struct Vector
{
	int* mData;
	int mSize;
	int mCapacity;

	Vector() : mData(nullptr), mSize(0), mCapacity(0) {}

	~Vector()
	{
		delete[] mData;
	}

	bool Empty() const
	{
		return mSize == 0;
	}

	int GetSize() const
	{
		return mSize;
	}

	int GetCapacity() const
	{
		return mCapacity;
	}

	int CalculateNewCapacity() const
	{
		return mCapacity == 0 ? 1 : mCapacity * 2;
	}

	void Reserve(int newCapacity)
	{
		if (newCapacity > mCapacity)
		{
			int* newData = new int[newCapacity];
			for (int i = 0; i < mSize; ++i)
			{
				newData[i] = mData[i];
			}
			delete[] mData;
			mData = newData;
			mCapacity = newCapacity;
		}
	}

	void PushBack(int data)
	{
		if (mSize == mCapacity)
		{
			Reserve(CalculateNewCapacity());
		}
		mData[mSize++] = data;
	}

	void PopBack()
	{
		if (mSize > 0)
		{
			mSize--;
		}
	}

	int At(int index) const
	{
		if (index >= 0 && index < mSize)
		{
			return mData[index];
		}

		throw std::out_of_range("Error! Index out of range!");
	}

	int operator[](int index) const
	{
		return At(index);
	}

	void Resize(int newSize)
	{
		if (newSize > mSize)
		{
			Reserve(newSize);
			for (int i = mSize; i < newSize; ++i)
			{
				mData[i] = 0;
			}
		}
		mSize = newSize;
	}

	void Clear()
	{
		mSize = 0;
	}

	void Insert(int index, int data)
	{
		if (index >= 0 && index <= mSize)
		{
			if (mSize == mCapacity)
			{
				Reserve(CalculateNewCapacity());
			}
			for (int i = mSize; i > index; --i)
			{
				mData[i] = mData[i - 1];
			}
			mData[index] = data;
			mSize++;
			return;
		}

		throw std::out_of_range("Error! Index out of range!");
	}

	void Erase(int index)
	{
		if (index >= 0 && index < mSize)
		{
			for (int i = index; i < mSize - 1; ++i)
			{
				mData[i] = mData[i + 1];
			}
			mSize--;
			return;
		}

		throw std::out_of_range("Error! Index out of range!");
	}

	void Print() const
	{
		std::cout << "Vector Elements: ";
		for (int i = 0; i < mSize; ++i)
		{
			std::cout << mData[i];
			if (i != mSize - 1)
			{
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}
};

int main()
{
	Vector vec;

	std::cout << "Empty: " << std::boolalpha << vec.Empty() << std::endl;
	std::cout << "Size: " << vec.GetSize() << std::endl;
	std::cout << "Capacity: " << vec.GetCapacity() << std::endl;

	// PushBack()
	vec.PushBack(65);
	vec.PushBack(66);
	vec.PushBack(67);

	// Print()
	vec.Print();

	// Empty() , GetSize() and GetCapacity()
	std::cout << "Empty: " << std::boolalpha << vec.Empty() << std::endl;
	std::cout << "Size: " << vec.GetSize() << std::endl;
	std::cout << "Capacity: " << vec.GetCapacity() << std::endl;

	// At() and operator[]
	std::cout << "Element at index 1: " << vec.At(1) << std::endl;
	std::cout << "Element at index 2: " << vec[2] << std::endl;

	// Resize()
	vec.Resize(5);
	std::cout << "Size after resize: " << vec.GetSize() << std::endl;

	vec.Print();

	// Insert()
	vec.Insert(1, 12);
	std::cout << "Element at index 1 after insertion: " << vec[1] << std::endl;

	// Erase()
	vec.Erase(2);
	std::cout << "Element at index 2 after erasing: " << vec[2] << std::endl;

	// Clear()
	vec.Clear();
	std::cout << "Size after clear: " << vec.GetSize() << std::endl;

	return 0;
}