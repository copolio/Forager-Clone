#include "stdafx.h"
#include "inventory.h"


HRESULT inventory::init()
{
	IMAGEMANAGER->addImage("Q", "Images/이미지/GUI/Q버튼.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("E", "Images/이미지/GUI/E버튼.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("커서", "Images/이미지/GUI/커서.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inventory_Kinds", "Images/이미지/GUI/inventory_Kinds.bmp", 383, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_item_icon", "Images/이미지/GUI/img_item_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_equip_icon", "Images/이미지/GUI/img_equip_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Img_UI_EquipmentSlotFilled", "Images/이미지/GUI/Img_UI_EquipmentSlotFilled.bmp", 72, 72, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("img_UI_TargetingBox", "Images/이미지/GUI/img_UI_TargetingBox.bmp", 48, 12,4,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_UI_ItemTooltip", "Images/이미지/GUI/img_UI_ItemTooltip.bmp", 296, 216, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_slot", "Images/이미지/GUI/img_UI_InventorySlotBoundary.bmp", 88, 88, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_equip_slot", "Images/이미지/GUI/img_equip_slot.bmp", 582, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pick", "Images/이미지/아이템/곡괭이.bmp", 56, 56, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("0", "Images/이미지/GUI/0.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1", "Images/이미지/GUI/1.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "Images/이미지/GUI/2.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3", "Images/이미지/GUI/3.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4", "Images/이미지/GUI/4.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5", "Images/이미지/GUI/5.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("6", "Images/이미지/GUI/6.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("7", "Images/이미지/GUI/7.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "Images/이미지/GUI/8.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("9", "Images/이미지/GUI/9.bmp", 15, 19, true, RGB(255, 0, 255));

	targetBox[0].img_num = 0;
	targetBox[1].img_num = 1;
	targetBox[2].img_num = 2;
	targetBox[3].img_num = 3;

	inven_kinds = ITEM;
	for (int i = 1; i < 10; i++) {
		item_count[i-1] = i;
	}
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 8; j++) {

			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->Kinds = ITEM_NULL;
			inven->x = 80 + j * 95;
			inven->y = 150 + i * 95;
			inven->count = 0;
			inven->item_name = "";
			inven->img_name = "";
			inven->_rc = RectMake( inven->x, inven->y, 88, 88);
			player_inventory.push_back(inven);
		}
	}

	for (int i = 0; i < 7; i++) {
		inventory_slot* inven = new inventory_slot;
		inven->isCheck = false;
		inven->Kinds = ITEM_NULL;
		inven->x = 364+ i * 80;
		inven->y = WINSIZEY/2+15 ;
		inven->count = 0;
		inven->img_name = "";
		inven->_rc = RectMake(inven->x, inven->y, 72, 72);
		player_equip.push_back(inven);
	}
	player_equip[0]->Kinds = ITEM_EQUIP;
	player_equip[0]->img_name = "pick";
	istargetBox = false;
	isCheck = false;

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{
	keyDown();
	if (isCheck) {
		mouse_targetBox();
	}
	item_check();
}

void inventory::render()
{

	for (int i = 0; i < player_equip.size();i++) {

		if (player_equip[i]->Kinds != ITEM_EQUIP) continue;
			player_Quick_slot.push_back(player_equip[i]);
		
		
	}
	if (isCheck) {
		IMAGEMANAGER->render("inventory_Kinds", getMemDC(), WINSIZEX/2-180, 15);
		IMAGEMANAGER->render("Q", getMemDC(), 400, 70);
		IMAGEMANAGER->render("E", getMemDC(), 850, 70);
		switch (inven_kinds)
		{
		case ITEM:
			IMAGEMANAGER->render("img_item_icon", getMemDC(), 562, 30);
			for (int i = 0; i < player_inventory.size(); i++) {
				//Rectangle(getMemDC(), player_inventory[i]->_rc);
				IMAGEMANAGER->render("item_slot", getMemDC(), player_inventory[i]->_rc.left, player_inventory[i]->_rc.top);
				if (player_inventory[i]->img_name != "") {
					IMAGEMANAGER->render(player_inventory[i]->img_name, getMemDC(), player_inventory[i]->_rc.left+15, player_inventory[i]->_rc.top+15);
				}
				int item_count = player_inventory[i]->count;
				int c=0;
				while (item_count != NULL) {
					switch (item_count %10)
					{
					case 0:
						IMAGEMANAGER->render(to_string(0), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 1:
						IMAGEMANAGER->render(to_string(1), getMemDC(), player_inventory[i]->_rc.left + 55- c *10, player_inventory[i]->_rc.top + 55);
						break;
					case 2:
						IMAGEMANAGER->render(to_string(2), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 3:
						IMAGEMANAGER->render(to_string(3), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 4:
						IMAGEMANAGER->render(to_string(4), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 5:
						IMAGEMANAGER->render(to_string(5), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 6:
						IMAGEMANAGER->render(to_string(6), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 7:
						IMAGEMANAGER->render(to_string(7), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 8:
						IMAGEMANAGER->render(to_string(8), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 9:
						IMAGEMANAGER->render(to_string(9), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					}
					c++;
					item_count /= 10;

				}
				if (player_inventory[i]->count > 0) {
					IMAGEMANAGER->render(to_string(player_inventory[i]->count), getMemDC(), player_inventory[i]->_rc.left + 55, player_inventory[i]->_rc.top + 55);
				}
			}
			
			if (istargetBox) {
				for (int i = 0; i < 4; i++) {
					IMAGEMANAGER->frameRender("img_UI_TargetingBox", getMemDC(), targetBox[i].x, targetBox[i].y, targetBox[i].img_num, 0);
				}
				IMAGEMANAGER->render("img_UI_ItemTooltip", getMemDC(), 900, 150);
				
			}
			break;
		case EQUIP:
			IMAGEMANAGER->render("img_equip_icon", getMemDC(), 470, 30);

			IMAGEMANAGER->render("img_equip_slot", getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("img_equip_slot")->getWidth()/2), WINSIZEY/2);

			for (int i = 0; i < player_equip.size(); i++) {
				if (player_equip[i]->Kinds == ITEM_NULL)continue;
				IMAGEMANAGER->render("Img_UI_EquipmentSlotFilled", getMemDC(), player_equip[i]->_rc.left, player_equip[i]->_rc.top);
				IMAGEMANAGER->render(player_equip[i]->img_name,getMemDC(), player_equip[i]->_rc.left+15, player_equip[i]->_rc.top);
			}
			if (istargetBox) {
				for (int i = 0; i < 4; i++) {
					IMAGEMANAGER->frameRender("img_UI_TargetingBox", getMemDC(), targetBox[i].x, targetBox[i].y, targetBox[i].img_num, 0);
				}
			}
			break;

		}
		
	}

}

void inventory::itemRemove()
{

}

void inventory::mouse_targetBox()
{
	switch (inven_kinds)
	{
	case ITEM:
		for (int i = 0; i < player_inventory.size(); i++) {
			if (PtInRect(&player_inventory[i]->_rc, _ptMouse)) {
				mouse_setingRc(player_inventory[i]->_rc);
				istargetBox = true;
				break;
			}
		}
		break;
	case EQUIP:
		for (int i = 0; i < player_equip.size(); i++) {
			if (PtInRect(&player_equip[i]->_rc, _ptMouse)) {
				mouse_setingRc(player_equip[i]->_rc);
				istargetBox = true;
				break;
			}
		}
		break;
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

void inventory::keyDown()
{
	if (INPUT->GetKeyDown('I')) {
		if (isCheck) {
			isCheck = false;
		}
		else {
			isCheck = true;
		}
	}

	if (INPUT->GetKeyDown('Q')|| INPUT->GetKeyDown('E')) {
		if (inven_kinds == ITEM) {
			inven_kinds = EQUIP;
		}
		else {
			inven_kinds = ITEM;
		}
		istargetBox = false;
	}

}

void inventory::item_check()
{
	if (INPUT->GetKeyDown('C')) {
		for (int i = 0; i < player_inventory.size(); i++) {

			if (player_inventory[i]->item_name != "목재")continue;
			if (player_inventory[i]->count > 2) {
				player_inventory[i]->count -= 2;
			}
		}
	}
}
