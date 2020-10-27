#include "stdafx.h"
#include "equipMent.h"

HRESULT equipMent::init()
{
	for (int i = 0; i < 7; i++) {
		inventory_slot* inven = new inventory_slot;
		inven->isCheck = false;
		inven->_item = tagItem();
		inven->x = 364 + i * 80;
		inven->y = WINSIZEY / 2 + 15;
		inven->count = 0;
		inven->_rc = RectMake(inven->x, inven->y, 72, 72);
		player_equip.push_back(inven);
	}
	player_equip[0]->_item = DATABASE->GetItem("pickaxeDrop");
	player_equip[1]->_item = DATABASE->GetItem("bowDrop");

	_targetBox = new targetingBox;
	_targetBox->init();
	return S_OK;
}

void equipMent::release()
{
	for (int i = 0; i < player_equip.size(); i++) {
		SAFE_DELETE(player_equip[i]);
		player_equip[i] = NULL;
	}
	player_equip.clear();
}

void equipMent::update()
{
	_targetBox->update();
	mouse_targetBox();
}

void equipMent::render(HDC hdc)
{
	
	IMAGEMANAGER->alphaRender("inventory_background", hdc, 180);
	IMAGEMANAGER->render("inventory_Kinds", hdc, WINSIZEX / 2 - 240, 15);
	IMAGEMANAGER->render("Q", hdc, 320, 70);
	IMAGEMANAGER->render("E", hdc, 890, 70);
	IMAGEMANAGER->render("img_equip_icon", hdc, 411, 30);

	IMAGEMANAGER->render("img_equip_slot", hdc, WINSIZEX / 2 - (IMAGEMANAGER->findImage("img_equip_slot")->getWidth() / 2), WINSIZEY / 2);

	for (int i = 0; i < player_equip.size(); i++) {
		if (player_equip[i]->_item.itemType == ItemType::NONE)continue;
		IMAGEMANAGER->render("Img_UI_EquipmentSlotFilled", hdc, player_equip[i]->_rc.left, player_equip[i]->_rc.top);
		IMAGEMANAGER->render(player_equip[i]->_item.slotImgKey, hdc, player_equip[i]->_rc.left + 15, player_equip[i]->_rc.top);
	}
	if (isCheck) {
		_targetBox->render(hdc);
	}
}

void equipMent::mouse_targetBox()
{

	for (int i = 0; i < player_equip.size(); i++) {
		if (PtInRect(&player_equip[i]->_rc, _ptMouse)) {
			_targetBox->SetTarget(player_equip[i]->_rc, 2, i, 4, false);
			isCheck = true;
			break;
		}
	}
}
