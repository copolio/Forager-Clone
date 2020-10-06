#pragma once
#include "inventory_slot.h"
#include "singletonBase.h"
#include "unit.h"
class item_Manager : public singletonBase<item_Manager>
{
private:

	vector<inventory_slot*> _item_push;


private:
	bool isItemCheck(string key);
	int itemempty();
	int itemfind(string key);
	ItemKinds itemKind(string key);
	
	void inventorysection();
public:
	void setvInventory_info(vector<inventory_slot*> inven) {
		_item_push = inven;
	};

	void vItem_push(string key);

	void vItem_count_zoro();
public:
	bool Item_industry_check(string key);
	void _Item_industry_decrease(string key);

};

