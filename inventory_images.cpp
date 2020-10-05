#include "stdafx.h"
#include "inventory_images.h"

HRESULT inventory_images::init()
{
	IMAGEMANAGER->addImage("Q", "Images/이미지/GUI/Q버튼.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("E", "Images/이미지/GUI/E버튼.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("커서", "Images/이미지/GUI/커서.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inventory_Kinds", "Images/이미지/GUI/inventory_Kinds.bmp", 468, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_item_icon", "Images/이미지/GUI/img_item_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_equip_icon", "Images/이미지/GUI/img_equip_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Img_UI_EquipmentSlotFilled", "Images/이미지/GUI/Img_UI_EquipmentSlotFilled.bmp", 72, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테미나", "Images/이미지/GUI/img_UI_StaminaGaugeBar.bmp", 72, 72, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("img_UI_TargetingBox", "Images/이미지/GUI/img_UI_TargetingBox.bmp", 72, 21, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_UI_ItemTooltip", "Images/이미지/GUI/img_UI_ItemTooltip.bmp", 296, 216, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_slot", "Images/이미지/GUI/img_UI_InventorySlotBoundary.bmp", 88, 88, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_equip_slot", "Images/이미지/GUI/img_equip_slot.bmp", 582, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_construction_icon", "Images/이미지/GUI/img_construction_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inventory_background", "Images/이미지/GUI/inventory_background.bmp", 1280, 720);
	IMAGEMANAGER->addImage("img_industry_icon", "Images/이미지/GUI/img_industry_icon.bmp", 226, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_steelwork_icon", "Images/이미지/GUI/img_steelwork_icon.bmp", 205, 59, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_anvil_icon", "Images/이미지/GUI/img_anvil_icon.bmp", 205, 59, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_sewingmachine_icon", "Images/이미지/GUI/img_sewingmachine_icon.bmp", 205, 59, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("purchase_land", "Images/이미지/GUI/purchase_land.bmp", 105, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_Agriculture_icon", "Images/이미지/GUI/img_Agriculture_icon.bmp", 226, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("game_setting", "Images/이미지/GUI/game_setting.bmp", 64, 82, true, RGB(255, 0, 255));


	//IMAGEMANAGER->addImage("용광로", "Images/이미지/오브젝트/용광로.bmp", 112, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("용광로", "Images/이미지/오브젝트/용광로.bmp", 112 / 2, 160 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모루", "Images/이미지/오브젝트/모루.bmp", 100 / 2, 90 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("construction_background", "Images/이미지/GUI/construction_background.bmp", 324, 720);

	IMAGEMANAGER->addImage("pick", "Images/이미지/아이템/곡괭이.bmp", 56, 56, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("0", "Images/이미지/GUI/0.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1", "Images/이미지/GUI/1.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "Images/이미지/GUI/2.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3", "Images/이미지/GUI/3.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4", "Images/이미지/GUI/4.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5", "Images/이미지/GUI/5.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("6", "Images/이미지/GUI/6.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("7", "Images/이미지/GUI/7.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "Images/이미지/GUI/8.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("9", "Images/이미지/GUI/9.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("greentile", "Images/이미지/타일/img_tile_green.bmp", 56, 56);
	IMAGEMANAGER->addImage("redtile", "Images/이미지/타일/img_tile_red.bmp", 56, 56);
	return S_OK;
}
