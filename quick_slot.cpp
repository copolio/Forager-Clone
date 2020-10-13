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
	_targetBox->update();
	quick_slot_target_Move();
}

void quick_slot::render(HDC hdc)
{
	for (int i = 0; i < _quick.size(); i++) {

		IMAGEMANAGER->alphaRender("quick_slot_background", hdc, _quick[i]->_rc.left, _quick[i]->_rc.top,180);
		IMAGEMANAGER->render(_quick[i]->img_name, hdc, _quick[i]->_rc.left, _quick[i]->_rc.top);
	}
	_targetBox->render(hdc);
}

void quick_slot::quick_slot_update()
{
	_quick.clear();
	for (int i = 0; i < ITEMMANAGER->get_equip_info().size(); i++) {

		if (ITEMMANAGER->get_equip_info()[i]->Kinds == ITEM_EQUIP ) {
			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->Kinds = ITEMMANAGER->get_equip_info()[i]->Kinds;
			inven->x = (WINSIZEX /2)-(ITEMMANAGER->equip_count()*20) +(i*58);
			inven->y = WINSIZEY - 70;
			inven->count = 0;
			inven->img_name = ITEMMANAGER->get_equip_info()[i]->img_name;
			inven->_rc = RectMake(inven->x, inven->y, 56, 56);
			_quick.push_back(inven);
		}
	}
	
}

void quick_slot::target(int i)
{
	_targetBox->SetTarget(_quick[i]->_rc, 2, i, 4, false);
}

void quick_slot::quick_slot_target_Move()
{
	cout << ITEMMANAGER->equip_count() << endl;
	if (INPUT->GetKeyDown('1')&& ITEMMANAGER->equip_count() >=1) {
		target(0);
	}else if(INPUT->GetKeyDown('2') && ITEMMANAGER->equip_count() >= 2) {
		target(1);
	}
	else if (INPUT->GetKeyDown('3') && ITEMMANAGER->equip_count() >= 3) {
		target(2);
	}
	else if (INPUT->GetKeyDown('4') && ITEMMANAGER->equip_count() >= 4) {
		target(3);
	}
	else if (INPUT->GetKeyDown('5') && ITEMMANAGER->equip_count() >= 5) {
		target(3);
	}
	else if (INPUT->GetKeyDown('6') && ITEMMANAGER->equip_count() >= 6) {
		target(3);
	}
	else if (INPUT->GetKeyDown('7') && ITEMMANAGER->equip_count() >= 7) {
		target(3);
	}
}
