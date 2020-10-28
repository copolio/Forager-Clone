#include "stdafx.h"
#include "sewingmachinetooltip.h"


void sewingmachinetooltip::render(HDC hdc, int num, RECT rc,string item_name)
{
	_item = DATABASE->GetItem_Make(item_name);

	IMAGEMANAGER->render("img_UI_construction_Tooltip", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth(), rc.top);
	switch (num)
	{
	case 0:
		IMAGEMANAGER->render(_item.materials_one, hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		POINT pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_one)), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  " + to_string(_item.one), pos, 20, 0);
		
		break;
	case 1:
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);
		break;
	case 2:
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);
		break;
	case 3:
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);
		break;
	case 4:
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);
		break;
	case 5:
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);
		break;
	case 6:
		IMAGEMANAGER->render(_item.materials_one, hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() , rc.top - 5);
		IMAGEMANAGER->render(_item.materials_two, hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 10, rc.top + 45);
		IMAGEMANAGER->render(_item.materials_Three, hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100, rc.top - 10);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth()+60;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_one)), pos, 20, 0);

		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 90;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/ " + to_string(_item.one), pos, 20, 0);

		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 60;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_two)), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 90;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/ " + to_string(_item.two), pos, 20, 0);

		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 160;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_Three)), pos, 20, 0);

		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 180;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/ " + to_string(_item.three), pos, 20, 0);

	


		break;
	}
	if (cilck()) {
		click_item_event(item_name);
	}

}


void sewingmachinetooltip::click_item_event(string item_key)
{
	tagItemInfo _item = DATABASE->GetItem_Make(item_key);
	switch (_item.materials_count)
	{
	case 1:
		if (PRODUCTIONMANAGER->is_Item_Cilck(_item.itemKey)) {


			if (ITEMMANAGER->Item_count_Minus(_item.materials_one, _item.one)) {
				PRODUCTIONMANAGER->isCount(_item.itemKey);
			}
		}
		break;
	case 2:
		if (PRODUCTIONMANAGER->is_Item_Cilck(_item.itemKey)) {
			if (ITEMMANAGER->Item_count_Minus(_item.materials_one, _item.one, _item.materials_two, _item.two)) {
				PRODUCTIONMANAGER->isCount(_item.itemKey);
			}
		}
		break;
	case 3:
		if (PRODUCTIONMANAGER->is_Item_Cilck(_item.itemKey)) {
			if (ITEMMANAGER->Item_count_Minus(_item.materials_one, _item.one, _item.materials_two, _item.two, _item.materials_Three, _item.three)) {
				PRODUCTIONMANAGER->isCount(_item.itemKey);
			}
		}
		break;
	case 4:
		if (PRODUCTIONMANAGER->is_Item_Cilck(_item.itemKey)) {
			if (ITEMMANAGER->Item_count_Minus(_item.materials_one, _item.one, _item.materials_two, _item.two, _item.materials_Three, _item.three, _item.materials_Four, _item.four)) {
				PRODUCTIONMANAGER->isCount(_item.itemKey);
			}
		}
		break;
	}

}


bool sewingmachinetooltip::cilck()
{
	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		SOUNDMANAGER->play("»ı»ê½ÃÀÛ");
		return true;
	}
	return false;
}
