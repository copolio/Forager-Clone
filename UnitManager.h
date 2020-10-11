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
#include "earth.h"

class UnitManager : public singletonBase<UnitManager>
{
private:
	vector<unit*> _vUnits;


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
	void AddUnits(skull* p_unit, bool test);
	void AddUnits(tile* p_tile);
	void AddUnits(unit* p_enemy, string p_monsterName);
	void AddUnits(string p_itemKey, POINT p_pos);

	void AddBuilding(string buildkey, tile* _tile);
	void AddBuilding(string buildkey, vector<tile*> tiles);

	void AddProduction(string p_itemKey, POINT p_pos);

public:
	vector<unit*> GetUnits() { return _vUnits; };
};

