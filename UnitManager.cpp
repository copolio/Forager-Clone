	#include "stdafx.h"
#include "UnitManager.h"

void UnitManager::init()
{
	//자원
	IMAGEMANAGER->addFrameImage("berry", "Images/이미지/오브젝트/resource/img_object_berry.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rock", "Images/이미지/오브젝트/resource/img_object_rock.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tree", "Images/이미지/오브젝트/resource/img_object_tree.bmp", 280, 168, 5, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("berryDrop", "Images/이미지/아이템/berry.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rockDrop", "Images/이미지/아이템/돌.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("treeDrop", "Images/이미지/아이템/wood.bmp", 56, 56, true, RGB(255, 0, 255));

	//에너미 - 해골
	IMAGEMANAGER->addFrameImage("skull", "Images/이미지/NPC/해골idle.bmp", 280, 112, 5, 2, true, RGB(255, 0, 255));
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
		if (_vUnits[i]->tag != TAG::PLAYER) {
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
		skull* _skull = new skull;
		_skull->setEnemy();
		_vUnits.push_back(_skull);

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
}


