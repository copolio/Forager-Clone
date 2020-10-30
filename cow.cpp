#include "stdafx.h"
#include "cow.h"

HRESULT cow::init()
{
	cowHitCount = 0;
	cowHitWaitCount = 0;
	searchCount = 0;
	cowDashRange = 100;
	_attackIndex = 0;
	tryAttack = false;
	isattacking = false;
	_state2 = WALK;
	Atk = 20;
	return S_OK;
}

void cow::update()
{
	cowAnimation();
	cowMove();
	cowAttackAttempt();
	cowLookDirection();
	cowDash();
	//checkCowTile();
}

void cow::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.bottom ));
		_hpBar.render(hdc);
	}
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
	RECT temp;
	if (IntersectRect(&temp, &CAMERA->GetCameraRect(), &rc)) {
		if (_state2 == WALK || _state2 == DASH) {
			POINT ptCenter = { rc.left + (rc.right - rc.left) / 2 + RANDOM->range(-10, 0), rc.top + (rc.bottom - rc.top) / 2 - RANDOM->range(-1, -6) };
			// 발걸음 이펙트
			if (_count % 10 == 0) {
				float randomScale = RANDOM->range(0.5f, 0.7f);
				EFFECTMANAGER->ShowEffectAlphaSize("Walk1", ptCenter, 0.25f, randomScale, 50, 200, true);
			}
		}
	}
}

void cow::cowAnimation()
{
	switch (_state2)
	{
		//소 걷기 
	case WALK:
		objFrameX = _index;
		objFrameY = (isLeft) ? 1 : 0;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 5)
				_index = 0;
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
	if (searchCount % 1 == 0)
	{
		if (_state2 == WALK)
		{
			if (!checkDestination)
			{
				if (isattacking) 
				{
					auto path = ASTAR->pathFinding(_map->GetTiles(), _enemyTilePos, _target->GetPlayerTilePos(), true, true);
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
							_map->GetTile(_enemyTilePos + 1).canPass) {
							vPossibleDestination.push_back(_enemyTilePos + 1);
						}
						//서
						if (_map->GetTileX(_enemyTilePos) > 0 &&
							_map->GetTile(_enemyTilePos - 1).canPass) {
							vPossibleDestination.push_back(_enemyTilePos - 1);
						}
						//남
						if (_map->GetTileY(_enemyTilePos) < MAPTILEY - 1 &&
							_map->GetTile(_enemyTilePos + MAPTILEX).canPass) {
							vPossibleDestination.push_back(_enemyTilePos + MAPTILEX);
						}
						//북
						if (_map->GetTileX(_enemyTilePos) > 0 &&
							_map->GetTile(_enemyTilePos - MAPTILEX).canPass) {
							vPossibleDestination.push_back(_enemyTilePos - MAPTILEX);
						}
						//좌상
						if (_map->GetTileX(_enemyTilePos) > 0 && _map->GetTileY(_enemyTilePos) > 0 && _map->GetTile(_enemyTilePos - MAPTILEX - 1).canPass)
							vPossibleDestination.push_back(_enemyTilePos - MAPTILEX - 1);
						//우상
						if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 && _map->GetTileY(_enemyTilePos) > 0 && _map->GetTile(_enemyTilePos - MAPTILEX + 1).canPass)
							vPossibleDestination.push_back(_enemyTilePos - MAPTILEX + 1);
						//좌하
						if (_map->GetTileX(_enemyTilePos) > 0 && _map->GetTileY(_enemyTilePos) < MAPTILEY - 1 && _map->GetTile(_enemyTilePos + MAPTILEX - 1).canPass)
							vPossibleDestination.push_back(_enemyTilePos + MAPTILEX - 1);
						//우하
						if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 && _map->GetTileY(_enemyTilePos) < MAPTILEY - 1 && _map->GetTile(_enemyTilePos + MAPTILEX + 1).canPass)
							vPossibleDestination.push_back(_enemyTilePos + MAPTILEX + 1);

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
					vector<int> vPossibleDestination;
					//동
					if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 &&
						_map->GetTile(_enemyTilePos + 1).canPass) {
						vPossibleDestination.push_back(_enemyTilePos + 1);
					}
					//서
					if (_map->GetTileX(_enemyTilePos) > 0 &&
						_map->GetTile(_enemyTilePos - 1).canPass) {
						vPossibleDestination.push_back(_enemyTilePos - 1);
					}
					//남
					if (_map->GetTileY(_enemyTilePos) < MAPTILEY - 1 &&
						_map->GetTile(_enemyTilePos + MAPTILEX).canPass) {
						vPossibleDestination.push_back(_enemyTilePos + MAPTILEX);
					}
					//북
					if (_map->GetTileY(_enemyTilePos) > 0 &&
						_map->GetTile(_enemyTilePos - MAPTILEX).canPass) {
						vPossibleDestination.push_back(_enemyTilePos - MAPTILEX);
					}
					//좌상
					if (_map->GetTileX(_enemyTilePos) > 0 && _map->GetTileY(_enemyTilePos) > 0 && _map->GetTile(_enemyTilePos - MAPTILEX - 1).canPass)
						vPossibleDestination.push_back(_enemyTilePos - MAPTILEX - 1);
					//우상
					if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1  && _map->GetTileY(_enemyTilePos) > 0 && _map->GetTile(_enemyTilePos - MAPTILEX + 1).canPass)
						vPossibleDestination.push_back(_enemyTilePos - MAPTILEX + 1);
					//좌하
					if (_map->GetTileX(_enemyTilePos) > 0 && _map->GetTileY(_enemyTilePos) < MAPTILEY - 1 && _map->GetTile(_enemyTilePos + MAPTILEX - 1).canPass)
						vPossibleDestination.push_back(_enemyTilePos + MAPTILEX - 1);
					//우하
					if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 && _map->GetTileY(_enemyTilePos) < MAPTILEY - 1 && _map->GetTile(_enemyTilePos + MAPTILEX + 1).canPass)
						vPossibleDestination.push_back(_enemyTilePos + MAPTILEX + 1);
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

