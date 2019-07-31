#pragma once

#include "Bullet.h"
#include "ArrayType.h"

template <class Bullet>
class BulletArray<Bullet> : ArrayType<Bullet> {
public:
	BulletArray();

private:
	const static int MAX_CAPACITY = 10;
	//Bullet * elements[MAX_CAPACITY];
};