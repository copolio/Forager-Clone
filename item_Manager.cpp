#include "stdafx.h"
#include "item_Manager.h"


int item_Manager::equip_count()
{
	int count=0;
	for (int i = 0; i < _equip.size(); i++) {
		if (_equip[i]->Kinds == ITEM_EQUIP) {
			count++;
		}
	}
	for (int i = 0; i < ITEMMANAGER->getvInventory_info().size(); i++) {
		if (ITEMMANAGER->getvInventory_info()[i]->Kinds != ITEM_FOOD) continue;
			count++;
		
	}
	return count;
}

void item_Manager::vItem_push(string key)
{

	if (key == "img_game_money_icon") {
		*money += 1;
	}
	else if (isItemCheck(key)) {
		int number = itemfind(key);
		_item_push[number]->count += 1;
	}
	else {
		int number = itemempty();
		_item_push[number]->img_name = key;
		_item_push[number]->Kinds = itemKind(key);
		_item_push[number]->count += 1;
	}

}

//아이템 인벤에 넣어주는곳
void item_Manager::vequip_push(string key)
{
	if (!isequipCheck(key)) {
		for (int i = 0; i < _equip.size(); i++) {
			if (_equip[i]->img_name == "") {
				_equip[i]->img_name = key;
				_equip[i]->item_name = key;
				_equip[i]->Kinds = ITEM_EQUIP;
				break;
			}
		}
	}

}
bool item_Manager::isequipCheck(string key)
{
	for (int i = 0; i < _equip.size(); i++) {
		if (_equip[i]->img_name == key) {
			return true;
		}
	}
	return false;
}
void item_Manager::vItem_count_zoro()
{
	for (int i = 0; i < _item_push.size(); i++) {
		if (_item_push[i]->img_name == "")continue;
		if (_item_push[i]->count <= 0) {
			_item_push[i]->Kinds = ITEM_NULL;
			_item_push[i]->img_name = "";
			_item_push[i]->item_name = "";
			_item_push[i]->item_Info = "";
		}
	}
}
//아이템 카운트가 0 이되면 삭제


bool item_Manager::Item_industry_check(string key)
{			//rockDrop treeDrop
	int first_material_num = itemfind("rockDrop"); 
	int second_material_num = itemfind("treeDrop");
	if (key == "steelwork") {
		if (first_material_num != -1 && second_material_num != -1) {
			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 3) {
				return true;
			}
		}
	}
	else if (key == "anvil") {
		if (first_material_num != -1) {
			if (_item_push[first_material_num]->count >= 10) {
				return true;
			}
		}
	}
	else if (key == "sewingmachine") {
		if (first_material_num != -1 && second_material_num != -1) {
			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 5) {
				return true;
			}
		}
	}
	else if (key == "bridge") {
		if (second_material_num != -1) {
			if (_item_push[second_material_num]->count >= 5) {
				
				return true;
			}
		}
	}
	else if (key == "fishtrap") {
		if (second_material_num != -1) {
			if (_item_push[second_material_num]->count >= 5) {
				return true;
			}
		}
	}


	return false;
}
//인벤토리에서 건설시 아이템 체크 있으면 true 없으면 false

void item_Manager::_Item_industry_decrease(string key)
{
	int first_material_num = itemfind("rockDrop");
	int second_material_num = itemfind("treeDrop");
	if (key == "steelwork") {
		if (first_material_num != -1 && second_material_num != -1) {
			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 3) {
				_item_push[first_material_num]->count -= 5;
				_item_push[second_material_num]->count -= 3;
				vItem_count_zoro();
			}
		}
	}
	else if (key == "anvil") {
		if (first_material_num != -1) {
			if (_item_push[first_material_num]->count >= 10) {
				_item_push[first_material_num]->count -= 10;
				vItem_count_zoro();
			}
		}
	}
	else if (key == "sewingmachine") {
		if (first_material_num != -1 && second_material_num != -1) {
			if (_item_push[first_material_num]->count >= 5 && _item_push[second_material_num]->count >= 5) {
				_item_push[first_material_num]->count -= 5;
				_item_push[second_material_num]->count -= 5;
				vItem_count_zoro();
			}
		}
	}
	else if (key == "bridge") {
		if (second_material_num != -1) {
			if (_item_push[second_material_num]->count >= 5) {
				_item_push[second_material_num]->count -= 5;
				vItem_count_zoro();
			}
		}
	}
	else if (key == "fishtrap") {
		if (second_material_num != -1) {
			if (_item_push[second_material_num]->count >= 5) {
				_item_push[second_material_num]->count -= 5;
				vItem_count_zoro();
			}
		}
	}
}

//건설 완료시 재료 삭제
bool item_Manager::Item_count_Minus(string key, int count)
{
	if (isItemCheck(key) && _item_push[itemfind(key)]->count >= count) {
		_item_push[itemfind(key)]->count -= count;
		vItem_count_zoro();
		return true;
	}
	return false;

}
bool item_Manager::Item_count_Minus(string key, int count, string key2, int count2)
{
	if (isItemCheck(key) && isItemCheck(key2)) {
		_item_push[itemfind(key)]->count -= count;
		_item_push[itemfind(key2)]->count -= count2;
		return true;
	}
	return false;
}
//키값을 찾아서 재료 감소

bool item_Manager::isItemCheck(string key)
{
	for (int i = 0; i < _item_push.size(); i++) {
		if (_item_push[i]->img_name == key) {
			return true;
		}
	}
	return false;
}
//인벤토리에 있는지 없는지 확인


int item_Manager::itemempty()
{
	int i = 0;
	for (; i < _item_push.size(); i++) {
		if (_item_push[i]->img_name == "") {
			return i;
		}
	}
	return 888;
}
//비어있는 자릿수 반환 888은 가방이 더이상 들어갈때가 없을때 반환

ItemKinds item_Manager::itemKind(string key)
{
	if (key == "berryDrop" || key == "milkDrop") {
		return ITEM_FOOD;
	}
	else /*if (key == "rockDrop"|| key == "treeDrop"|| key == "coal" || key == "brick" || key == "Iron_ore" || key == "금광석")*/ {
		return ITEM_MATERIAL;
	}

	return ITEM_NULL;
}
//아이템 종류 확인

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
	return -1;
}
//인벤토리에 아이템이 어디있는지 찾는함수 -1는 없다는뜻

void item_Manager::inventorysection()
{


}//중복된 key가 있나없나 검사//아직까지는 잘됨...중복 버그가 발생하면..그때생각

int item_Manager::item_count(string key)
{
	if (isItemCheck(key)) {
		return _item_push[itemfind(key)]->count;
	}
	else {
		return 0;
	}
}
//아이템 이름으로 count값 가져오기