void cow::cowAttackAttempt()
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
		if (cowHitWaitCount > 200)	//돌진까지 준비시간 약 1~2초 사이.
		{
			if (cowHitCount == 17) {
				if (abs(_target->rc.left - rc.left) <= cowDashRange && abs(_target->rc.top - rc.top) <= cowDashRange)
				{
					_target->hurt(Atk);
				}
			}
			_state2 = DASH;
		}
		else {
			cowHitWaitCount++;
			_state2 = IDLE3;
		}
	}
	
	
}

void cow::cowDash()
{
	if (_state2 == DASH)
	{
		if (_target->rc.left < rc.left)
		{
			OffsetRect(&rc, -MOVESPEED*4, 0);
		}
		else if (_target->rc.left > rc.left)
		{
			OffsetRect(&rc, MOVESPEED * 4, 0);
		}
		if (_target->rc.top > rc.top)
		{
			OffsetRect(&rc, 0, MOVESPEED * 4);
		}
		else if (_target->rc.top < rc.top)
		{
			OffsetRect(&rc, 0, -MOVESPEED * 4);
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

void cow::checkCowTile()
{
	POINT ptCowPos = { GetCenterX(), GetCenterY() };

	// 플레이어 좌표 기준 상하좌우 타일중에 
	// 지금 밟고 있는 타일로 좌표 변경
	if (PtInRect(&_map->GetTileRc(_cowTilePos), ptCowPos))
		_cowTilePos = _cowTilePos;


	//소 좌표 기준 상하좌우 타일 충돌 체크
	else if (PtInRect(&_map->GetTileRc(_cowTilePos + 1), ptCowPos))
		_cowTilePos += 1;
	else if (PtInRect(&_map->GetTileRc(_cowTilePos - 1), ptCowPos))
		_cowTilePos -= 1;
	else if (PtInRect(&_map->GetTileRc(_cowTilePos + MAPTILEX), ptCowPos))
		_cowTilePos += MAPTILEX;
	else if (PtInRect(&_map->GetTileRc(_cowTilePos - MAPTILEX), ptCowPos))
		_cowTilePos -= MAPTILEX;

	// 소 좌표 기준 대각선 타일 충돌 체크
	else if (PtInRect(&_map->GetTileRc(_cowTilePos - MAPTILEX + 1), ptCowPos))
		_cowTilePos += MAPTILEX + 1;
	else if (PtInRect(&_map->GetTileRc(_cowTilePos - MAPTILEX - 1), ptCowPos))
		_cowTilePos -= MAPTILEX - 1;
	else if (PtInRect(&_map->GetTileRc(_cowTilePos + MAPTILEX + 1), ptCowPos))
		_cowTilePos += MAPTILEX + 1;
	else if (PtInRect(&_map->GetTileRc(_cowTilePos + MAPTILEX - 1), ptCowPos))
		_cowTilePos -= MAPTILEX - 1;

	// 소의 좌표가 어긋날 경우 다시 받아옴.
	else
		_cowTilePos = FindCowTilePos();


}

int cow::FindCowTilePos()
{
	vector<tile> _vTiles = _map->GetTiles();
	POINT _ptCowPos = { GetCenterX(),  GetCenterY() };

	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, _ptCowPos)) {
				return (i*MAPTILEY + j);
			}
		}
	}

	
}
