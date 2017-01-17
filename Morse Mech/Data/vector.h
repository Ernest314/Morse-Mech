#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "util.h"

template<typename T>
class vector {
private:
	T* m_data = nullptr;
	int m_size, m_max_size;

public:
	vector(T buf[], int buf_max_size) :
		m_size(0),
		m_max_size(buf_max_size) {
		m_data = (m_max_size > 0) ? buf : nullptr;	// TODO: error if buf_max_size <= 0
	}
	vector(T buf[], int buf_max_size, int count, T value=T()) :
		m_max_size(buf_max_size) {
		m_size = min(count, m_max_size);	// TODO: error if size_limit reached
		m_data = (m_max_size > 0) ? buf : nullptr;	// TODO: error if buf_max_size <= 0
			
		for (int i=0; i<size; ++i) {
			m_data[i] = value;
		}
	}
		
	// Element access
	T& operator[](int index)	{ return m_data[index]; }
	T at(int index)				{ return m_data[index]; }
	T front()		{ return m_data[0]; }
	T back()		{ return m_data[m_size]; }
		
	// Capacity
	bool empty()	{ return (m_size == 0); }
	int max_size()	{ return m_max_size; }
	int size()		{ return m_size; }
		
	// Modifiers
	void clear()	{ m_size = 0; }
	void insert(int index, T value) {
		// TODO: error if exceeds limit
		if (m_size < m_max_size && index <= m_size) {
			for (int i=m_size; i>index; ++i) {
				m_data[i] = m_data[i-1];
			}
			m_size++;
			m_data[index] = value;
		}
	}
	//void insert(int index, int count, T value);
	//void erase(int index);
	//void erase(int begin, int end);	// [begin, end)
	void push_back(T value) {
		// TODO: error if exceeds limit
		if (m_size < m_max_size) {
			m_data[m_size] = value;	// `m_size` guaranteed >= 0
			m_size++;
		}
	}
	void pop_back() {
		if (m_size > 0) { m_size--; }
	}
	//void resize(int size, T value=T());
};

#endif // _VECTOR_H_
