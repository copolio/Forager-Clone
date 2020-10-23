#include "stdafx.h"
#include "demon.h"

HRESULT demon::init()
{
	_state4 = DIDLE;
	demonWaitCount = 0;
	demonBrassCount = 0;
	demonHitCount = 0;
	searchCount = 0;
	demonAttackRange = 350;
	skillFireCount = 0;

	tryAttack = false;
	isattacking = true;
	Atk = 1;

	return S_OK;
}

void demon::update()
{
	demonAnimation();
	demonLookDirection();
	demonAttack();
	demonMove();

}

void demon::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left - 11), CAMERA->GetRelativeY(rc.bottom + 16));
		_hpBar.render(hdc);
	}

	switch (_state4)
	{
	case DWALK:
		IMAGEMANAGER->frameRender("demonWalk", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case DIDLE:
		IMAGEMANAGER->frameRender("demonIdle", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case DYELL:
		IMAGEMANAGER->frameRender("demonYell", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	}
}

void demon::demonMove()
{
	if (_state4 == DIDLE)
	{
		if (!checkDestination)
		{
			searchCount++;
			if (searchCount > 50)
			{
				if (isattacking) {
					
					auto path = ASTAR->pathFinding(_map->GetTiles(), _enemyTilePos, _target->GetPlayerTilePos(), true, false);
					//_vDestTileIndex = path;
					if (path.size() > 0) {
						_vDestTileIndex.push_back(path[0]);
						_enemyTilePos = path[0];
						checkDestination = true;
						_destCount = 0;
					}
					else {
						vector<int> vPossibleDestination;
						//동
						if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 &&
							!_map->GetTile(_enemyTilePos + 1).hasUnit &&
							_map->GetTile(_enemyTilePos + 1).terrKey == "plaintile") {
							vPossibleDestination.push_back(_enemyTilePos + 1);
						}
						//서
						if (_map->GetTileX(_enemyTilePos) > 0 &&
							!_map->GetTile(_enemyTilePos - 1).hasUnit &&
							_map->GetTile(_enemyTilePos - 1).terrKey == "plaintile") {
							vPossibleDestination.push_back(_enemyTilePos - 1);
						}
						//남
						if (_map->GetTileY(_enemyTilePos) < MAPTILEY - 1 &&
							!_map->GetTile(_enemyTilePos + MAPTILEX).hasUnit &&
							_map->GetTile(_enemyTilePos + MAPTILEX).terrKey == "plaintile") {
							vPossibleDestination.push_back(_enemyTilePos + MAPTILEX);
						}
						//북
						if (_map->GetTileX(_enemyTilePos) > 0 &&
							!_map->GetTile(_enemyTilePos - MAPTILEX).hasUnit &&
							_map->GetTile(_enemyTilePos - MAPTILEX).terrKey == "plaintile") {
							vPossibleDestination.push_back(_enemyTilePos - MAPTILEX);
						}
						if (vPossibleDestination.size() > 0) {
							int randDestInd = RANDOM->range(int(vPossibleDestination.size()));
							if (vPossibleDestination[randDestInd] > _enemyTilePos) {
								isLeft = false;
							}
							else if (vPossibleDestination[randDestInd] <= _enemyTilePos) {
								isLeft = true;
							}
							_vDestTileIndex.push_back(vPossibleDestination[randDestInd]);
							_enemyTilePos = vPossibleDestination[randDestInd];
						}
						checkDestination = true;
						_destCount = 0;
					}
				}
				else {
					vector<int> vPossibleDestination;
					//동
					if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 &&
						!_map->GetTile(_enemyTilePos + 1).hasUnit &&
						_map->GetTile(_enemyTilePos + 1).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos + 1);
					}
					//서
					if (_map->GetTileX(_enemyTilePos) > 0 &&
						!_map->GetTile(_enemyTilePos - 1).hasUnit &&
						_map->GetTile(_enemyTilePos - 1).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos - 1);
					}
					//남
					if (_map->GetTileY(_enemyTilePos) < MAPTILEY - 1 &&
						!_map->GetTile(_enemyTilePos + MAPTILEX).hasUnit &&
						_map->GetTile(_enemyTilePos + MAPTILEX).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos + MAPTILEX);
					}
					//북
					if (_map->GetTileX(_enemyTilePos) > 0 &&
						!_map->GetTile(_enemyTilePos - MAPTILEX).hasUnit &&
						_map->GetTile(_enemyTilePos - MAPTILEX).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos - MAPTILEX);
					}
					if (vPossibleDestination.size() > 0) {
						int randDestInd = RANDOM->range(int(vPossibleDestination.size()));
						if (vPossibleDestination[randDestInd] > _enemyTilePos) {
							isLeft = false;
						}
						else if (vPossibleDestination[randDestInd] <= _enemyTilePos) {
							isLeft = true;
						}
						_vDestTileIndex.push_back(vPossibleDestination[randDestInd]);
						_enemyTilePos = vPossibleDestination[randDestInd];
					}
					checkDestination = true;
					_destCount = 0;
				}
	
			}
		}
		else
		{
			_state4 = DWALK;
			if (_vDestTileIndex.size() > 0)
			{
				POINT tDestination = { _map->GetTile(_vDestTileIndex[_destCount]).rc.left , _map->GetTile(_vDestTileIndex[_destCount]).rc.top };
				if (abs(rc.left - tDestination.x) > MOVESPEED || abs(rc.top - tDestination.y) > MOVESPEED)
				{
					if (tDestination.x < rc.left)
					{
						OffsetRect(&rc, -MOVESPEED, 0);
					}
					else if (tDestination.x > rc.left)
					{
						OffsetRect(&rc, MOVESPEED, 0);
					}
					if (tDestination.y > rc.top)
					{
						OffsetRect(&rc, 0, MOVESPEED);
					}
					else if (tDestination.y < rc.top)
					{
						OffsetRect(&rc, 0, -MOVESPEED);
					}
	
				}
				else
				{
					_destCount++;
					if (_vDestTileIndex.size() <= _destCount)
					{
						checkDestination = false;
						searchCount = 0;
						_vDestTileIndex.clear();
					}
				}
			}
		}
	}
}

