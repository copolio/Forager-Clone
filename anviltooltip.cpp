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
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("±Ý±«")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, "/  1", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
		break;
	case 1:
		IMAGEMANAGER->render("±Ý±«", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("±Ý±«")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, "/  3", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
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
		break;
	case 6:
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
