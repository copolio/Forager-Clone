#include "stdafx.h"
#include "item_Manager.h"


void item_Manager::vItem_push(string key)
{
	if (isItemCheck(key)) {
		int number = itemfind(key);
		_item_push[number]->count += 1;
	}
	else {
		int number = itemempty();
		_item_push[number]->img_name = key;
		_item_push[number]->Kinds = itemKind(key);
		_item_push[number]->count += 1;
		cout << _item_push[number]->count << endl;
	}

}



bool item_Manager::isItemCheck(string key)
{
	for (int i = 0; i < _item_push.size(); i++) {
		if (_item_push[i]->img_name == key) {
			return true;
		}
	}
	return false;
}//인벤토리에 있는지 없는지 확인


int item_Manager::itemempty()
{
	int i = 0;
	for (; i < _item_push.size(); i++) {
		if (_item_push[i]->img_name == "") {
			return i;
		}
	}
	return 888;
}//비어있는 자릿수 반환 888은 가방이 더이상 들어갈때가 없을때 반환

ItemKinds item_Manager::itemKind(string key)
{
	if (key == "berryDrop") {
		return ITEM_FOOD;
	}
	else if (key == "rockDrop") {
		return ITEM_MATERIAL;
	}
	else if (key == "treeDrop") {
		return ITEM_MATERIAL;
	}
	return ITEM_NULL;
}

//item 종류 확인(아이템 종류가 늘어나면 if문 추가해야됨)
/*
	ITEM_NULL,
	ITEM_FOOD,
	ITEM_EQUIP,
	ITEM_MATERIAL,
*/

int item_Manager::itemfind(string key)
{
	
	for (int i = 0; i < _item_push.size(); i++) {
		if (_item_push[i]->img_name == key) {
			return i;
		}
	}
}//인벤토리에 아이템이 어디있는지 찾는함수

void item_Manager::inventorysection()
{


}//중복된 key가 있나없나 검사//아직까지는 잘됨...중복 버그가 발생하면..그때생각