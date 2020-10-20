#include "stdafx.h"
#include "quick_slot.h"

HRESULT quick_slot::init()
{
	_targetBox = new targetingBox;
	_targetBox->init();
	targetnum = 0;
	return S_OK;
}

void quick_slot::release()
{
	SAFE_DELETE(_targetBox);
	_targetBox = NULL;
}

void quick_slot::update()
{
	this->target(targetnum);
	_targetBox->update();
	quick_slot_target_Move();
	Item_Minus("", 0);
	
}

void quick_slot::render(HDC hdc)
{
	for (int i = 0; i < _quick.size(); i++) {

		IMAGEMANAGER->alphaRender("quick_slot_background", hdc, _quick[i]->_rc.left, _quick[i]->_rc.top,180);
		if (_quick[i]->img_name == "Bow") {
			IMAGEMANAGER->frameRender(_quick[i]->img_name, hdc, _quick[i]->_rc.left, _quick[i]->_rc.top, 0, 2);
		}else {
			IMAGEMANAGER->render(_quick[i]->img_name, hdc, _quick[i]->_rc.left, _quick[i]->_rc.top);
		}
	}
	for (int i = 0; i < _quick.size(); i++) {
		if (_quick[i]->Kinds == ITEM_FOOD) {
			int item_count = _quick[i]->count;
			int c = 0;
			
			while (item_count != NULL) {
				switch (item_count % 10)
				{
				case 0:
					IMAGEMANAGER->render(to_string(0), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				case 1:
					IMAGEMANAGER->render(to_string(1), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				case 2:
					IMAGEMANAGER->render(to_string(2), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				case 3:
					IMAGEMANAGER->render(to_string(3), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				case 4:
					IMAGEMANAGER->render(to_string(4), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				case 5:
					IMAGEMANAGER->render(to_string(5), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				case 6:
					IMAGEMANAGER->render(to_string(6), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				case 7:
					IMAGEMANAGER->render(to_string(7), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				case 8:
					IMAGEMANAGER->render(to_string(8), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				case 9:
					IMAGEMANAGER->render(to_string(9), hdc, _quick[i]->_rc.left + 50 - c * 10, _quick[i]->_rc.top + 40);
					break;
				}
				c++;
				item_count /= 10;

			}
		}
		
	}
	
	_targetBox->render(hdc);
}

void quick_slot::quick_slot_update()
{
	_quick.clear();
	int j = 0;
	for (int i = 0; i < ITEMMANAGER->get_equip_info().size(); i++) {

		if (ITEMMANAGER->get_equip_info()[i]->Kinds == ITEM_EQUIP ) {
			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->Kinds = ITEMMANAGER->get_equip_info()[i]->Kinds;
			inven->x = (WINSIZEX /2)-(ITEMMANAGER->equip_count()*20) +((j++) *58);
			inven->y = WINSIZEY - 70;
			inven->count = 0;
			inven->img_name = ITEMMANAGER->get_equip_info()[i]->img_name;
			inven->_rc = RectMake(inven->x, inven->y, 56, 56);
			_quick.push_back(inven);
		}
	}
	for (int i = 0; i < ITEMMANAGER->getvInventory_info().size(); i++) {
		if (ITEMMANAGER->getvInventory_info()[i]->Kinds == ITEM_FOOD) {
			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->Kinds = ITEMMANAGER->getvInventory_info()[i]->Kinds;
			inven->x = (WINSIZEX / 2) - (ITEMMANAGER->equip_count() * 20) + ((j++) * 58);
			inven->y = WINSIZEY - 70;
			inven->count = ITEMMANAGER->getvInventory_info()[i]->count;
			inven->img_name = ITEMMANAGER->getvInventory_info()[i]->img_name;
			inven->_rc = RectMake(inven->x, inven->y, 56, 56);
			_quick.push_back(inven);
		}
	}
	
	this->target(0);
}

void quick_slot::target(int i)
{
	_targetBox->SetTarget(_quick[i]->_rc, 2, i, 4, false);
}

void quick_slot::quick_slot_target_Move()
{
	if (INPUT->GetKeyDown('1')&& ITEMMANAGER->equip_count() >=1) {
		target(0); targetnum = 0;
	}else if(INPUT->GetKeyDown('2') && ITEMMANAGER->equip_count() >= 2) {
		target(1); targetnum = 1;
	}
	else if (INPUT->GetKeyDown('3') && ITEMMANAGER->equip_count() >= 3) {
		target(2); targetnum = 2;
	}
	else if (INPUT->GetKeyDown('4') && ITEMMANAGER->equip_count() >= 4) {
		target(3); targetnum = 3;
	}
	else if (INPUT->GetKeyDown('5') && ITEMMANAGER->equip_count() >= 5) {
		target(4); targetnum = 4;
	}
	else if (INPUT->GetKeyDown('6') && ITEMMANAGER->equip_count() >= 6) {
		target(5); targetnum = 5;
	}
	else if (INPUT->GetKeyDown('7') && ITEMMANAGER->equip_count() >= 7) {
		target(6); targetnum = 6;
	}

}

void quick_slot::Item_Minus(string key, int count)
{
	for (int i = 0; i < _quick.size(); i++) {
		if (_quick[i]->img_name == key && _quick[i]->count >= count) {
			_quick[i]->count -= count;
			
		}
		if (_quick[i]->Kinds == ITEM_FOOD && _quick[i]->count == 0) {
			this->settargetNum(0);
			this->target(0);
			quick_slot_update();
			break;
		}
		
	}
}
