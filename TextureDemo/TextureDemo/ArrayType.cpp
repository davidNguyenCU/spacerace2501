#include "ArrayType.h"

template <class T>
ArrayType<T>::ArrayType()
{
	elements = new T[10];
}

template <class T>
ArrayType<T>::ArrayType(int size) 
{
	elements = new T[size];
}

template <class T>
void ArrayType<T>::add(T * entity) {
	int availableIndex = findFirstAvailableSpace();
	if (availableIndex < 0) return;

	elements[availableIndex] = entity;
	size++;
}

template <class T>
void ArrayType<T>::remove(T * entity) {
	if (size == 0) {
		std::cout << "EmptyArrayRemoveError" << std::endl;
		return;
	}

	for (int i = 0; i < MAX_CAPACITY; i++) {
		if (elements[i] == entity) elements[i] = NULL;
	}
	size--;
}

template <class T>
int ArrayType<T>::findFirstAvailableSpace() {
	if (size == MAX_CAPACITY) return;

	for (int i = 0; i < MAX_CAPACITY; i++) {
		if (elements[i] == NULL) return i;
	}
	std::cout << "IndexExpectedNullSpaceError" << std::endl;
	return -1;
}

template <class T>
T * ArrayType<T>::get(int index) {
	if (size == 0) {
		std::cout << "GetFromEmptyArrayError" << std::endl;
		return NULL;
	}

	return elements[index];
}