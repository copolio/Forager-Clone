#pragma once
#include "singletonBase.h"
#include "building.h"
#include "enemy.h"
#include "fieldItem.h"
#include "inGameResource.h"
#include "building.h"
#include "unit.h"
#include "skull.h"
#include "cow.h"
#include "tile.h"
#include "earth.h"
//#include "SpawnManager.h"
#include "ForagerPlayer.h"
#include "ProjectileManager.h"
#include "wraith.h"
#include "npc.h"
#include "demon.h"
#include "fishTrap.h"
#include "muBoss.h"
#include "treasureBox.h"


#define MAXENEMYUNIT 40

class earth;

class UnitManager : public singletonBase<UnitManager>
{
private:
	vector<unit*> _vUnits;
	vector<enemy*> _vEnemy;
	vector<npc*> _vNpc;

	tagProjectile* _pProjectiles;
	earth *_map;
	//SpawnManager *_spawnManager;
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
	void AddUnits(cow* p_unit, bool test);
	void AddUnits(demon* p_unit, bool test);
	void AddUnits(muBoss* p_unit, bool test);
	void AddUnits(tile* p_tile);
	void AddUnits(string p_monsterName, POINT p_pos, bool enemyCheck);
	void AddUnits(string p_itemKey, POINT p_pos);

	void AddBuilding(string buildkey, tile* _tile, int tileindex);
	void AddBuilding(string buildkey, vector<tile*> tiles, int tileindex);

	void AddProduction(string p_itemKey, POINT p_pos);
	void AddResource(tile* _tile, int p_tileIndex);
	void AddResource(string key, tile* _tile, int p_tileIndex);
	
	void AddTreasure(string p_key, string p_itemRewardKey, POINT p_ptPos);

public:
	vector<unit*> GetUnits() { return _vUnits; };
	vector<npc*>* PGetNpc() { return &_vNpc; }
	vector<npc*> GetNpc() { return _vNpc; }
	int GetMonsterCount();
	void setLinkMap(earth *p_map);
	ProjectileManager* GetProjectileMG() { return _projectileManager; };
	RECT GetPlayerRc() { return _player->rc; };
	POINT GetPlayerFootPt();
	int GetCowCount();
};

