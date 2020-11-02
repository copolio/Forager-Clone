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
				//SpawnPatternOne("cow",1, 100);
				//SpawnPatternOne("slime",1);
				//SpawnPatternOne("slimeBoss",1);
				//SpawnPatternOne("smallMu",1);
				
				break;
			}
		}
		_plainTile.clear();
	}
}





void SpawnManager::SpawnPatternOne(string p_enemyName, int p_count, int p_hp)
{
	if (UNITMANAGER->GetMonsterCount() >= MAXENEMYUNIT) return;
	if (_plainTile.size() <= 0)
		GetCanSpawnTile();
	for (int i = 0; i < p_count; i++) {
		int randomTile = RANDOM->range(0, _plainTile.size() - 1);
		RECT t_rc = _plainTile[randomTile].rc;
		POINT t_ptPos = { t_rc.left + (t_rc.right - t_rc.left) / 2,
							t_rc.top + (t_rc.bottom - t_rc.top) / 2 };

		UNITMANAGER->AddUnits(p_enemyName, t_ptPos, true, p_hp);
	}
}
void SpawnManager::SpawnPatternOne(string p_enemyName, int p_count, int tileidx, int islandX, int islandY)
{
	if (UNITMANAGER->GetMonsterCount() >= MAXENEMYUNIT) return;
	for (int i = 0; i < p_count; i++) {
		RECT t_rc = _map->GetTiles()[tileidx].rc;
		POINT t_ptPos = { t_rc.left + (t_rc.right - t_rc.left) / 2,
							t_rc.top + (t_rc.bottom - t_rc.top) / 2 };

		int t_hp = SetDifficultHp(islandX, islandY);

		UNITMANAGER->AddUnits(p_enemyName, t_ptPos, true, t_hp);
	}
}

void SpawnManager::SpawnPatternOne(string p_enemyName, int p_count, int tileidx, bool p_isReal, int islandX, int islandY)
{
	if (UNITMANAGER->GetMonsterCount() >= MAXENEMYUNIT) return;

	RECT t_rc = _map->GetTiles()[tileidx].rc;
	POINT t_ptPos = { t_rc.left + (t_rc.right - t_rc.left) / 2,
						t_rc.top + (t_rc.bottom - t_rc.top) / 2 };

	int t_hp = SetDifficultHp(islandX, islandY);

	UNITMANAGER->AddSlimeBoss(t_ptPos, p_isReal, t_hp);
}

int SpawnManager::SetDifficultHp(int p_islandX, int p_islandY)
{

	// 스타트섬 주변은 체력 80
	if (2 <= p_islandY && p_islandY <= 4)
	{
		if (2 <= p_islandX && p_islandX <= 4) {
			return 80;
		}
	}
	// 스타트섬 그 다음 주변 섬은 체력 100
	else if (1 <= p_islandY && p_islandY <= 5)
	{
		if (1 <= p_islandX && p_islandX <= 5) {
			return 100;
		}
	}
	// 외곽은 체력 120
	else
		return 120;
}
