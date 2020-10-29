#include "stdafx.h"
#include "quick_slot.h"

HRESULT quick_slot::init()
{
	_targetBox = new targetingBox;
	_targetBox->init();
	targetnum = 0;
	_isQuickSlotChanged = false;
	return S_OK;
}

void quick_slot::release()
{
	SAFE_DELETE(_targetBox);
	_targetBox = NULL;
	for (int i = 0; i < _quick.size(); i++) {
		SAFE_DELETE(_quick[i]);
		_quick[i] = NULL;
	}
}

void quick_slot::update()
{
	this->changeQuickSlot(targetnum);
	_targetBox->update();
	quick_slot_target_Move();
	Item_Minus("", 0);
	
}

void quick_slot::render(HDC hdc)
{
	for (int i = 0; i < _quick.size(); i++) {

		IMAGEMANAGER->alphaRender("quick_slot_background", hdc, _quick[i]->_rc.left, _quick[i]->_rc.top,180);

		IMAGEMANAGER->render(_quick[i]->_item.slotImgKey, hdc, _quick[i]->_rc.left, _quick[i]->_rc.top);
		
	}
	for (int i = 0; i < _quick.size(); i++) {
		if (_quick[i]->_item.itemType == ItemType::CONSUMABLE) {
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

		if (ITEMMANAGER->get_equip_info()[i]->_item.itemType == ItemType::EQUIPMENT) {
			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->x = (WINSIZEX /2)-(ITEMMANAGER->equip_count()*20) +((j++) *58);
			inven->y = WINSIZEY - 70;
			inven->count = 0;
			inven->_item = DATABASE->GetItem(ITEMMANAGER->get_equip_info()[i]->_item.itemKey);
			inven->_rc = RectMake(inven->x, inven->y, 56, 56);
			_quick.push_back(inven);
		}
	}
	for (int i = 0; i < ITEMMANAGER->getvInventory_info().size(); i++) {
		if (ITEMMANAGER->getvInventory_info()[i]->_item.itemType == ItemType::CONSUMABLE) {
			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->x = (WINSIZEX / 2) - (ITEMMANAGER->equip_count() * 20) + ((j++) * 58);
			inven->y = WINSIZEY - 70;
			inven->count = ITEMMANAGER->getvInventory_info()[i]->count;
			inven->_item = DATABASE->GetItem(ITEMMANAGER->getvInventory_info()[i]->_item.itemKey);
			inven->_rc = RectMake(inven->x, inven->y, 56, 56);
			_quick.push_back(inven);
		}
	}
	
	_targetBox->SetTarget(_quick[ITEMMANAGER->equip_count()-1]->_rc, 2, ITEMMANAGER->equip_count()-1, 4, false);
}

void quick_slot::changeQuickSlot(int num)
{
	_targetBox->SetTarget(_quick[num]->_rc, 2, num, 4, false);
	targetnum = num; 
	_isQuickSlotChanged = true;
}


void quick_slot::quick_slot_target_Move()
{
	if (INPUT->GetKeyDown('1') && ITEMMANAGER->equip_count() >= 1) {
		changeQuickSlot(0);
	}
	else if(INPUT->GetKeyDown('2') && ITEMMANAGER->equip_count() >= 2) {
		changeQuickSlot(1);
	}
	else if (INPUT->GetKeyDown('3') && ITEMMANAGER->equip_count() >= 3) {
		changeQuickSlot(2);
	}
	else if (INPUT->GetKeyDown('4') && ITEMMANAGER->equip_count() >= 4) {
		changeQuickSlot(3);
	}
	else if (INPUT->GetKeyDown('5') && ITEMMANAGER->equip_count() >= 5) {
		changeQuickSlot(4);
	}
	else if (INPUT->GetKeyDown('6') && ITEMMANAGER->equip_count() >= 6) {
		changeQuickSlot(5);
	}
	else if (INPUT->GetKeyDown('7') && ITEMMANAGER->equip_count() >= 7) {
		changeQuickSlot(6);
	}

}

void quick_slot::Item_Minus(string key, int count)
{
	for (int i = 0; i < _quick.size(); i++) {
		if (_quick[i]->_item.itemKey == key && _quick[i]->count >= count) {
			_quick[i]->count -= count;
			
		}
		if (_quick[i]->_item.itemType == ItemType::CONSUMABLE&& _quick[i]->count == 0) {
			this->settargetNum(0);
			this->changeQuickSlot(0);
			quick_slot_update();
			break;
		}
		
	}
}
