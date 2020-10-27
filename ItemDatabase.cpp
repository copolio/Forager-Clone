#include "stdafx.h"
#include "ItemDatabase.h"

#define ITEM_MAX 16



void ItemDatabase::init()
{
	_itemDictionary.clear();

	// 임시로 10개
	tagItem items[ITEM_MAX];
	int t_cnt = 0;

	// 소비템			    필드아이템키   슬롯키   이름  설명  아이템유형      장비유형    가치 옵션1 옵션2
	items[t_cnt++] = tagItem("berryDrop", "berryDrop", "열매", "체력을 회복시켜준다.", CONSUMABLE, WeaponType::NONE2, 1, 5, 0);
	items[t_cnt++] = tagItem("fishDrop", "fishDrop", "물고기", "체력을 회복시켜준다.", CONSUMABLE, WeaponType::NONE2, 1, 5);
	items[t_cnt++] = tagItem("milkDrop", "milkDrop", "우유", "체력을 회복시켜준다.", CONSUMABLE, WeaponType::NONE2, 3, 5);
	
	// 재료템			    필드아이템키   슬롯키   이름  설명  아이템유형      장비유형    가치 옵션1 옵션2
	items[t_cnt++] = tagItem("rockDrop", "rockDrop", "돌", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("treeDrop", "treeDrop", "목재", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("goldBarDrop", "goldBarDrop", "금괴", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("ironBarDrop", "ironBarDrop", "괴철", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("goldOreDrop", "goldOreDrop", "금광석", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("ironOreDrop", "ironOreDrop", "철광석", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("coalDrop", "coalDrop", "석탄", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("brickDrop", "brickDrop", "벽돌", " ", INGREDIANT, WeaponType::NONE2, 3, 0);
	items[t_cnt++] = tagItem("skullHeadDrop", "skullHeadDrop", "스컬머리", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("leatherDrop", "leatherDrop", "가죽", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	
	// 장비템			    필드아이템키   슬롯키   이름  설명  아이템유형      장비유형    가치 옵션1 옵션2
	items[t_cnt++] = tagItem("bowDrop", "bowDrop", "활", " ", EQUIPMENT, BOW, 1, 0);
	items[t_cnt++] = tagItem("swordDrop", "sword", "칼", " ", EQUIPMENT, SWORD, 1, 30);
	items[t_cnt++] = tagItem("pickaxeDrop", "pickaxe", "곡괭이", " ", EQUIPMENT, PICKAXE, 1, 15);
	
	for (int i = 0; i < ITEM_MAX; i++) {
		_itemDictionary.insert(make_pair(items[i].itemKey, items[i]));
	}



}
