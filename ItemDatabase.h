#pragma once
#include "singletonBase.h"
#include "item.h"

class ItemDatabase : public singletonBase<ItemDatabase>
{

private:
	map<string, tagItem> _itemDictionary;
	map<string, tagItemInfo> _itemMaterials;




public:
	void init();



public:
	tagItemInfo GetItem_Make(string p_key) { return _itemMaterials[p_key]; };
	tagItem GetItem(string p_key) { return _itemDictionary[p_key]; };
};