void demon::demonAttack()
{
	if (!tryAttack)
	{
		if (abs(_target->rc.left - rc.left) <= demonAttackRange && abs(_target->rc.top - rc.top) <= 30) {
			tryAttack = true;
			isattacking = true;
		}
		else
			_state4 = DIDLE;
	}
	else
	{
		demonWaitCount++;
		if (demonWaitCount > 23)
		{
			_state4 = DYELL;
			demonBrassFire();
			
		}
		else
			_state4 = DIDLE;
	}
}

void demon::demonAnimation()
{
	switch (_state4)
	{
	case DWALK:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 11)
				_index == 0;
		}
		break;
		break;
	case DIDLE:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 4)
				_index = 0;
		}
		break;
	case DYELL:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 15 == 0)
		{
			if (_index++ > 10)
			{
				_index = 0;
				demonWaitCount = 0;
				demonHitCount = 1;
				tryAttack = false;
				
					
			}

		}
		break;
	}
}

void demon::demonLookDirection()
{
	if (_state4 == DIDLE || _state4 == DWALK)
	{
		if (rc.right > _target->rc.right && rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}
}

void demon::demonBrassFire()
{
	skillFireCount++;
	if (skillFireCount % 200 == 0) {
		SOUNDMANAGER->play("악마불지질때소리");
		_count = 0;
		_index = 0;
		
		for (int i = 0; i < 2; i++)
		{
			if(isLeft)
				UNITMANAGER->GetProjectileMG()->CreateProjectile("demonBrass", GetCenterX() - 320, GetCenterY() - 40, 1, 320, 40, isLeft);
			else
				UNITMANAGER->GetProjectileMG()->CreateProjectile("demonBrass", GetCenterX(), GetCenterY() - 40, 1, 320, 40, isLeft);
		}
		skillFireCount = 0;
	}
}
