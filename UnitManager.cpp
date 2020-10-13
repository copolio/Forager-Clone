#include "stdafx.h"
#include "UnitManager.h"
#include "productionManager.h"
void UnitManager::init()
{
	//자원 1 (나무, 돌, 열매)
	IMAGEMANAGER->addFrameImage("berry", "Images/이미지/오브젝트/resource/img_object_berry.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rock", "Images/이미지/오브젝트/resource/img_object_rock.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tree", "Images/이미지/오브젝트/resource/img_object_tree.bmp", 280, 168, 5, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("berryDrop", "Images/이미지/아이템/berry.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rockDrop", "Images/이미지/아이템/돌.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("treeDrop", "Images/이미지/아이템/wood.bmp", 56, 56, true, RGB(255, 0, 255));
	
	//자원 2 ('해골, 소'의 드랍아이템)
	IMAGEMANAGER->addImage("skullHeadDrop", "Images/이미지/아이템/skullHead.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("milkDrop", "Images/이미지/아이템/milk.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pooDrop", "Images/이미지/아이템/poo.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("letherDrop", "Images/이미지/아이템/lether.bmp", 56, 56, true, RGB(255, 0, 255));


	
	//에너미 - (해골, 소, 레이스)
	IMAGEMANAGER->addFrameImage("skull", "Images/이미지/NPC/해골idle.bmp", 280, 112, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullAppear", "Images/이미지/NPC/해골Appear.bmp", 224, 56, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullAttack", "Images/이미지/NPC/해골attack.bmp", 393, 112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullIdle", "Images/이미지/NPC/해골stay.bmp",224 ,112 , 4, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("cow", "Images/이미지/NPC/황소IDLE.bmp", 400, 100, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cowDash", "Images/이미지/NPC/황소WALK.bmp", 560, 100, 7, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("wraithAttack", "Images/이미지/NPC/레이스2.bmp", 1710, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wraithIdle", "Images/이미지/NPC/레이스IDLE2.bmp", 2280, 400, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("wraithBullet", "Images/이미지/NPC/레이스무기발사.bmp", 80, 600, 1, 2, true, RGB(255, 0, 255));
	


	// 체력바
	IMAGEMANAGER->addImage("hpBarBG", "Images/이미지/NPC/NPC체력(뒤).bmp", 50, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpBar", "Images/이미지/NPC/NPC체력(앞).bmp", 40, 10, true, RGB(255, 0, 255));
}

void UnitManager::release()
{
	for(int i = 0 ; i < _vUnits.size(); i++)
		SAFE_DELETE(_vUnits[i]);

	_vUnits.clear();

}


void UnitManager::update()
{
	Sorting();
	CheckRemoveUnit();

	for (int i = 0; i < _vUnits.size(); i++) {
		if (_vUnits[i]->tag != TAG::PLAYER ) {
			_vUnits[i]->update();
		}
	}
}


void UnitManager::render(HDC hdc)
{
	// 레이어 : Terrain
	for (int i = 0; i < _vUnits.size(); i++) {
		if ((*_vUnits[i]).layer == LAYER::TERRAIN) {
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &(*_vUnits[i]).rc)) continue;
			(*_vUnits[i]).render(hdc);
		}
	}

	// 레이어 : Object
	for (int i = 0; i < _vUnits.size(); i++) {
		if ((*_vUnits[i]).layer == LAYER::OBJECT) {
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &(*_vUnits[i]).rc)) continue;
			(*_vUnits[i]).render(hdc);
		}
	}
}



bool compare(unit* i, unit* j) {
	return (*i).GetCenterY() < (*j).GetCenterY();
}


// y축 정렬
void UnitManager::Sorting()
{
	sort(_vUnits.begin(), _vUnits.end(), compare);
}

// 죽거나 제거해야될 객체는 삭제
void UnitManager::CheckRemoveUnit()
{
	if (_vUnits.size() > 0) {
		for (auto iter = _vUnits.begin(); iter != _vUnits.end();) {
			if ((*iter)->isDead()) {
				SAFE_DELETE((*iter));
				iter = _vUnits.erase(iter);
			}
			else
				++iter;
		}
	}
}


void UnitManager::AddUnits(unit* p_unit)
{
	_player = p_unit;
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(skull* p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(wraith* p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(tile* p_tile)
{
	
	resource* _res = new resource;
	_res->setRandomRes(p_tile);
	_vUnits.push_back(_res);
}

void UnitManager::AddUnits(unit * p_enemy, string p_monsterName)
{
	//해골
	if (p_monsterName == "skull")
	{
		
		
		_vUnits.push_back(p_enemy);
	}
	
	//소
	if (p_monsterName == "cow")
	{
		cow* _cow = new cow;
		_cow->setEnemy(p_monsterName, "milkDrop", _player);
		_cow->init();
		_vUnits.push_back(_cow);
		
	}
	
	//레이스
	if (p_monsterName == "wraith")
	{
		//wraith* _wraith = new wraith;
		//_wraith->setEnemy(p_monsterN)
		_vUnits.push_back(p_enemy);

	}

}





// 유닛 추가
void UnitManager::AddUnits(string p_itemKey, POINT p_pos)
{
	for (int i = 0; i < 3; i++) {
		fieldItem* t_fieldItem = new fieldItem;
		t_fieldItem->setFieldItem(p_pos, p_itemKey);
		_vUnits.push_back(t_fieldItem);
	}
}

void UnitManager::AddProduction(string p_itemKey, POINT p_pos)
{
	fieldItem* t_fieldItem = new fieldItem;
	t_fieldItem->setFieldItem(p_pos, p_itemKey);
	_vUnits.push_back(t_fieldItem);
}

void UnitManager::AddBuilding(string buildkey, tile * _tile)
{
	building* _building = new building;
	_building->setBuilding(buildkey, _tile);
	_vUnits.push_back(_building);
}

void UnitManager::AddBuilding(string buildkey, vector<tile*> tiles)
{
	building* _building = new building;
	_building->setBuilding(buildkey, tiles);
	_vUnits.push_back(_building);
	PRODUCTIONMANAGER->settion(_building->rc);
	//_production->settion(_building->rc);

}




