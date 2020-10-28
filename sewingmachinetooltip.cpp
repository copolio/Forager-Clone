#include "stdafx.h"
#include "sewingmachinetooltip.h"


void sewingmachinetooltip::render(HDC hdc, int num, RECT rc)
{
	IMAGEMANAGER->render("img_UI_construction_Tooltip", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth(), rc.top);
	switch (num)
	{
	case 0:
		IMAGEMANAGER->render("wood", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		POINT pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("treeDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  3", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
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
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);
		break;
	}


}


void sewingmachinetooltip::click_item_event(int num)
{
	switch (num)
	{
	case 0:
		if (PRODUCTIONMANAGER->is_Item_Cilck("threadDrop")) {


			if (ITEMMANAGER->Item_count_Minus("treeDrop", 3)) {
				PRODUCTIONMANAGER->isCount("threadDrop");
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
