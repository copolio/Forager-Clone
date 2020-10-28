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
	};

	tagItem(string p_itemKey, string p_slotImgKey, string p_itemName, string p_itemInfo, ItemType p_itemType, WeaponType p_weaponType, int p_value, int p_option, int p_option2 = 0)
		: itemKey(p_itemKey), slotImgKey(p_slotImgKey), itemName(p_itemName), itemInfo(p_itemInfo), itemType(p_itemType), weaponType(p_weaponType), value(p_value), option(p_option), option2(p_option2) {};
};

struct tagItemInfo {
	string itemKey;
	string  materials_one;
	string  materials_two;
	string  materials_Three;
	string  materials_Four;

	int MakeTime;
	int materials_count;

	MaterialsType  type;
	tagItemInfo() {
		itemKey = "";
		materials_one = "";
		materials_two = "";
		materials_Three = "";
		materials_Four = "";

		MakeTime = 0;
		materials_count = 0;

		type = MaterialsType::NONE3;
	}
};