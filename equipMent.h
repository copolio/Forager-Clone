#pragma once
#include "inventory_slot.h"

class equipMent
{
private:

	vector<inventory_slot*> player_equip;

	targetingBox* _targetBox;

	bool isCheck;
	bool istargetBox;
public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void mouse_targetBox();
	void setIsCheck(bool check) {
		isCheck = check;
	}
};

