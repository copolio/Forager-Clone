#pragma once
#include "singletonBase.h"
#include "item.h"

class ItemDatabase : public singletonBase<ItemDatabase>
{

private:
	map<string, tagItem> _itemDictionary;




public:
	void init();



public:
	tagItem GetItem(string p_key) { return _itemDictionary[p_key]; };
};

