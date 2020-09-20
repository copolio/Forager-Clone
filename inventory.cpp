#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{

	IMAGEMANAGER->addImage("item_slot", "Images/¿ÃπÃ¡ˆ/GUI/img_UI_InventorySlotBoundary.bmp", 88, 88, true, RGB(255, 0, 255));
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 8; j++) {

			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->Kinds = ITEM_NULL;
			inven->x = 80 + j * 95;
			inven->y = 150 + i * 95;
			inven->_rc = RectMake( inven->x, inven->y, 88, 88);
			player_inventory.push_back(inven);
		}
	}
	
	isCheck = false;

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{

	if (INPUT->GetKeyDown('I')) {
		if (isCheck) {
			isCheck = false;
		}
		else {
			isCheck = true;
		}
	}
}

void inventory::render()
{
	if (isCheck) {


		for (int i = 0; i < player_inventory.size(); i++) {
			//Rectangle(getMemDC(), player_inventory[i]->_rc);
			IMAGEMANAGER->render("item_slot", getMemDC(), player_inventory[i]->_rc.left, player_inventory[i]->_rc.top);
		}
	}
}

void inventory::itemRemove()
{
}
