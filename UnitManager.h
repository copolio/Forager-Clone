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
#include "ForagerPlayer.h"
#include "ProjectileManager.h"
#include "wraith.h"
#include "npc.h"

class earth;

class UnitManager : public singletonBase<UnitManager>
{
private:
	vector<unit*> _vUnits;
	tagProjectile* _pProjectiles;
	earth *_map;
	SpawnManager *_spawnManager;
	ProjectileManager *_projectileManager;

private:
	void Sorting();
	void CheckRemoveUnit();

	ForagerPlayer* _player;
public:
	void init();
	void release();
	void update();
	void render(HDC hdc);

	void checkCollision(unit* p_unit);
	void AddUnits(ForagerPlayer* p_unit);
	void AddUnits(skull* p_unit, bool test);
	void AddUnits(wraith* p_unit, bool test);
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
	ProjectileManager* GetProjectileMG() { return _projectileManager; };
};

