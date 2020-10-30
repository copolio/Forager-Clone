#include "stdafx.h"
#include "smallMu.h"

HRESULT smallMu::init()
{
	searchCount = 0;
	ShootCount = 0;
	isattacking = false;

	return S_OK;
}

void smallMu::update()
{
	smallMuAnimation();
	smallMuMove();
	smallMuFire();
}

void smallMu::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left - 11), CAMERA->GetRelativeY(rc.bottom + 5));
		_hpBar.render(hdc);
	}

	switch (_state6)
	{
	case IDLE6:
		IMAGEMANAGER->frameRender("smallMu", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case CRY2:
		IMAGEMANAGER->frameRender("smallMuCry", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	}
}

void smallMu::smallMuAnimation()
{
	switch (_state6)
	{
	case IDLE6:
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 7)
				_index = 0;
		}
		break;
	case CRY2:
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 6) {
				_index = 0;
				_state6 = IDLE6;
			}
		}
		break;
	}

}

void smallMu::smallMuMove()
{
	searchCount++;
	if (searchCount % 1 == 0)
	{
		if (_state6 == IDLE6)
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
						//µ¿
						if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 &&
							_map->GetTile(_enemyTilePos + 1).canPass) {
							vPossibleDestination.push_back(_enemyTilePos + 1);
						}
						//¼­
						if (_map->GetTileX(_enemyTilePos) > 0 &&
							_map->GetTile(_enemyTilePos - 1).canPass) {
							vPossibleDestination.push_back(_enemyTilePos - 1);
						}
						//³²
						if (_map->GetTileY(_enemyTilePos) < MAPTILEY - 1 &&
							_map->GetTile(_enemyTilePos + MAPTILEX).canPass) {
							vPossibleDestination.push_back(_enemyTilePos + MAPTILEX);
						}
						//ºÏ
						if (_map->GetTileX(_enemyTilePos) > 0 &&
							_map->GetTile(_enemyTilePos - MAPTILEX).canPass) {
							vPossibleDestination.push_back(_enemyTilePos - MAPTILEX);
						}
						//ÁÂ»ó
						if (_map->GetTileX(_enemyTilePos) > 0 && _map->GetTileY(_enemyTilePos) > 0 && _map->GetTile(_enemyTilePos - MAPTILEX - 1).canPass)
							vPossibleDestination.push_back(_enemyTilePos - MAPTILEX - 1);
						//¿ì»ó
						if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 && _map->GetTileY(_enemyTilePos) > 0 && _map->GetTile(_enemyTilePos - MAPTILEX + 1).canPass)
							vPossibleDestination.push_back(_enemyTilePos - MAPTILEX + 1);
						//ÁÂÇÏ
						if (_map->GetTileX(_enemyTilePos) > 0 && _map->GetTileY(_enemyTilePos) < MAPTILEY - 1 && _map->GetTile(_enemyTilePos + MAPTILEX - 1).canPass)
							vPossibleDestination.push_back(_enemyTilePos + MAPTILEX - 1);
						//¿ìÇÏ
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
					//µ¿
					if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 &&
						_map->GetTile(_enemyTilePos + 1).canPass) {
						vPossibleDestination.push_back(_enemyTilePos + 1);
					}
					//¼­
					if (_map->GetTileX(_enemyTilePos) > 0 &&
						_map->GetTile(_enemyTilePos - 1).canPass) {
						vPossibleDestination.push_back(_enemyTilePos - 1);
					}
					//³²
					if (_map->GetTileY(_enemyTilePos) < MAPTILEY - 1 &&
						_map->GetTile(_enemyTilePos + MAPTILEX).canPass) {
						vPossibleDestination.push_back(_enemyTilePos + MAPTILEX);
					}
					//ºÏ
					if (_map->GetTileY(_enemyTilePos) > 0 &&
						_map->GetTile(_enemyTilePos - MAPTILEX).canPass) {
						vPossibleDestination.push_back(_enemyTilePos - MAPTILEX);
					}
					//ÁÂ»ó
					if (_map->GetTileX(_enemyTilePos) > 0 && _map->GetTileY(_enemyTilePos) > 0 && _map->GetTile(_enemyTilePos - MAPTILEX - 1).canPass)
						vPossibleDestination.push_back(_enemyTilePos - MAPTILEX - 1);
					//¿ì»ó
					if (_map->GetTileX(_enemyTilePos) < MAPTILEX - 1 && _map->GetTileY(_enemyTilePos) > 0 && _map->GetTile(_enemyTilePos - MAPTILEX + 1).canPass)
						vPossibleDestination.push_back(_enemyTilePos - MAPTILEX + 1);
					//ÁÂÇÏ
					if (_map->GetTileX(_enemyTilePos) > 0 && _map->GetTileY(_enemyTilePos) < MAPTILEY - 1 && _map->GetTile(_enemyTilePos + MAPTILEX - 1).canPass)
						vPossibleDestination.push_back(_enemyTilePos + MAPTILEX - 1);
					//¿ìÇÏ
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
}

void smallMu::smallMuFire()
{
	if(isHit)
		_state6 = CRY2;
	
	
	ShootCount++;
	if (ShootCount >= 60)
	{
		UNITMANAGER->GetProjectileMG()->CreateProjectile("smallMuMissile", GetCenterX(), GetCenterY(), atk, shootToTarget(), 2, 30, true, false);
		ShootCount = 0;
	}
	
}
