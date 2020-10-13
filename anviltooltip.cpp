#include "stdafx.h"
#include "anviltooltip.h"
#include "stdafx.h"
#include "steelworktooltip.h"

void anviltooltip::render(HDC hdc, int num, RECT rc)
{
	IMAGEMANAGER->render("img_UI_construction_Tooltip", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth(), rc.top);
	switch (num)
	{
	case 0:
		IMAGEMANAGER->render("±Ý±«", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		POINT pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("±Ý±«")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  1", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
		break;
	case 1:
		IMAGEMANAGER->render("±Ý±«", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("±Ý±«")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  3", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
		break;
	case 2:
		pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, "¹Ì°³ºÀ", pos, 20, 0);

		break;
	case 3:
		pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, "¹Ì°³ºÀ", pos, 20, 0);

		break;
	case 4:
		pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, "¹Ì°³ºÀ", pos, 20, 0);

		break;
	case 5:
		IMAGEMANAGER->render("±Ý±«", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		IMAGEMANAGER->render("stone", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("±Ý±«")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, "/  2", pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("rockDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, "/  5", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
		break;
	case 6:
		IMAGEMANAGER->render("±«Ã¶", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		IMAGEMANAGER->render("stone", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("±«Ã¶")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, "/  2", pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("rockDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, "/  5", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
		break;
	case 7:
		pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, "¹Ì°³ºÀ", pos, 20, 0);

		break;
	case 8:
		pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, "¹Ì°³ºÀ", pos, 20, 0);

		break;
	}


}

void anviltooltip::click_item_event(int num)
{
	switch (num)
	{
	case 0:
		if (PRODUCTIONMANAGER->is_Item_Cilck("img_game_money_icon")) {


			if (ITEMMANAGER->Item_count_Minus("±Ý±«", 1)) {
				PRODUCTIONMANAGER->isCount("img_game_money_icon");
			}
		}

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:
		break;
	case 5:
		if (PRODUCTIONMANAGER->is_Item_Cilck("sword")) {

			if (ITEMMANAGER->Item_count_Minus("±Ý±«", 2, "rockDrop",5)) {
				
				PRODUCTIONMANAGER->isCount("sword");
			}
		}
		//°Ë
		break;
	case 6:
		if (PRODUCTIONMANAGER->is_Item_Cilck("Bow")) {


			if (ITEMMANAGER->Item_count_Minus("±«Ã¶", 2, "rockDrop", 5)) {
				PRODUCTIONMANAGER->isCount("Bow");
			}
		}
		//È°
		break;
	case 7:
		break;
	case 8:
		break;

	}
}

bool anviltooltip::cilck()
{
	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		return true;
	}
	return false;
}
