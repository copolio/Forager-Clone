#pragma once
#include "inventory_slot.h"
class quick_slot
{
private:
	vector<inventory_slot*> _quick;
public:

	void render(HDC hdc);
	void quick_slot_update();
};

