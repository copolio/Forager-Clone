#pragma once

enum ItemType {
	NONE,
	EQUIPMENT,
	CONSUMABLE,
	INGREDIANT,
};

enum WeaponType {
	NONE2,
	PICKAXE,
	BOW,
	SWORD,
};

enum MaterialsType {
	NONE3,
	ANVIL,
	SEWINGMACHINE,
	STEELWORK
};


struct tagItem {
	string itemKey;
	string slotImgKey;
	string itemName;
	string itemInfo;
	ItemType itemType;
	WeaponType weaponType;
	int value;
	int option;
	int option2;

	tagItem() {
		itemKey = "";
		slotImgKey = "";
		itemName = "";
		itemInfo = "";
		value = 0;
		option = 0;
		option2 = 0;
		itemType = ItemType::NONE;
		weaponType = WeaponType::NONE2;
	};

	tagItem(string p_itemKey, string p_slotImgKey, string p_itemName, string p_itemInfo, ItemType p_itemType, WeaponType p_weaponType, int p_value, int p_option, int p_option2 = 0)
		: itemKey(p_itemKey), slotImgKey(p_slotImgKey), itemName(p_itemName), itemInfo(p_itemInfo), itemType(p_itemType), weaponType(p_weaponType), value(p_value), option(p_option), option2(p_option2) {};
};

struct tagItemInfo {
	string itemKey;
	string  materials_one;
	int one;
	string  materials_two;
	int two;
	string  materials_Three;
	int three;
	string  materials_Four;
	int four;

	int MakeTime;
	int materials_count;

	MaterialsType  type;
	tagItemInfo() {
		itemKey = "";
		materials_one = "";
		one = 0;
		materials_two = "";
		two = 0;
		materials_Three = "";
		three = 0;
		materials_Four = "";
		four = 0;

		MakeTime = 0;
		materials_count = 0;

		type = MaterialsType::NONE3;
	}
	tagItemInfo(string p_itemKey, string p_materials_one,int p_one, string p_materials_two, int p_two, string p_materials_Three,  int p_three,string p_materials_Four, int p_four, int p_MakeTime, int p_materials_count, MaterialsType _type)
		: itemKey(p_itemKey), materials_one(p_materials_one),one(p_one), materials_two(p_materials_two), two(p_two), materials_Three(p_materials_Three), three(p_three), materials_Four(p_materials_Four), four(p_four), MakeTime(p_MakeTime), materials_count(p_materials_count), type(_type){};
};