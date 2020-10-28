#include "stdafx.h"
#include "ItemDatabase.h"

#define ITEM_MAX 24



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
	items[t_cnt++] = tagItem("roast_fishDrop", "roast_fishDrop", "구운 고기", " ", CONSUMABLE, WeaponType::NONE2, 1, 10);
	// 추가할때마다 Define문 ITEM_MAX 크기 늘려줄 것!!!


	// 재료템			    필드아이템키   슬롯키   이름  설명  아이템유형      장비유형    가치 옵션1 옵션2
	items[t_cnt++] = tagItem("rockDrop", "rockDrop", "돌", " ", INGREDIANT, WeaponType::NONE2, 1, 0, 0);
	items[t_cnt++] = tagItem("treeDrop", "treeDrop", "목재", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("goldBarDrop", "goldBarDrop", "금괴", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("ironBarDrop", "ironBarDrop", "괴철", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("goldOreDrop", "goldOreDrop", "금광석", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("ironOreDrop", "ironOreDrop", "철광석", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("coalDrop", "coalDrop", "석탄", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("brickDrop", "brickDrop", "벽돌", " ", INGREDIANT, WeaponType::NONE2, 3, 0);
	items[t_cnt++] = tagItem("skullHeadDrop", "skullHeadDrop", "스컬머리", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("leatherDrop", "leatherDrop", "가죽", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("threadDrop", "threadDrop", "실", " ", INGREDIANT, WeaponType::NONE2, 1, 0);

	items[t_cnt++] = tagItem("high_class_cloth", "high_class_cloth", "고급 옷감", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("high_class_SteelDrop", "high_class_SteelDrop", "고급 강철", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("SteelhDrop", "SteelhDrop", "강철", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	items[t_cnt++] = tagItem("arrowDrop", "arrowDrop", "화살", " ", INGREDIANT, WeaponType::NONE2, 1, 0);
	// 추가할때마다 Define문 ITEM_MAX 크기 늘려줄 것!!!
	
	// 장비템			    필드아이템키   슬롯키   이름  설명  아이템유형      장비유형    가치 옵션1 옵션2
	items[t_cnt++] = tagItem("bow1Drop", "bow1Drop", "활", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bow2Drop", "bow2Drop", "강철 활", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bow3Drop", "bow3Drop", "합금 활", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("swordDrop", "sword", "칼", " ", EQUIPMENT, SWORD, 1, 35);
	items[t_cnt++] = tagItem("pickaxeDrop", "pickaxe", "곡괭이", " ", EQUIPMENT, PICKAXE, 1, 20);
	// 추가할때마다 Define문 ITEM_MAX 크기 늘려줄 것!!!


	for (int i = 0; i < ITEM_MAX; i++) {
		_itemDictionary.insert(make_pair(items[i].itemKey, items[i]));
	}
}
