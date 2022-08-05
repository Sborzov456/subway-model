#pragma once
#include <iostream>
#include <exception>
#define SPECIFIC_SIZE 3
using namespace std;

template <class T> class ArrayIterator : public iterator<input_iterator_tag, T>
{
private:
	T* it;
public:
	ArrayIterator(T* p) : it(p) {}
	bool operator == (const ArrayIterator<T>& other) { return this->it == other.it; }
	bool operator != (const ArrayIterator<T>& other) { return this->it != other.it; }
	ArrayIterator& operator ++ () {
		++it;
		return *this;
	}
	ArrayIterator& operator ++ (int) {
		++it;
		return *this;
	}
	T& operator * () const { return *it; }
};

template <class T, size_t MAX_SIZE> class Array
{
private:
	T arr[MAX_SIZE];
	int _size;
public:
	Array() : arr(), _size(0) {}
	Array(const Array<T, MAX_SIZE>& other) {
		for (int i = 0; i < other._size; i++)
			arr[i] = other.arr[i];
		_size = other._size;
	}
	~Array() = default;
	const int size() const { return _size; }
	bool empty() const { return _size == 0 ? true : false; }
	bool full() const { return _size == MAX_SIZE ? true : false; }
	bool find(const T& value) const
	{
		for (int i = 0; i < _size; i++) {
			if (arr[i] == value) return true;
		}
		return false;
	}
	T& operator [] (const int& index) 
	{
		if (index < 0 || index >= MAX_SIZE)
			throw exception("Index out of range!\n");
		else return arr[index];
	}
	const T& operator [] (const int& index) const
	{
		if (index < 0 || index >= MAX_SIZE)
			throw exception("Index out of range!\n");
		else return arr[index];
	}
	Array<T, MAX_SIZE>& operator += (const T& value)
	{
		if (_size == MAX_SIZE)
			throw("Array is full!\n");
		else {
			arr[_size] = value;
			++_size;
		}
		return *this;
	}
	Array<T, MAX_SIZE>& operator = (const Array<T, MAX_SIZE>& other)
	{
		if (this == &other) {
			return *this;
		}
		for (size_t i = 0; i < MAX_SIZE; i++)
			arr[i] = other.arr[i];
		_size = other._size;
		return *this;
	}
	

	typedef ArrayIterator<T> iterator;
	typedef ArrayIterator<const T> const_iterator;

	iterator begin() { return iterator(arr); }
	iterator end() { return iterator(arr + MAX_SIZE); }

	const_iterator begin() const { return const_iterator(arr); }
	const_iterator end() const { return const_iterator(arr + MAX_SIZE); }
};
