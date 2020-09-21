#pragma once
#include "inventory_slot.h"
#include "gameNode.h"
struct mouse_rc
{
	float x, y;
	int img_num;

};
class inventory : public gameNode
{

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void itemRemove();
	void mouse_targetBox();
	void mouse_setingRc(RECT rc);
	bool isCheck;

private:
	vector<inventory_slot*> player_inventory;

	mouse_rc targetBox[4];

	bool istargetBox;
};

