#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <util/atomic.h>
#include "util.h"

template<typename T>
class queue {
private:
	T* m_data = nullptr;
	int m_front, m_back, m_max_size;
	bool m_is_empty;
	
public:
	queue(T buf[], int buf_max_size) :
		m_front(buf_max_size),
		m_back(buf_max_size),
		m_max_size(buf_max_size),
		m_is_empty(true) {
		m_data = (m_max_size > 0) ? buf : nullptr;
	}
		
	// Element access
	// TODO: These should error out if the queue is empty
	T front()			{ return m_is_empty ? T() : m_data[m_front]; }
	T front() volatile	{ ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { return front(); } }
	T back()			{ return m_is_empty ? T() : m_data[m_back]; }
	T back() volatile	{ ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { return back(); } }
		
	// Capacity
	bool empty() volatile	{ return m_is_empty; }
	int max_size() volatile	{ return m_max_size; }
	int size() {
		if (m_is_empty) { return 0; }	// TODO: also error out(?)
		int output = m_back - m_front + 1;
		if (m_front > m_back) {
			output += m_max_size;
		}
		return output;
	}
	int size() volatile { ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { return size(); } }
		
	// Modifiers
	void push(T value) {
		// TODO: error if exceeds limit
		if (size() < m_max_size) {
			if (m_is_empty) {
				m_is_empty = false;
			} else {
				m_front--;
				if (m_front < 0) { m_front += m_max_size; }
			}
			m_data[m_front] = value;
		}
	}
	void push(T value) volatile
		{ ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { push(value); } }
	void pop() {
		if (m_is_empty) { return; }	// TODO: also error out
		if (m_back == m_front) { m_is_empty = true; return; }
		m_back--;
		if (m_back < 0) { m_back += m_max_size; }
	}
	void pop() volatile { ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { pop(); } }
};

#endif	// _QUEUE_H_
