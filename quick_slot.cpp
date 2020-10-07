#include "stdafx.h"
#include "quick_slot.h"

void quick_slot::render(HDC hdc)
{
	for (int i = 0; i < _quick.size(); i++) {

		IMAGEMANAGER->alphaRender("quick_slot_background", hdc, _quick[i]->_rc.left, _quick[i]->_rc.top,180);
		IMAGEMANAGER->render(_quick[i]->img_name, hdc, _quick[i]->_rc.left, _quick[i]->_rc.top);
	}
	cout << ITEMMANAGER->get_equip_info().size() << endl;
}

void quick_slot::quick_slot_update()
{
	for (int i = 0; i < ITEMMANAGER->get_equip_info().size(); i++) {

		if (ITEMMANAGER->get_equip_info()[i]->Kinds == ITEM_EQUIP ) {
			cout << "a" << endl;
			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->Kinds = ITEMMANAGER->get_equip_info()[i]->Kinds;
			inven->x = (WINSIZEX /2) - (ITEMMANAGER->equip_count() * 56) + (i * 56);
			inven->y = WINSIZEY - 56;
			inven->count = 0;
			inven->img_name = ITEMMANAGER->get_equip_info()[i]->img_name;
			inven->_rc = RectMake(inven->x, inven->y, 56, 56);
			_quick.push_back(inven);
		}
	}
	
		
}
