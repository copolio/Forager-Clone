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
#include "tile.h"
#include "earth.h"
#include "SpawnManager.h"

class earth;

class UnitManager : public singletonBase<UnitManager>
{
private:
	vector<unit*> _vUnits;
	earth *_map;
	SpawnManager *_spawnManager;

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
	void AddUnits(string p_monsterName, POINT p_pos, bool enemyCheck);
	void AddUnits(string p_itemKey, POINT p_pos);

	void AddBuilding(string buildkey, tile* _tile);
	void AddBuilding(string buildkey, vector<tile*> tiles);

	void AddProduction(string p_itemKey, POINT p_pos);

public:
	vector<unit*> GetUnits() { return _vUnits; };
	int GetMonsterCount();
	void setLinkMap(earth *p_map);
};

