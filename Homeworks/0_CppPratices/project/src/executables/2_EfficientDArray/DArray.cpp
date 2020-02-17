// implementation of class DArray
#include "DArray.h"
#include<iostream>
// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) {
	Reserve(nSize);//allocate enough memory
	m_nSize = nSize;
	for (int i = 0; i != m_nSize; ++i) 
	{
		m_pData[i] = dValue;
	}
}

DArray::DArray(const DArray& arr) {
	m_pData = new double[arr.GetSize()];
	for (int i = 0; i < arr.GetSize(); ++i) {
		m_pData[i] = arr.GetAt(i);
	}
	m_nSize = arr.GetSize();
	m_nMax = m_nSize;
}

// deconstructor
DArray::~DArray() {
	Free();
}

// display the elements of the array
void DArray::Print() const {
	for (int i = 0; i != m_nSize; ++i) 
	{
		std::cout << " " << m_pData[i];
	}
	std::cout << std::endl;
}

// initilize the array
void DArray::Init() {
	m_nSize = 0;
	m_nMax = 0;
	m_pData = nullptr;
}

// free the array
void DArray::Free() {
	delete m_pData;
}

// get the size of the array
int DArray::GetSize() const {
	return m_nSize;
}

// set the size of the array
void DArray::SetSize(int nSize) {
	if (nSize < m_nSize) {
		std::cerr << "too small" << std::endl;
	}
	Reserve(nSize);
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	if (nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex];
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		return;
	}
	m_pData[nIndex] = dValue;
}

//allocate enough memory
void DArray::Reserve(int nSize) {
	auto pNewData = new double[nSize]();
	for (int i = 0; i != m_nSize; ++i) {
		pNewData[i] = m_pData[i];
	}
	Free(); //free old memory
	m_pData = pNewData;
	m_nMax = nSize;

}

// overload operator '[]'
double& DArray::operator[](int nIndex) {
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		static double ERROR;
		return ERROR;
	}
	return m_pData[nIndex];
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		return 0;
	}
	return m_pData[nIndex];
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	if (m_nSize+1 > m_nMax) 
	{
		if (m_nMax == 0)
			Reserve(1);
		else
		{
			Reserve(2 * m_nMax);
		}
	}
	m_pData[m_nSize ] = dValue;
	++m_nSize;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	if (nIndex < 0 || nIndex >= m_nSize)
	{
		return;
	}
	for (int i = nIndex; i < m_nSize - 1; ++i) {
		m_pData[i] = m_pData[i + 1];
	}
	--m_nSize;
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	if (nIndex < 0 || nIndex > m_nSize)
	{
		std::cerr << "out of range!" << std::endl;
		return;
	}
	if (m_nSize+1 > m_nMax)//if no enough space
	{
		if (m_nMax == 0)
			Reserve(1);
		else
		{
			Reserve(2 * m_nMax);
		}
	}
	for (int i = m_nSize; i != nIndex; --i) {
		m_pData[i] = m_pData[i-1];
	}
	m_pData[nIndex] = dValue;
	++m_nSize;

}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	Reserve(arr.GetSize());
	m_nSize = arr.GetSize();
	for (int i = 0; i != m_nSize; ++i)
	{
		m_pData[i] = arr.GetAt(i);
	}
	return *this;
}
