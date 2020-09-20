#pragma once
#include "inventory_slot.h"
#include "gameNode.h"

#define INVENTORY MAX;
class inventory : public gameNode
{

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void itemRemove();
	
	bool isCheck;

private:
	vector<inventory_slot*> player_inventory;
};

