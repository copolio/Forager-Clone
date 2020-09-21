#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{

	IMAGEMANAGER->addImage("Q", "Images/이미지/GUI/Q버튼.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("E", "Images/이미지/GUI/E버튼.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("커서", "Images/이미지/GUI/커서.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("img_UI_TargetingBox", "Images/이미지/GUI/img_UI_TargetingBox.bmp", 48, 12,4,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_UI_ItemTooltip", "Images/이미지/GUI/img_UI_ItemTooltip.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_slot", "Images/이미지/GUI/img_UI_InventorySlotBoundary.bmp", 88, 88, true, RGB(255, 0, 255));
	targetBox[0].img_num = 0;
	targetBox[1].img_num = 1;
	targetBox[2].img_num = 2;
	targetBox[3].img_num = 3;

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 8; j++) {

			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->Kinds = ITEM_NULL;
			inven->x = 80 + j * 95;
			inven->y = 150 + i * 95;
			inven->count = 0;
			inven->img_name = "";
			inven->_rc = RectMake( inven->x, inven->y, 88, 88);
			player_inventory.push_back(inven);
		}
	}
	istargetBox = false;
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
	if (isCheck) {
		mouse_targetBox();
	}
	
}

void inventory::render()
{
	if (isCheck) {
		for (int i = 0; i < player_inventory.size(); i++) {
			//Rectangle(getMemDC(), player_inventory[i]->_rc);
			IMAGEMANAGER->render("item_slot", getMemDC(), player_inventory[i]->_rc.left, player_inventory[i]->_rc.top);
		}

		if (istargetBox) {
			for (int i = 0; i < 4; i++) {
				IMAGEMANAGER->frameRender("img_UI_TargetingBox", getMemDC(), targetBox[i].x, targetBox[i].y, targetBox[i].img_num, 0);
			}

		}
	}

}

void inventory::itemRemove()
{

}

void inventory::mouse_targetBox()
{
	for (int i = 0; i < player_inventory.size(); i++) {
		if (PtInRect(&player_inventory[i]->_rc, _ptMouse)) {
			mouse_setingRc(player_inventory[i]->_rc);
			istargetBox = true;
			break;
		}
	}
}

void inventory::mouse_setingRc(RECT rc )
{
	targetBox[0].x = rc.left-5;
	targetBox[0].y = rc.top-5;

	targetBox[1].x = rc.right-7;
	targetBox[1].y = rc.top-5;

	targetBox[2].x = rc.right-7;
	targetBox[2].y = rc.bottom - 7;

	targetBox[3].x = rc.left-5;
	targetBox[3].y = rc.bottom-7;
}
