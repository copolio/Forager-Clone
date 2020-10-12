#include "unit.h"
#include "earth.h"

#pragma once
class SpawnManager
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
	void SpawnPatternOne(string p_enemyName, int p_count);
};

