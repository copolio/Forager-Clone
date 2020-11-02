#pragma once

#include"singletonBase.h"
#include "unit.h"
#include "earth.h"

class SpawnManager : public singletonBase<SpawnManager>
{
private:
	earth *_map;
	vector<tile> _plainTile;

	float timer;
	int pattern;

public :
	void init();
	void setLinkMap(earth *p_map) { _map = p_map; };
	void update();

	void GetCanSpawnTile();
	void TrySpawn();
	void SpawnPatternOne(string p_enemyName, int p_count, int p_hp);
	void SpawnPatternOne(string p_enemyName, int p_count, int tileidx, int islandX, int islandY);
	void SpawnPatternOne(string p_enemyName, int p_count, int tileidx, bool p_isReal, int islandX, int islandY);
	int SetDifficultHp(int p_islandX, int p_islandY);

};

