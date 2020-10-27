#include "stdafx.h"
#include "inventory_images.h"

HRESULT inventory_images::init()
{
	// UI 등록
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
	IMAGEMANAGER->addImage("quick_slot_background", "Images/이미지/GUI/inventory_background.bmp", 56, 56);
	IMAGEMANAGER->addImage("img_industry_icon", "Images/이미지/GUI/img_industry_icon.bmp", 250, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_steelwork_icon", "Images/이미지/GUI/img_steelwork_icon.bmp", 220, 53, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_missing_icon", "Images/이미지/GUI/img_missing_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_anvil_icon", "Images/이미지/GUI/img_anvil_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_sewingmachine_icon", "Images/이미지/GUI/img_sewingmachine_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("purchase_land", "Images/이미지/GUI/purchase_land.bmp", 105, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_Agriculture_icon", "Images/이미지/GUI/img_Agriculture_icon.bmp", 250, 80, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("game_setting", "Images/이미지/GUI/game_setting.bmp", 64, 82, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_bridge_icon", "Images/이미지/GUI/img_bridge_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_fish_trap_icon", "Images/이미지/GUI/img_fish_trap_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_Agriculture_missing_icon", "Images/이미지/GUI/img_Agriculture_missing_icon.bmp", 220, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_UI_construction_Tooltip", "Images/이미지/GUI/img_UI_construction_Tooltip.bmp", 220, 100, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("targetMenu", "Images/이미지/GUI/targetMenu.bmp", 319, 54, true, RGB(255, 0, 255));


	// 상단 메뉴 UI 등록
	IMAGEMANAGER->addImage("mouse_construction_icon", "Images/이미지/GUI/mouse_construction_icon.bmp", 62, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouse_equip_icon", "Images/이미지/GUI/mouse_equip_icon.bmp", 58, 81, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouse_game_setting", "Images/이미지/GUI/mouse_game_setting.bmp", 74, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouse_item_icon", "Images/이미지/GUI/mouse_item_icon.bmp", 81, 83, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouse_purchase_land", "Images/이미지/GUI/mouse_purchase_land.bmp", 116, 82, true, RGB(255, 0, 255));


	// 건물 상호작용 출력 UI 등록
	IMAGEMANAGER->addImage("img_steelwork_menu", "Images/이미지/GUI/img_steelwork_menu.bmp",	350, 650, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_sewingmachine_menu", "Images/이미지/GUI/img_sewingmachine_menu.bmp",	350, 485, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_anvil_menu", "Images/이미지/GUI/img_anvil_menu.bmp",	350, 595, true, RGB(255, 0, 255));
	
	// 건물 생산 이펙트
	IMAGEMANAGER->addFrameImage("smoke_img", "Images/이미지/GUI/smoke_img.bmp", 364, 28, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("steelwork_yellow", "Images/이미지/오브젝트/용광로_파티클.bmp", 33, 21, true, RGB(255, 0, 255));

	// 아이템 슬롯 이미지 등록
	IMAGEMANAGER->addImage("img_game_money_icon", "Images/이미지/GUI/img_game_money_icon.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bag", "Images/이미지/GUI/bag_image.bmp", 112, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wood", "Images/이미지/아이템/wood.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stone", "Images/이미지/아이템/돌.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bow", "Images/이미지/아이템/Bow.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pickaxe", "Images/이미지/아이템/곡괭이.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sword", "Images/이미지/아이템/sword.bmp", 56, 56, true, RGB(255, 0, 255));

	// 장비 공격 모션 이미지
	IMAGEMANAGER->addImage("sword_right", "Images/이미지/아이템/sword_right.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword_att", "Images/이미지/아이템/sword_att.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("img_smoke", "Images/이미지/Effects/img_smoke.bmp", 600, 200,7,1, true, RGB(255, 0, 255));

	// 건설 관련 이미지 등록
	//IMAGEMANAGER->addImage("용광로", "Images/이미지/오브젝트/용광로.bmp", 112, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("용광로", "Images/이미지/오브젝트/용광로.bmp", 112 / 2, 160 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모루", "Images/이미지/오브젝트/모루.bmp", 100 / 2, 90 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("construction_background", "Images/이미지/GUI/construction_background.bmp", 324, 720);
	IMAGEMANAGER->addImage("greentile", "Images/이미지/타일/img_tile_green.bmp", 56, 56);
	IMAGEMANAGER->addImage("redtile", "Images/이미지/타일/img_tile_red.bmp", 56, 56);





	// 기타 UI 등록
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




	return S_OK;
}
