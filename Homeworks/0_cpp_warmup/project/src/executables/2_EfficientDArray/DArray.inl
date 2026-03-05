#ifndef DARRAY_INL_INCLUDED
#define DARRAY_INL_INCLUDED

#ifndef DARRAY_HEADER_INCLUDED
#include "DArray.h"
#endif

#include <iostream>

#include <assert.h>

using namespace std;

template<typename T>
DArray<T>::DArray() {
	Init();
}

template<typename T>
DArray<T>::DArray(int nSize, T dValue)
	: m_pData(new T[nSize]), m_nSize(nSize), m_nMax(nSize)
{
	for (int i = 0; i < nSize; i++) {
		m_pData[i] = dValue;
	}
}

template<typename T>
DArray<T>::DArray(const DArray<T>& arr)
	: m_pData(new T[arr.GetSize()]), m_nSize(arr.GetSize()), m_nMax(arr.GetSize())
{
	for (int i = 0; i < arr.GetSize(); i++) {
		m_pData[i] = arr[i];
	}
}

template<typename T>
DArray<T>::~DArray() {
	Free();
}

template<typename T>
void DArray<T>::Print() const {
	for (int i = 0; i < m_nSize; i++)
		cout << " " << GetAt(i);

	cout << endl;
}

template<typename T>
void DArray<T>::Init() {
	m_pData = nullptr;
	m_nSize = 0;
	m_nMax = 0;
}

template<typename T>
void DArray<T>::Free() {
	delete[] m_pData;
	m_nMax = 0;
	m_nSize = 0;
	m_pData = nullptr;
}

template<typename T>
int DArray<T>::GetSize() const {
	return m_nSize;
}

template<typename T>
void DArray<T>::Reserve(int nSize) {
	if (m_nMax >= nSize)
		return;

	while (m_nMax < nSize) {
		if (m_nMax == 0) m_nMax = 1;
		m_nMax *= 2;
	}

	T* pData = new T[m_nMax];
	for (int i = 0; i < m_nSize; i++) {
		pData[i] = m_pData[i];
	}

	delete[] m_pData;
	m_pData = pData;
}

template<typename T>
void DArray<T>::SetSize(int nSize) {
	if (m_nSize == nSize) {
		return;
	}

	Reserve(nSize);
	for (int i = m_nSize; i < nSize; i++) {
		m_pData[i] = static_cast<T>(0);
	}
	m_nSize = nSize;
}

template<typename T>
const T& DArray<T>::GetAt(int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

template<typename T>
void DArray<T>::SetAt(int nIndex, T dValue) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
}

template<typename T>
T& DArray<T>::operator[](int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

template<typename T>
const T& DArray<T>::operator[](int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

template<typename T>
void DArray<T>::PushBack(T dValue) {
	Reserve(m_nSize + 1);

	m_pData[m_nSize] = dValue;
	m_nSize++;
}

template<typename T>
void DArray<T>::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	for (int i = nIndex + 1; i < m_nSize; i++) {
		m_pData[i - 1] = m_pData[i];
	}

	m_nSize -= 1;
}

template<typename T>
void DArray<T>::InsertAt(int nIndex, T dValue) {
	assert(nIndex >= 0 && nIndex <= m_nSize);
	Reserve(m_nSize + 1);

	for (int i = m_nSize; i > nIndex; i--) {
		m_pData[i] = m_pData[i - 1];
	}

	m_pData[nIndex] = dValue;
	m_nSize++;
}

template<typename T>
DArray<T>& DArray<T>::operator = (const DArray<T>& arr) {
	if (this == &arr)
		return *this;

	Reserve(arr.GetSize());
	m_nSize = arr.GetSize();

	for (int i = 0; i < arr.GetSize(); i++) {
		m_pData[i] = arr[i];
	}
	return *this;
}

#endif