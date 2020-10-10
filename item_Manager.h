#pragma once
#include "inventory_slot.h"
#include "singletonBase.h"
#include "unit.h"
class item_Manager : public singletonBase<item_Manager>
{
private:

	vector<inventory_slot*> _item_push;
	vector<inventory_slot*> _equip;
	int *money;
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
	
	void set_equip_info(vector<inventory_slot*> equip) {
		_equip = equip;
	};

	vector<inventory_slot*> get_equip_info() {
		return _equip ;
	};

	vector<inventory_slot*> getvInventory_info() {
		return _item_push;
	}

	void setMoney(int* m) {
		money = m;
	}

	int getMoney() {
		return *money;
	}
public:
	
	int equip_count();
	void vItem_push(string key);
	void vItem_count_zoro();
	int item_count(string key);
public:
	bool Item_industry_check(string key);
	void _Item_industry_decrease(string key);

};

