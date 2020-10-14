#include "stdafx.h"
#include "cow.h"

HRESULT cow::init()
{
	cowHitCount = 0;
	cowHitWaitCount = 0;
	searchCount = 0;
	cowDashRange = 200;
	_attackIndex = 0;
	tryAttack = false;
	isattacking = false;

	return S_OK;
}

void cow::update()
{
	cowAnimation();
	cowMove();
	
	cowAttack();
	cowLookDirection();
}

void cow::render(HDC hdc)
{

	switch (_state2)
	{
	case IDLE3:
		IMAGEMANAGER->frameRender("cow", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case WALK:
		IMAGEMANAGER->frameRender("cowWalk", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case DASH:
		IMAGEMANAGER->frameRender("cowDash", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;

	}
}

void cow::cowAnimation()
{
	switch (_state2)
	{
		//소 걷기 
	case WALK:
		if (isLeft)
		{
			objFrameY = 1;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index-- <= 0)
					_index = 4;
			}
		}
		else
		{
			objFrameY = 0;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index++ > 5)
					_index = 0;
			}
		}
		break;
		//소 가만히.
	case IDLE3:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 5)
				_index = 0;
		}
		break;
		//소 돌진
	case DASH:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _attackIndex;

		cowHitCount++;
		if (cowHitCount < 5) _attackIndex = 0;
		else if (cowHitCount == 10) _attackIndex = 1;
		else if (cowHitCount == 15) _attackIndex = 2;
		else if (cowHitCount == 20) _attackIndex = 1;
		else if (cowHitCount >= 25) {
			_attackIndex = 0;
			cowHitCount = 1;
			cowHitWaitCount = 0;
			tryAttack = false;
		}
		break;
	}
}

void cow::cowMove()
{
	searchCount++;
	if (searchCount % 120 == 0)
	{
		if (_state2 == WALK)
		{
			if (!checkDestination)
			{
				if (isattacking) 
				{
					cout << " 호출됨" << endl;
					Astar astar;
					auto path = astar.pathFinding(_map->GetTiles(), _enemyTilePos, _target->GetPlayerTilePos(), true, false);
					//_vDestTileIndex = path;
					_vDestTileIndex.push_back(path[0]);
					_enemyTilePos = path[0];
					checkDestination = true;
					_destCount = 0;
				}
				else 
				{
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
			else
			{
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
}

void cow::cowAttack()
{
	if (!tryAttack)
	{
		if (abs(_target->rc.left - rc.left) <= cowDashRange && abs(_target->rc.top - rc.top) <= cowDashRange)
		{
			tryAttack = true;
			isattacking = true;
		}
		else
			_state2 = WALK;
	}
	else
	{
		if (cowHitWaitCount > 120)
		{
			//if (skullHitCount == 17) {
			//	if (abs(_target->rc.left - rc.left) <= skullAttackRange && abs(_target->rc.top - rc.top) <= skullAttackRange)	
			//		_target->hurt(Atk);
			//}
			_state2 = DASH;
		}
		else {
			cowHitWaitCount++;
			_state2 = IDLE3;
		}
	}
}

void cow::cowLookDirection()
{
	if (_state2 == DASH || _state2 == IDLE3 || _state2 == WALK)
	{
		if (rc.right > _target->rc.right && rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}
}
