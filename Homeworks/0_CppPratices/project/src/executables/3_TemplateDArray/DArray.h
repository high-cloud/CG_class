#pragma once
#ifndef _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_

#include<iostream>
// interfaces of Dynamic Array class DArray
template <typename T>
class DArray
{
public:
	DArray();							  // default constructor
	DArray(int nSize, T dValue = 0); // set an array with default values
	DArray(const DArray& arr);			  // copy constructor
	~DArray();							  // deconstructor

	void Print() const; // print the elements of the array

	int GetSize() const;	 // get the size of the array
	void SetSize(int nSize); // set the size of the array

	const T& GetAt(int nIndex) const; // get an element at an index
	void SetAt(int nIndex, T dValue); // set the value of an element

	T& operator[](int nIndex);				// overload operator '[]'
	const T& operator[](int nIndex) const; // overload operator '[]'

	void PushBack(T dValue);			  // add a new element at the end of the array
	void DeleteAt(int nIndex);				  // delete an element at some index
	void InsertAt(int nIndex, T dValue); // insert a new element at some index

	DArray& operator=(const DArray& arr); //overload operator '='

private:
	T* m_pData; // the pointer to the array memory
	int m_nSize;	 // the size of the array
	int m_nMax;		 // the size of memory

private:
	void Init();			 // initilize the array
	void Free();			 // free the array
	void Reserve(int nSize); // allocate enough memory
};
//---------------------define----------------
// default constructor
template <typename T>
DArray<T>::DArray()
{
	Init();
}

// set an array with default values
template <typename T>
DArray<T>::DArray(int nSize, T dValue)
{
	Reserve(nSize); //allocate enough memory
	m_nSize = nSize;
	for (int i = 0; i != m_nSize; ++i)
	{
		m_pData[i] = dValue;
	}
}

template <typename T>
DArray<T>::DArray(const DArray& arr)
{
	m_pData = new T[arr.GetSize()];
	for (int i = 0; i < arr.GetSize(); ++i)
	{
		m_pData[i] = arr.GetAt(i);
	}
	m_nSize = arr.GetSize();
	m_nMax = m_nSize;
}

// deconstructor
template <typename T>
DArray<T>::~DArray()
{
	Free();
}

// display the elements of the array
template <typename T>
void DArray<T>::Print() const
{
	for (int i = 0; i != m_nSize; ++i)
	{
		std::cout << " " << m_pData[i];
	}
	std::cout << std::endl;
}

// initilize the array
template <typename T>
void DArray<T>::Init()
{
	m_nSize = 0;
	m_nMax = 0;
	m_pData = nullptr;
}

// free the array
template <typename T>
void DArray<T>::Free()
{
	delete m_pData;
}

// get the size of the array
template <typename T>
int DArray<T>::GetSize() const
{
	return m_nSize;
}

// set the size of the array
template <typename T>
void DArray<T>::SetSize(int nSize)
{
	if (nSize < m_nSize)
	{
		std::cerr << "too small" << std::endl;
	}
	Reserve(nSize);
}

// get an element at an index
template <typename T>
const T& DArray<T>::GetAt(int nIndex) const
{
	if (nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex];
}

// set the value of an element
template <typename T>
void DArray<T>::SetAt(int nIndex, T dValue)
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		return;
	}
	m_pData[nIndex] = dValue;
}

//allocate enough memory
template <typename T>
void DArray<T>::Reserve(int nSize)
{
	auto pNewData = new T[nSize]();
	for (int i = 0; i != m_nSize; ++i)
	{
		pNewData[i] = m_pData[i];
	}
	Free(); //free old memory
	m_pData = pNewData;
	m_nMax = nSize;
}

// overload operator '[]'
template <typename T>
T& DArray<T>::operator[](int nIndex)
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		static T ERROR;
		return ERROR;
	}
	return m_pData[nIndex];
}

// overload operator '[]'
template <typename T>
const T& DArray<T>::operator[](int nIndex) const
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		return 0;
	}
	return m_pData[nIndex];
}

// add a new element at the end of the array
template <typename T>
void DArray<T>::PushBack(T dValue)
{
	if (m_nSize + 1 > m_nMax)
	{
		if (m_nMax == 0)
			Reserve(1);
		else
		{
			Reserve(2 * m_nMax);
		}
	}
	m_pData[m_nSize] = dValue;
	++m_nSize;
}

// delete an element at some index
template <typename T>
void DArray<T>::DeleteAt(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		return;
	}
	for (int i = nIndex; i < m_nSize - 1; ++i)
	{
		m_pData[i] = m_pData[i + 1];
	}
	--m_nSize;
}

// insert a new element at some index
template <typename T>
void DArray<T>::InsertAt(int nIndex, T dValue)
{
	if (nIndex < 0 || nIndex > m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		return;
	}
	if (m_nSize + 1 > m_nMax) //if no enough space
	{
		if (m_nMax == 0)
			Reserve(1);
		else
		{
			Reserve(2 * m_nMax);
		}
	}
	for (int i = m_nSize; i != nIndex; --i)
	{
		m_pData[i] = m_pData[i - 1];
	}
	m_pData[nIndex] = dValue;
	++m_nSize;
}

// overload operator '='
template <typename T>
DArray<T>& DArray<T>::operator=(const DArray& arr)
{
	Reserve(arr.GetSize());
	m_nSize = arr.GetSize();
	for (int i = 0; i != m_nSize; ++i)
	{
		m_pData[i] = arr.GetAt(i);
	}
	return *this;
}

#endif // !_DYNAMICARRAY_H_