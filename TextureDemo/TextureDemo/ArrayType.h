#pragma once

template <class T>
class ArrayType {
public:
	ArrayType();
	ArrayType(int size);
	void add(T * newBullet);
	//remove(int index);
	void remove(T * bullet);
	T * get(int index);

private:
	T ** elements;
	int size;
	int findFirstAvailableSpace();
};