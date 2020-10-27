#include "stdafx.h"
#include "steelworktooltip.h"

void steelworktooltip::render(HDC hdc, int num, RECT rc)
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
		TEXTMANAGER->ShowText(hdc, false, "/  1", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
			
		}
		break;
	case 1:
		IMAGEMANAGER->render("coalDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		IMAGEMANAGER->render("stone", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("coalDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  2", pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("rockDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  2", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
		break;
	case 2:
		IMAGEMANAGER->render("coalDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		IMAGEMANAGER->render("ironOreDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("coalDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  1", pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("Iron_ore")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  2", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
		break;
	case 3:
		IMAGEMANAGER->render("coalDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		IMAGEMANAGER->render("goldOreDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("coalDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  1", pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("±İ±¤¼®")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  2", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
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
	case 7:
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);
		break;
	case 8:
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);
		break;
	case 9:
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, false, "¹Ì°³ºÀ", pos, 20, 0);
		break;

	}


}

void steelworktooltip::click_item_event(int num)
{
	switch (num)
	{
	case 0:
		if (PRODUCTIONMANAGER->is_Item_Cilck("coalDrop")) {


			if (ITEMMANAGER->Item_count_Minus("treeDrop", 1)) {
				PRODUCTIONMANAGER->isCount("coalDrop");
			}
		}

		break;
	case 1:
		if (PRODUCTIONMANAGER->is_Item_Cilck("brickDrop")) {
			if (ITEMMANAGER->Item_count_Minus("treeDrop", 2, "coalDrop", 2)) {
				PRODUCTIONMANAGER->isCount("brickDrop");
			}
		}
		break;
	case 2:
		if (PRODUCTIONMANAGER->is_Item_Cilck("ironBarDrop")) {
			if (ITEMMANAGER->Item_count_Minus("Iron_ore", 2, "coalDrop", 1)) {
				PRODUCTIONMANAGER->isCount("ironBarDrop");
			}
		}
		break;
	case 3:
		if (PRODUCTIONMANAGER->is_Item_Cilck("goldBarDrop")) {
			if (ITEMMANAGER->Item_count_Minus("goldOreDrop", 2, "coalDrop", 1)) {
				PRODUCTIONMANAGER->isCount("goldBarDrop");
			}
		}
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
	case 9:
		break;

	}
	
}


bool steelworktooltip::cilck()
{
	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		SOUNDMANAGER->play("»ı»ê½ÃÀÛ");
		return true;
	}
	return false;
}
