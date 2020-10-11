#pragma once
#include "singletonBase.h"
#include "building.h"
#include "enemy.h"
#include "fieldItem.h"
#include "resource.h"
#include "building.h"
#include "unit.h"
#include "skull.h"
#include "cow.h"

class productionManager;
class UnitManager : public singletonBase<UnitManager>
{
private:
	vector<unit*> _vUnits;


	productionManager* _production;				//건물 설치시 위치 받기
private:
	void Sorting();
	void CheckRemoveUnit();

	unit* _player;
	

public:
	void init();
	void release();
	void update();
	void render(HDC hdc);

	void AddUnits(unit* p_unit);
	void AddUnits(tile* p_tile);
	void AddUnits(unit* p_enemy, string p_monsterName);
	void AddUnits(string p_itemKey, POINT p_pos);

	void AddBuilding(string buildkey, tile* _tile);
	void AddBuilding(string buildkey, vector<tile*> tiles);


public:
	vector<unit*> GetUnits() { return _vUnits; };

	void setproductionInfo(productionManager* _p) {
		_production = _p;
	}
};

