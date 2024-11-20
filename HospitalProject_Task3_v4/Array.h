#pragma once
#include <iostream>
using namespace std;
#include "myRealloc.h"

template<class T>
class Array
{
	T* m_arr;
	int m_arrPhySize;
	int m_arrLogSize;
	char m_delimiter;

public:
	Array(char delimiter = ' ');
	~Array();
	Array(const Array& other);
	const Array& operator=(const Array& other);

	const Array& operator+=(const T& newVal);
	T& operator[](int index);
	const T& operator[](int index) const;
	int getArrLogSize() const;

	friend ostream& operator<<(ostream& os, const Array& arr)
	{
		for (int i = 0; i < arr.logicalSize; i++)
			os << arr.m_arr[i] << arr.m_delimiter;
		return os;
	}
};

template<class T>
Array<T>::Array(char delimiter)
	: m_delimiter(delimiter)
{
	m_arrPhySize = 1;
	m_arrLogSize = 0;
	m_arr = new T[m_arrPhySize];
}

template<class T>
Array<T>::Array(const Array& other) 
	: m_arr(nullptr)
{
	*this = other;
}

template<class T>
Array<T>::~Array()
{
	delete[] m_arr;
}

template<class T>
const Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this != &other)
	{
		delete[] m_arr;
		m_arrPhySize = other.m_arrPhySize;
		m_arrLogSize = other.m_arrLogSize;
		m_delimiter = other.m_delimiter;
		m_arr = new T[m_arrPhySize];
		for (int i = 0; i < m_arrLogSize; i++)
			m_arr[i] = other.m_arr[i];
	}
	return *this;
}

template<class T>
const Array<T>& Array<T>::operator+=(const T& newVal)
{
	if (m_arrLogSize == m_arrPhySize)
	{
		m_arrPhySize *= 2;
		m_arr = (T*)myRealloc::myReallocFunc(m_arr, (m_arrPhySize * sizeof(T)), (m_arrLogSize * sizeof(T)));
	}
	m_arr[m_arrLogSize] = newVal;
	m_arrLogSize++;
	return *this;
}

template<class T>
T& Array<T>::operator[](int index)
{
	return m_arr[index];
}

template<class T>
const T& Array<T>::operator[](int index) const
{
	return m_arr[index];
}

template<class T>
int Array<T>::getArrLogSize() const
{
	return m_arrLogSize;
}
