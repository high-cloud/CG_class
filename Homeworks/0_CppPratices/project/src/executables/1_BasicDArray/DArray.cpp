// implementation of class DArray
#include "DArray.h"
#include <iostream>
// default constructor
DArray::DArray()
{
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue)
{
	SetSize(nSize);
	for(int i=0;i<nSize;++i){
		m_pData[i]=dValue;
	}
	m_nSize=nSize;
}

DArray::DArray(const DArray &arr)
{
	m_pData=new double[arr.GetSize()];
	for(int i=0;i<arr.GetSize();++i){
		m_pData[i]=arr.GetAt(i);
	}
	m_nSize=arr.GetSize();
}

// deconstructor
DArray::~DArray()
{
	Free();
}

// display the elements of the array
void DArray::Print() const
{
	for(int i=0;i!=m_nSize;++i){
		std::cout<<" "<<m_pData[i];
	}
}

// initilize the array
void DArray::Init()
{
	m_nSize = 0;
	m_pData = nullptr;
}

// free the array
void DArray::Free()
{
	if (m_pData != nullptr)
	{
		delete[] m_pData;
		m_pData = nullptr;
	}
}

// get the size of the array
int DArray::GetSize() const
{
	return m_nSize;
} 

// set the size of the array
void DArray::SetSize(int nSize)
{
	Free();
}

// get an element at an index
const double &DArray::GetAt(int nIndex) const
{
	if (nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex];
}

// set the value of an element
void DArray::SetAt(int nIndex, double dValue)
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		return;
	}
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
const double &DArray::operator[](int nIndex) const
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		return 0;
	}
	return m_pData[nIndex];
}

// add a new element at the end of the array
void DArray::PushBack(double dValue)
{
	auto pNewData = new double[m_nSize + 1];
	for (int i = 0; i != m_nSize; ++i)
	{
		pNewData[i] = m_pData[i];
	}
	pNewData[m_nSize] = dValue;
	Free();
	m_pData = pNewData;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		return;
	}
	auto pNewData = new double[m_nSize - 1];
	for (int i = 0; i != nIndex; ++i)
		pNewData[i] = m_pData[i];
	for (int i = nIndex + 1; i < m_nSize; i++)
	{
		pNewData[i - 1] = m_pData[i];
	}
	Free();
	m_pData = pNewData;
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue)
{
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		return;
	}
	auto pNewData = new double[m_nSize + 1];
	for (int i = 0; i < nIndex; ++i)// the half before nIndex
	{
		pNewData[i] = m_pData[i];
	}
	pNewData[nIndex] = dValue;
	for (int i = nIndex + 1; i <= m_nSize; ++i)// the half behine nIndex
	{
		pNewData[i] = m_pData[i - 1];
	}
	Free();
	m_pData=pNewData;
}

// overload operator '='
DArray &DArray::operator=(const DArray &arr)
{
	Free();
	m_pData=new double[arr.GetSize()];
	for(int i=0;i<arr.GetSize();++i){
		m_pData[i]=arr.GetAt(i);
	}
	m_nSize=arr.GetSize();
	return *this;
}
