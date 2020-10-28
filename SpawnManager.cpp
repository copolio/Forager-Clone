#include "stdafx.h"
#include "SpawnManager.h"


void SpawnManager::init()
{
	timer = 0.0f;
	pattern = 0;
}

void SpawnManager::update()
{
	timer += TIME->deltaTime();

	if (timer >= 7.0f) {

		float errorValue = timer - 7.0f;
		timer = errorValue;
		TrySpawn();
	}
}


void SpawnManager::GetCanSpawnTile()
{
	vector<tile> t_vTiles = _map->GetTiles();
	for (int i = 0; i < t_vTiles.size(); i++) {
		if (t_vTiles[i].terrKey == "plaintile" && !t_vTiles[i].hasUnit) {
			_plainTile.push_back(t_vTiles[i]);
		}
	}
}

void SpawnManager::TrySpawn()
{

	if (UNITMANAGER->GetMonsterCount() < MAXENEMYUNIT && _map->GetIslandCount() >= 2) {

		GetCanSpawnTile();

		if (_plainTile.size() > 0) {
			if (UNITMANAGER->GetCowCount() < _map->GetIslandCount())
			switch (pattern)
			{
			case 0:
				//SpawnPatternOne("skull", 10);
				//SpawnPatternOne("demonIdle",1);
				SpawnPatternOne("cow",1);
				//SpawnPatternOne("slime",1);
				
				break;
			}
		}
		_plainTile.clear();
	}
}





void SpawnManager::SpawnPatternOne(string p_enemyName, int p_count)
{
	if (UNITMANAGER->GetMonsterCount() >= MAXENEMYUNIT) return;
	for (int i = 0; i < p_count; i++) {
		int randomTile = RANDOM->range(0, _plainTile.size() - 1);
		RECT t_rc = _plainTile[randomTile].rc;
		POINT t_ptPos = { t_rc.left + (t_rc.right - t_rc.left) / 2,
							t_rc.top + (t_rc.bottom - t_rc.top) / 2 };

		UNITMANAGER->AddUnits(p_enemyName, t_ptPos, true);
	}
}
void SpawnManager::SpawnPatternOne(string p_enemyName, int p_count, int tileidx)
{
	if (UNITMANAGER->GetMonsterCount() >= MAXENEMYUNIT) return;
	for (int i = 0; i < p_count; i++) {
		RECT t_rc = _map->GetTiles()[tileidx].rc;
		POINT t_ptPos = { t_rc.left + (t_rc.right - t_rc.left) / 2,
							t_rc.top + (t_rc.bottom - t_rc.top) / 2 };
		UNITMANAGER->AddUnits(p_enemyName, t_ptPos, true);
	}
}
