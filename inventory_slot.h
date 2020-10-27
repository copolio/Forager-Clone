#pragma once
#include "item.h"

class inventory_slot
{
public:
	float x, y;
	RECT _rc;
	tagItem	_item;
	bool isCheck;
	int count;
};