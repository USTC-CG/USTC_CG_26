// implementation of class DArray
#include "DArray.h"
#include <iostream>

// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) {
	Init();

	//Error
	if (nSize < 0) {
		std::cout << "Cannot set array size which is less than 0!" << std::endl;
		return;
	}
	if (nSize == 0) {
		m_pData = nullptr;
		m_nSize = 0;
		return;
	}
	m_nSize = nSize;
	m_pData = new double[m_nSize];
	for (int i = 0; i < m_nSize; i++) {
		m_pData[i] = dValue;
	}

}

DArray::DArray(const DArray& arr) {
	Init();
	m_nSize = arr.m_nSize;

	if (m_nSize > 0) {
		m_pData = new double[m_nSize];
		for (int i = 0; i < m_nSize; i++) {
			m_pData[i] = arr.m_pData[i];
		}
	}	
}

// deconstructor
DArray::~DArray() {
	Free();
}

// display the elements of the array
void DArray::Print() const {
	if (m_nSize == 0) {
		std::cout << "The array is empty!" << std::endl;
		return;
	}
	for (int i = 0; i < m_nSize; i++) {
		std::cout << m_pData[i] << " ";
	}
	std::cout << std::endl;
}

// initilize the array
void DArray::Init() {
	m_nSize = 0;
	m_pData = nullptr;
}

// free the array
void DArray::Free() {
	m_nSize = 0;
	if (m_pData != nullptr) {
		delete[] m_pData;
		m_pData = nullptr;
	}

}

// get the size of the array
int DArray::GetSize() const {
	return m_nSize;
}

// set the size of the array
void DArray::SetSize(int nSize) {
	//Error
	if (nSize < 0) {
		std::cout << "Cannot set array size which is less than 0!" << std::endl;
		return;
	}

	else if (nSize == 0) {
		Free();
		return;
	}

	else if (nSize <= m_nSize) {
		m_nSize = nSize;
		return;
	}

	else if (nSize > m_nSize) {
		double* pNewData = new double[nSize];
		for (int i = 0; i < m_nSize; i++) {
			pNewData[i] = m_pData[i];
		}
		for (int i = m_nSize; i < nSize; i++) {
			pNewData[i] = 0;
		}
		delete[] m_pData;
		m_pData = pNewData;
		m_nSize = nSize;
	}

}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	if (nIndex < 0 || nIndex >= m_nSize) {
		std::cout << "Index is invalid in GetAt()! Returning default value." << std::endl;
		static double error = 0.0;
		return error;
	}

	else {
		return m_pData[nIndex];
	}
}

double& DArray::operator[](int nIndex) {
	if (nIndex < 0 || nIndex >= m_nSize) {
		std::cout << "Index is invalid in operator[]! Returning default value." << std::endl;
		static double error = 0.0;
		return error;
	}

	else {
		return m_pData[nIndex];
	}
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	if (nIndex < 0 || nIndex >= m_nSize) {
		std::cout << "Index is invalid in SetAt()! No value is set." << std::endl;
		return;
	}

	else {
		m_pData[nIndex] = dValue;
	}
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	return GetAt(nIndex);
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	double* pNewdata = new double[m_nSize + 1];
	for (int i = 0; i < m_nSize; i++) {
		pNewdata[i] = m_pData[i];
	}
	pNewdata[m_nSize] = dValue;
	delete[] m_pData;
	m_pData = pNewdata;
	m_nSize++;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	//Error
	if (nIndex < 0 || nIndex >= m_nSize) {
		std::cout << "Index is invalid in DeleteAt()! No element is deleted." << std::endl;
		return;
	}

	else {
		double* pNewData = new double[m_nSize - 1];
		for (int i = 0; i < nIndex; i++) {
			pNewData[i] = m_pData[i];
		}
		for (int i = nIndex + 1; i < m_nSize; i++) {
			pNewData[i - 1] = m_pData[i];
		}
		delete[] m_pData;
		m_pData = pNewData;
		m_nSize--;
	}
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	//Error
	if (nIndex < 0 || nIndex > m_nSize) {
		std::cout << "Index is invalid in InsertAt()! No element is inserted." << std::endl;
		return;
	}

	else {
		double* pNewData = new double[m_nSize + 1];
		for (int i = 0; i < nIndex; i++) {
			pNewData[i] = m_pData[i];
		}
		pNewData[nIndex] = dValue;
		for (int i = nIndex; i < m_nSize; i++) {
			pNewData[i + 1] = m_pData[i];
		}
		delete[] m_pData;
		m_pData = pNewData;
		m_nSize++;
	}
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	if (this == &arr) {
		return *this;
	}

	Free();

	m_nSize = arr.m_nSize;
	if (m_nSize > 0) {
		m_pData = new double[m_nSize];
		for (int i = 0; i < m_nSize; i++) {
			m_pData[i] = arr.m_pData[i];
		}
	}

	else
	{
		m_pData = nullptr;
	}

	return *this;
}
