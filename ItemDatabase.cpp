#include "stdafx.h"
#include "ItemDatabase.h"

#define ITEM_MAX 34
#define ITEM_MAKE_MAX 40


void ItemDatabase::init()
{
	_itemDictionary.clear();
	_itemMaterials.clear();
	// 임시로 10개
	tagItem items[ITEM_MAX];
	tagItemInfo item_make[ITEM_MAKE_MAX];
	int t_cnt = 0;
	int m_cnt = 0;

	// 소비템			    필드아이템키   슬롯키   이름  설명  아이템유형      장비유형    가치 옵션1 옵션2
	// 4개
	items[t_cnt++] = tagItem("berryDrop", "berryDrop", "열매", "체력을 회복시켜준다.", CONSUMABLE, WeaponType::NONE2, 1, 5, 0);
	items[t_cnt++] = tagItem("fishDrop", "fishDrop", "물고기", "체력을 회복시켜준다.", CONSUMABLE, WeaponType::NONE2, 1, 5);
	items[t_cnt++] = tagItem("milkDrop", "milkDrop", "우유", "체력을 회복시켜준다.", CONSUMABLE, WeaponType::NONE2, 3, 5);
	items[t_cnt++] = tagItem("roast_fishDrop", "roast_fishDrop", "구운 고기", " ", CONSUMABLE, WeaponType::NONE2, 1, 10);
	// 추가할때마다 Define문 ITEM_MAX 크기 늘려줄 것!!!


	// 재료템			    필드아이템키   슬롯키   이름  설명  아이템유형      장비유형    가치 옵션1 옵션2
	// 15개
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
	items[t_cnt++] = tagItem("GlassDrop", "GlassDrop", "유리", " ", INGREDIANT, WeaponType::NONE2, 1, 0);

	
	// 장비템			    필드아이템키   슬롯키   이름  설명  아이템유형      장비유형    가치 옵션1 옵션2
	// 12개
	items[t_cnt++] = tagItem("bowDrop1", "bowDrop1", "활", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bowDrop2", "bowDrop2", "강철 활", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bowDrop3", "bowDrop3", "합금 활", " ", EQUIPMENT, BOW, 1, 10);
	items[t_cnt++] = tagItem("bowDrop4", "bowDrop4", "폭발 활", " ", EQUIPMENT, BOW, 1, 10);

	items[t_cnt++] = tagItem("pickaxe1", "pickaxe1", "곡괭이", " ", EQUIPMENT, PICKAXE, 1, 15);
	items[t_cnt++] = tagItem("pickaxe2", "pickaxe2", "단단한 곡괭이", " ", EQUIPMENT, PICKAXE, 1, 20);
	items[t_cnt++] = tagItem("pickaxe3", "pickaxe3", "강철 곡괭이", " ", EQUIPMENT, PICKAXE, 1, 25);
	items[t_cnt++] = tagItem("pickaxe4", "pickaxe4", "합금 곡괭이", " ", EQUIPMENT, PICKAXE, 1, 30);


	items[t_cnt++] = tagItem("swordDrop1", "swordDrop1", "검", " ", EQUIPMENT, SWORD, 1, 25);
	items[t_cnt++] = tagItem("swordDrop2", "swordDrop2", "강철 검", " ", EQUIPMENT, SWORD, 1, 35);
	items[t_cnt++] = tagItem("swordDrop3", "swordDrop3", "황금 검", " ", EQUIPMENT, SWORD, 1, 45);
	items[t_cnt++] = tagItem("swordDrop4", "swordDrop4", "화염 검", " ", EQUIPMENT, SWORD, 1, 55);

	



	//======================================================================================================
	//제작								이름			재료1  필요개수1   재료2	 필요개수2  재료3  필요개수3  재료4  필요개수4  시간  재료갯수 빌딩이름
	//제봉소
	item_make[m_cnt++] = tagItemInfo("threadDrop","treeDrop",1,"",0,"",0,"",0,5,1, MaterialsType::SEWINGMACHINE);
	item_make[m_cnt++] = tagItemInfo("Flag1", "threadDrop", 100, "treeDrop", 50, "boositemDrop", 10, "", 0, 72, 3, MaterialsType::SEWINGMACHINE);
	item_make[m_cnt++] = tagItemInfo("Flag2", "threadDrop", 120, "treeDrop", 100, "boositemDrop", 20, "", 0, 96, 3, MaterialsType::SEWINGMACHINE);
	item_make[m_cnt++] = tagItemInfo("Flag3", "threadDrop", 150, "treeDrop", 150, "boositemDrop", 30, "", 0, 126, 3, MaterialsType::SEWINGMACHINE);
	item_make[m_cnt++] = tagItemInfo("Flag4", "threadDrop", 200, "treeDrop", 200, "boositemDrop", 40, "", 0, 168, 3, MaterialsType::SEWINGMACHINE);


	//모루
	item_make[m_cnt++] = tagItemInfo("img_game_money_icon","goldOreDrop",1,"",0,"",0,"",0,5,1, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("arrowDrop","treeDrop",2,"rockDrop",2,"",0,"",0,5,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("pickaxe2","ironOreDrop",3,"rockDrop",5,"",0,"",0,5,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("pickaxe3","SteelhDrop",2,"coalDrop",5,"",0,"",0,5,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("pickaxe4","high_class_SteelDrop",2,"ironBarDrop",4,"",0,"",0,5,2, MaterialsType::ANVIL);


	item_make[m_cnt++] = tagItemInfo("swordDrop1","goldBarDrop",2,"rockDrop",5,"",0,"",0,16,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("swordDrop2","ironBarDrop",6,"ironOreDrop",8,"",0,"",0,24,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("swordDrop3","SteelhDrop",5,"goldBarDrop",5,"goldOreDrop",10,"",0,32,3, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("swordDrop4","high_class_SteelDrop",5,"goldBarDrop",5,"ironBarDrop",5,"coalDrop",25,64,4, MaterialsType::ANVIL);

	item_make[m_cnt++] = tagItemInfo("bowDrop1","ironBarDrop",2,"rockDrop",5,"",0,"",0,5,2, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("bowDrop2","threadDrop",2,"SteelhDrop",2,"ironOreDrop",5,"",0,15,3, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("bowDrop3","threadDrop",5,"goldBarDrop",5,"goldOreDrop",5,"",0,30,3, MaterialsType::ANVIL);
	item_make[m_cnt++] = tagItemInfo("bowDrop4","threadDrop",10,"goldBarDrop",5,"ironBarDrop",5,"coalDrop",10,60,4, MaterialsType::ANVIL);


	//용광로
	item_make[m_cnt++] = tagItemInfo("coalDrop","treeDrop",1,"",0,"",0,"",0,5,1, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("brickDrop","coalDrop",2,"rockDrop",2,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("ironBarDrop","ironOreDrop",1,"coalDrop",1,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("goldBarDrop","goldOreDrop",1,"coalDrop",1,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("SteelhDrop","ironOreDrop",2,"rockDrop",2,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("high_class_SteelDrop","SteelhDrop",1,"ironOreDrop",3,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("roast_fishDrop","fishDrop",1,"coalDrop",2,"",0,"",0,5,2, MaterialsType::STEELWORK);
	item_make[m_cnt++] = tagItemInfo("GlassDrop","goldOreDrop",1,"coalDrop",2,"rockDrop",2,"",0,5,3, MaterialsType::STEELWORK);



	//우물
	item_make[m_cnt++] = tagItemInfo("여신의 우물2", "high_class_SteelDrop", 10, "GlassDrop", 10, "goldBarDrop", 20, "", 0, 5, 3, MaterialsType::NONE3);
	item_make[m_cnt++] = tagItemInfo("여신의 우물3", "high_class_SteelDrop", 30, "GlassDrop", 30, "goldBarDrop", 30, "", 0, 5, 3, MaterialsType::NONE3);
	item_make[m_cnt++] = tagItemInfo("여신의 우물4", "high_class_SteelDrop", 50, "GlassDrop", 40, "goldBarDrop", 40, "", 0, 5, 3, MaterialsType::NONE3);
	item_make[m_cnt++] = tagItemInfo("여신의 우물5", "high_class_SteelDrop", 60, "GlassDrop", 60, "goldBarDrop", 50, "", 0, 5, 3, MaterialsType::NONE3);


	item_make[m_cnt++] = tagItemInfo("요정의 나무2", "GlassDrop", 10, "brickDrop", 10, "goldBarDrop", 20, "", 0, 5, 3, MaterialsType::NONE3);
	item_make[m_cnt++] = tagItemInfo("요정의 나무3", "GlassDrop", 30, "brickDrop", 30, "goldBarDrop", 30, "", 0, 5, 3, MaterialsType::NONE3);
	item_make[m_cnt++] = tagItemInfo("요정의 나무4", "GlassDrop", 50, "brickDrop", 40, "goldBarDrop", 40, "", 0, 5, 3, MaterialsType::NONE3);
	item_make[m_cnt++] = tagItemInfo("요정의 나무5", "GlassDrop", 60, "brickDrop", 60, "goldBarDrop", 50, "", 0, 5, 3, MaterialsType::NONE3);


	item_make[m_cnt++] = tagItemInfo("산신령의 묘석2", "high_class_SteelDrop", 10, "brickDrop", 10, "goldBarDrop", 20, "", 0, 5, 3, MaterialsType::NONE3);
	item_make[m_cnt++] = tagItemInfo("산신령의 묘석3", "high_class_SteelDrop", 30, "brickDrop", 30, "goldBarDrop", 30, "", 0, 5, 3, MaterialsType::NONE3);
	item_make[m_cnt++] = tagItemInfo("산신령의 묘석4", "high_class_SteelDrop", 50, "brickDrop", 40, "goldBarDrop", 40, "", 0, 5, 3, MaterialsType::NONE3);
	item_make[m_cnt++] = tagItemInfo("산신령의 묘석5", "high_class_SteelDrop", 60, "brickDrop", 50, "goldBarDrop", 50, "", 0, 5, 3, MaterialsType::NONE3);




	for (int i = 0; i < ITEM_MAX; i++) {
		_itemDictionary.insert(make_pair(items[i].itemKey, items[i]));
	}

	for (int i = 0; i < ITEM_MAKE_MAX; i++) {
		_itemMaterials.insert(make_pair(item_make[i].itemKey, item_make[i]));
	}

}
