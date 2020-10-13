#pragma once
#include "inventory_slot.h"
#include "targetingBox.h"
class quick_slot
{
private:
	vector<inventory_slot*> _quick;
	targetingBox* _targetBox;
	int targetnum;
public:
	
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void quick_slot_update();
	void target(int i);

	void quick_slot_target_Move();
	inventory_slot* GetQuickSlotNumber() { return _quick[targetnum]; };
};

