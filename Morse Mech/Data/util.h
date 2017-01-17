#ifndef _UTIL_H_
#define _UTIL_H_

template<typename T> T min(T x, T y) {
	return (x < y) ? x : y;
}
template<typename T> T max(T x, T y) {
	return (x > y) ? x : y;
}

#endif	// _UTIL_H_
