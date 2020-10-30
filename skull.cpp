#include "stdafx.h"
#include "skull.h"


HRESULT skull::init()
{
	//skullMoveCount = 0;
	//skullIdleCount = 0;
	searchCount = 0;
	skullHitCount = 0;
	skullHitWaitCount = 0;
	skullAttackRange = 80;
	_attackIndex = 0;
	//hitPlayer = false;
	tryAttack = false;
	isattacking = true;
	_state = APPEAR;
	
	return S_OK;
}

void skull::update()
{
	skullAnimation();
	skullMove();
	if (_state != APPEAR) {
		canAttackCheck();
	}
	skullLookDirection();
	
}

void skull::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left-11), CAMERA->GetRelativeY(rc.bottom + 16));
		_hpBar.render(hdc);
	}
	switch (_state)
	{
	case STAY:
		IMAGEMANAGER->frameRender("skull", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case ATTACK:
		IMAGEMANAGER->frameRender("skullAttack", hdc, CAMERA->GetRelativeX(rc.left - 53),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case APPEAR:
		IMAGEMANAGER->frameRender("skullAppear", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case IDLE2:
		IMAGEMANAGER->frameRender("skullIdle", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	}	
	RECT temp;
	if (IntersectRect(&temp, &CAMERA->GetCameraRect(), &rc)) {
		if (_state == STAY) {
			POINT ptCenter = { rc.left + (rc.right - rc.left) / 2 + RANDOM->range(-10, 0), rc.top + (rc.bottom - rc.top) / 2 - RANDOM->range(-1, -6) };
			// ¹ß°ÉÀ½ ÀÌÆåÆ®
			if (_count % 10 == 0) {
				float randomScale = RANDOM->range(0.5f, 0.7f);
				EFFECTMANAGER->ShowEffectAlphaSize("Walk1", ptCenter, 0.25f, randomScale, 50, 200, true);
			}
		}
	}
}

//1Å¸ÀÏ¾¿ »óÇÏÁÂ¿ì ·£´ý¿òÁ÷ÀÌ´Âµ¥, ÃÑ 5¹ø 
void skull::skullMove()
{
	if (_state == STAY)
	{
		if (!checkDestination)
		{
			searchCount++;
			if (searchCount > 1)
			{
				if (isattacking) {
					vector<int> path = ASTAR->pathFinding(_map->GetTiles(), _enemyTilePos, _target->GetPlayerTilePos(), true, true);
					//_vDestTileIndex = path;
					if (path.size() > 0) {
						_vDestTileIndex.push_back(path[0]);
						_enemyTilePos = path[0];
						checkDestination = true;
						_destCount = 0;
					}
					else {
						vector<int> vPossibleDestination;
						//µ¿
						if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 &&
							!_map->GetTile(_enemyTilePos + 1).hasUnit &&
							_map->GetTile(_enemyTilePos + 1).terrKey == "plaintile") {
							vPossibleDestination.push_back(_enemyTilePos + 1);
						}
						//¼­
						if (_map->GetTileX(_enemyTilePos) > 0 &&
							!_map->GetTile(_enemyTilePos - 1).hasUnit &&
							_map->GetTile(_enemyTilePos - 1).terrKey == "plaintile") {
							vPossibleDestination.push_back(_enemyTilePos - 1);
						}
						//³²
						if (_map->GetTileY(_enemyTilePos) < MAPTILEY - 1 &&
							!_map->GetTile(_enemyTilePos + MAPTILEX).hasUnit &&
							_map->GetTile(_enemyTilePos + MAPTILEX).terrKey == "plaintile") {
							vPossibleDestination.push_back(_enemyTilePos + MAPTILEX);
						}
						//ºÏ
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
					//µ¿
					if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 &&
						!_map->GetTile(_enemyTilePos + 1).hasUnit &&
						_map->GetTile(_enemyTilePos + 1).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos + 1);
					}
					//¼­
					if (_map->GetTileX(_enemyTilePos) > 0 &&
						!_map->GetTile(_enemyTilePos - 1).hasUnit &&
						_map->GetTile(_enemyTilePos - 1).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos - 1);
					}
					//³²
					if (_map->GetTileY(_enemyTilePos) < MAPTILEY - 1 &&
						!_map->GetTile(_enemyTilePos + MAPTILEX).hasUnit &&
						_map->GetTile(_enemyTilePos + MAPTILEX).terrKey == "plaintile") {
						vPossibleDestination.push_back(_enemyTilePos + MAPTILEX);
					}
					//ºÏ
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
			if (_vDestTileIndex.size() > 0)
			{
				POINT tDestination = { _map->GetTile(_vDestTileIndex[_destCount]).rc.left , _map->GetTile(_vDestTileIndex[_destCount]).rc.top };
				if (abs(rc.left - tDestination.x) > enemySpeedX || abs(rc.top - tDestination.y) > enemySpeedY)
				{
					if (tDestination.x < rc.left)
					{
						OffsetRect(&rc, -enemySpeedX, 0);
					}
					else if (tDestination.x > rc.left)
					{
						OffsetRect(&rc, enemySpeedX, 0);
					}
					if (tDestination.y > rc.top)
					{
						OffsetRect(&rc, 0, enemySpeedY);
					}
					else if (tDestination.y < rc.top)
					{
						OffsetRect(&rc, 0, -enemySpeedY);
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

void skull::canAttackCheck()
{
	if (!tryAttack)
	{
		if (abs(_target->rc.left - rc.left) <= skullAttackRange && abs(_target->rc.top - rc.top) <= skullAttackRange)
		{
			tryAttack = true;
			isattacking = true;
		}
		else
			_state = STAY;
	}
	else
	{

		if (skullHitWaitCount > 120)
		{
			if (skullHitCount == 17) {
				if (abs(_target->rc.left - rc.left) <= skullAttackRange && abs(_target->rc.top - rc.top) <= skullAttackRange)
					_target->hurt(atk);
			}
			_state = ATTACK;
		}
		else {
			skullHitWaitCount++;
			_state = IDLE2;
		}
	}
}

void skull::skullAnimation()
{
	switch (_state)
	{
		//ÇØ°ñ ¶Ù´ó±è
	case STAY:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 5)
				_index = 0;
		}
		break;
		//ÇØ°ñ ¶¥¿¡¼­ µîÀå.
	case APPEAR:
		objFrameY = 0;
		objFrameX = _index;
		if (_count++ % 30 == 0)
		{
			if (_index++ > 4)
			{
				_index = 0;
				_state = STAY;
			}
		}
		break;

	case IDLE2:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 5)
				_index = 0;
		}
		break;
		//ÇØ°ñ °ø°Ý
	case ATTACK:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _attackIndex;

		skullHitCount++;
		if (skullHitCount < 5) _attackIndex = 0;
		else if (skullHitCount == 10) _attackIndex = 1;
		else if (skullHitCount == 15) _attackIndex = 2;
		else if (skullHitCount == 20) _attackIndex = 1;
		else if (skullHitCount >= 25) {
			_attackIndex = 0;
			skullHitCount = 1;
			skullHitWaitCount = 0;
			tryAttack = false;
			searchCount = 0;
			checkDestination = false;
			isattacking = true;
			_state = STAY;
		}
		break;
	}
}

void skull::skullLookDirection()
{
	if (_state == ATTACK || isattacking)
	{
		if (rc.right > _target->rc.right && rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}
}

