#pragma once

#include "singletonBase.h"

enum ItemType {
	EQUIPMENT,
	CONSUMABLE,
	INGREDIANT,
};

struct tagItem {
	string itemKey;
	string itemName;
	ItemType itemType;
	int value;
	int option;

	tagItem() {};
	tagItem(string p_itemKey, string p_itemName, ItemType p_itemType, int p_value, int p_option)
		: itemKey(p_itemKey), itemName(p_itemName), itemType(p_itemType), value(p_value), option(p_option) {};
};

class ItemDatabase : public singletonBase<ItemDatabase>
{

public:
	map<string, tagItem> _itemDictionary;

public:
	void init();


};

