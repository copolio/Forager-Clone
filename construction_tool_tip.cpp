#include "stdafx.h"
#include "construction_tool_tip.h"

void construction_tool_tip::render(HDC hdc, string item_name, RECT rc)
{
	/*treeDrop
	rockDrop*/
	IMAGEMANAGER->render("img_UI_construction_Tooltip", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth(), rc.top);
	if (item_name == "steelwork") {

		IMAGEMANAGER->render("wood", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth()+20, rc.top+10);
		IMAGEMANAGER->render("stone", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth()+20, rc.top+50);
		POINT pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("treeDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, "/  3", pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("rockDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, "/  5", pos, 20, 0);

	}else if (item_name == "anvil") {
		IMAGEMANAGER->render("stone", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 30);
		POINT pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("rockDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, "/  10", pos, 20, 0);

		
	}
	else if (item_name == "sewingmachine") {
		IMAGEMANAGER->render("wood", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 10);
		IMAGEMANAGER->render("stone", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 50);
		POINT pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("treeDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 20;
		TEXTMANAGER->ShowText(hdc, "/  3", pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("rockDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 60;
		TEXTMANAGER->ShowText(hdc, "/  5", pos, 20, 0);
	}
	else if (item_name == "bridge") {
		IMAGEMANAGER->render("wood", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 30);
		POINT pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("treeDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, "/  5", pos, 20, 0);
	}
	else if (item_name == "fishtrap") {
		IMAGEMANAGER->render("wood", hdc, rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 20, rc.top + 30);
		POINT pos;
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 100;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, to_string(ITEMMANAGER->item_count("treeDrop")), pos, 20, 0);
		pos.x = rc.left - IMAGEMANAGER->findImage("img_UI_construction_Tooltip")->getWidth() + 140;
		pos.y = rc.top + 40;
		TEXTMANAGER->ShowText(hdc, "/  5", pos, 20, 0);
	}

}
