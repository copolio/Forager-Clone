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
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("ironOreDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  1", pos, 20, 0);
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
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("goldOreDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  1", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
		break;
	case 4:
		IMAGEMANAGER->render("ironOreDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		IMAGEMANAGER->render("stone", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("ironOreDrop")), pos, 20, 0);
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
	case 5:
		IMAGEMANAGER->render("SteelhDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 10, rc.top-10);
		IMAGEMANAGER->render("goldOreDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("SteelhDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  1", pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("goldOreDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  3", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
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
		IMAGEMANAGER->render("fishDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 10, rc.top - 10);
		IMAGEMANAGER->render("coalDrop", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("fishDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, false, "/  1", pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count("coalDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, false, "/  2", pos, 20, 0);
		if (cilck()) {
			click_item_event(num);
		}
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
			if (ITEMMANAGER->Item_count_Minus("coalDrop", 2, "rockDrop", 2)) {
				PRODUCTIONMANAGER->isCount("brickDrop");
			}
		}
		break;
	case 2:
		if (PRODUCTIONMANAGER->is_Item_Cilck("ironBarDrop")) {
			if (ITEMMANAGER->Item_count_Minus("Iron_ore", 1, "coalDrop", 1)) {
				PRODUCTIONMANAGER->isCount("ironBarDrop");
			}
		}
		break;
	case 3:
		if (PRODUCTIONMANAGER->is_Item_Cilck("goldBarDrop")) {
			if (ITEMMANAGER->Item_count_Minus("goldOreDrop", 1, "coalDrop", 1)) {
				PRODUCTIONMANAGER->isCount("goldBarDrop");
			}
		}
		break;
	case 4:
		if (PRODUCTIONMANAGER->is_Item_Cilck("SteelhDrop")) {
			if (ITEMMANAGER->Item_count_Minus("ironOreDrop", 2, "rockDrop", 2)) {
				PRODUCTIONMANAGER->isCount("SteelhDrop");
			}
		}
		break;
	case 5:
		if (PRODUCTIONMANAGER->is_Item_Cilck("high_class_SteelDrop")) {
			if (ITEMMANAGER->Item_count_Minus("SteelhDrop", 1, "goldOreDrop", 3)) {
				PRODUCTIONMANAGER->isCount("high_class_SteelDrop");
			}
		}
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		if (PRODUCTIONMANAGER->is_Item_Cilck("roast_fishDrop")) {
			if (ITEMMANAGER->Item_count_Minus("fishDrop", 1, "coalDrop", 2)) {
				PRODUCTIONMANAGER->isCount("roast_fishDrop");
			}
		}
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
