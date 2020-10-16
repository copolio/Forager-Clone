#include "stdafx.h"
#include "enemy.h"
#include "earth.h"

void enemy::render(HDC hdc)
{
	
	

}

void enemy::update()
{
	

}

void enemy::setEnemy(string key, string itemkey, ForagerPlayer* target, POINT pos)
{
	tileIndex = 0;

	
	tag = TAG::ENEMY;
	layer = LAYER::OBJECT;
	_target = target;
	//_mapTile = mapTile;

	x = pos.x;
	y = pos.y;

	//rc = RectMakeCenter(x, y, 25, 25);
	objKey = key;
	if (objKey == "wraithIdle")
	{
		rc = RectMakeCenter(x, y, 100, 100);
		maxHp = 100;
		currentHp = 100;
		exp = 50;

	}
	else if (objKey == "skull")
	{
		rc = RectMakeCenter(x, y, 35, 35);
		maxHp = 30;
		currentHp = 30;
		exp = 10;
	}
	else if (objKey == "cow")
	{
		rc = RectMakeCenter(x, y, 55, 55);
		maxHp = 50;
		currentHp = 50;
		exp = 30;
	}
	

	dropItem.itemKey = itemkey;
	
	objFrameX = 0;
	objFrameY = 0;
	_destCount = 0;

	enemySpeedX = 3;
	enemySpeedY = 3;
	_index = 0;
	_attackIndex = 0;
	_count = 0;
	_appearCount = 0;
	
	enemyMoving = false;
	isLeft = false;
	isAngle = false;
	checkDestination = false;

	_enemyTilePos = FindEnemyTilePos();

	_hpBar.init("hpBar", "hpBarBG");
}



void enemy::dead()
{
	EFFECTMANAGER->ShowEffectFrame(EFFECTMANAGER->smokeEff, GetCenterPoint(), 4, true);

	UNITMANAGER->AddUnits(dropItem.itemKey, { GetCenterX(),GetCenterY() });
}

int enemy::FindEnemyTilePos()
{
	vector<tile> _vTiles = _map->GetTiles();
	POINT _ptSkullPos = { GetCenterX(), GetCenterY() };

	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, _ptSkullPos)) {
				return (i*MAPTILEY + j);
			}
		}
	}
}








	
