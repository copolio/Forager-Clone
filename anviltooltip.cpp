#include "stdafx.h"
#include "anviltooltip.h"
#include "stdafx.h"
#include "steelworktooltip.h"

void anviltooltip::render(HDC hdc, int num, RECT rc,string _item_name)
{
	_item = DATABASE->GetItem_Make(_item_name);
	
	
	int t_width = IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth();

	IMAGEMANAGER->render("img_UI_construction_Tooltip", hdc, rc.left - t_width, rc.top);
	switch (num)
	{
	case 0:
		IMAGEMANAGER->render(_item.materials_one, hdc, rc.left - t_width + 20, rc.top + 10);
		POINT pos;
		pos.x = rc.left - t_width + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_one)), pos, 20, 0);
		pos.x = rc.left - t_width + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  "+to_string( _item.one), pos, 20, 0);

		break;
	case 1:
		pos.x = rc.left - t_width + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);

		break;
	case 2:
		IMAGEMANAGER->render(_item.materials_one, hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 10, rc.top );
		IMAGEMANAGER->render(_item.materials_two, hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_one)), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  " + to_string(_item.one), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_two)), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  " + to_string(_item.two), pos, 20, 0);

		break;

	case 3:
		IMAGEMANAGER->render(_item.materials_one, hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 10, rc.top);
		IMAGEMANAGER->render(_item.materials_two, hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_one)), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  " + to_string(_item.one), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_two)), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  " + to_string(_item.two), pos, 20, 0);

		break;
	case 4:
		pos.x = rc.left - t_width + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);

		break;
	case 5:
		IMAGEMANAGER->render(_item.materials_one, hdc, rc.left - t_width + 20, rc.top + 10);
		IMAGEMANAGER->render(_item.materials_two, hdc, rc.left - t_width + 20, rc.top + 50);
		pos.x = rc.left - t_width + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_one)), pos, 20, 0);
		pos.x = rc.left - t_width + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  " + to_string(_item.one), pos, 20, 0);
		pos.x = rc.left - t_width + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_two)), pos, 20, 0);
		pos.x = rc.left - t_width + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  " + to_string(_item.two), pos, 20, 0);

		break;
	case 6:
		IMAGEMANAGER->render(_item.materials_one, hdc, rc.left - t_width + 20, rc.top + 10);
		IMAGEMANAGER->render(_item.materials_two, hdc, rc.left - t_width + 20, rc.top + 50);
		pos.x = rc.left - t_width + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_one)), pos, 20, 0);
		pos.x = rc.left - t_width + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  " + to_string(_item.one), pos, 20, 0);
		pos.x = rc.left - t_width + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(_item.materials_two)), pos, 20, 0);
		pos.x = rc.left - t_width + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  " + to_string(_item.two), pos, 20, 0);

		break;
	case 7:
		pos.x = rc.left - t_width + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);

		break;
	case 8:
		pos.x = rc.left - t_width + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);

		break;
	}

	if (cilck()) {
		click_item_event(_item_name);
	}
}

void anviltooltip::click_item_event(string item_key)
{
	if (item_key != "") {

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
	/*switch (num)
	{
	case 0:
		if (PRODUCTIONMANAGER->is_Item_Cilck("img_game_money_icon")) {


			if (ITEMMANAGER->Item_count_Minus("goldBarDrop", 1)) {
				PRODUCTIONMANAGER->isCount("img_game_money_icon");
			}
		}

		break;
	case 1:

		break;
	case 2:
		if (PRODUCTIONMANAGER->is_Item_Cilck("arrowDrop")) {

			if (ITEMMANAGER->Item_count_Minus("treeDrop", 2, "rockDrop", 2)) {

				PRODUCTIONMANAGER->isCount("arrowDrop");
			}
		}
		break;
	}*/

}

bool anviltooltip::cilck()
{
	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		SOUNDMANAGER->play("»ı»ê½ÃÀÛ");
		return true;
	}
	return false;
}
