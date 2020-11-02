#include "stdafx.h"
#include "wraith.h"

HRESULT wraith::init(int p_level)
{
	_difficultyLevel = p_level;
	currentHp = maxHp =	(_difficultyLevel == 80)	? 300
					  : (_difficultyLevel == 100)	? 400
													: 500;

	wraithHitCount = 0;
	wraithWaitCount = 0;
	searchCount = 0;
	wraithShootCount = 0;
	skillFireCount = 0;
	wraithAttackRange = 280;
	_hitCount = 0;

	tryAttack = false;
	skillAngle = 0.0f;
	_state3 = FLY;
	return S_OK;
}

void wraith::update()
{
	wraithAnimation();
	switch (_state3)
	{
	case FLY:
		wraithMove();
		break;
	case SHOOT:
		break;
	}
	wraithAttack();
	wraithHitAttack();
	wraithLookDirection();

	if (searchCount % 1000 == 0) {
		int possibility = RANDOM->range(10);
		if (possibility == 0) 
			SPAWNMANAGER->SpawnPatternOne("demonIdle", 1, _difficultyLevel);
		else
			SPAWNMANAGER->SpawnPatternOne("skull", 1, _difficultyLevel);

	}	
}

void wraith::render(HDC hdc)
{
	if ((float)currentHp / maxHp <= 0.8f) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left + 30), CAMERA->GetRelativeY(rc.bottom + 15));
		_hpBar.render(hdc);
	}
	switch (_state3)
	{
	case FLY:
		IMAGEMANAGER->frameRender("wraithIdle", hdc, CAMERA->GetRelativeX(rc.left - 235),
			CAMERA->GetRelativeY(rc.top - 70), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case SHOOT:
		IMAGEMANAGER->frameRender("wraithAttack", hdc, CAMERA->GetRelativeX(rc.left - 235),
			CAMERA->GetRelativeY(rc.top - 70), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	}
	//Rectangle(hdc, { CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), CAMERA->GetRelativeX(rc.right), CAMERA->GetRelativeY(rc.bottom) });
}

void wraith::wraithMove()
{
	if (!checkDestination)
	{
		searchCount++;
		//if (searchCount > 200)
		//{
		//	for (int i = 0; i < 5; i++)
		//	{
		//		int random = RANDOM->range(0, 3);
		//		switch (random)
		//		{
		//		case 0: _vDestTileIndex.push_back(_enemyTilePos + 1);
		//			break;
		//		case 1: _vDestTileIndex.push_back(_enemyTilePos - 1);
		//			break;
		//		case 2: _vDestTileIndex.push_back(_enemyTilePos + MAPTILEX);
		//			break;
		//		case 3: _vDestTileIndex.push_back(_enemyTilePos - MAPTILEX);
		//			break;
		//		}
		//		_enemyTilePos = _vDestTileIndex[i];
		//	}
		//	checkDestination = true;
		//	_destCount = 0;
		//}
	}
	else
	{
		if (_vDestTileIndex.size() > 0)
		{
			POINT tDestination = { _map->GetTile(_vDestTileIndex[_destCount]).rc.left , _map->GetTile(_vDestTileIndex[_destCount]).rc.top };
			if (abs(rc.left - tDestination.x) > 2 || abs(rc.top - tDestination.y) > 2)
			{
				if (tDestination.x < rc.left)
				{
					OffsetRect(&rc, -2, 0);
				}
				else if (tDestination.x > rc.left)
				{
					OffsetRect(&rc, 2, 0);
				}
				if (tDestination.y > rc.top)
				{
					OffsetRect(&rc, 0, 2);
				}
				else if (tDestination.y < rc.top)
				{
					OffsetRect(&rc, 0, -2);
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

void wraith::wraithAttack()
{
	if (!tryAttack)	//플레이어가 레이스 공격 범위에 들기 전, 
	{
		if (abs(_target->rc.left - rc.left) <= wraithAttackRange && abs(_target->rc.top - rc.top) <= wraithAttackRange)
		{
			tryAttack = true;
		}
		else
			_state3 = FLY;
	}
	// 공격 가능 상태가 되면 탄환 발사. 
	else
	{
		wraithWaitCount++;
		if (wraithWaitCount > 20)
		{
			_state3 = SHOOT;
			wraithFire();
		}
	}
}

void wraith::wraithAnimation()
{
	switch (_state3)
	{
	case FLY:
		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _index;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 4)
				_index = 0;
		}
		break;
	case SHOOT:

		objFrameY = (isLeft) ? 1 : 0;
		objFrameX = _attackIndex;
		if (wraithHitCount++ % 20 == 0)
		{
			if (_attackIndex++ > 5)
			{
				wraithHitCount = 1;
				_attackIndex = 0;
				wraithWaitCount = 0;
				isHit = false;
				tryAttack = false;
			}
		}
		break;
	}
}

void wraith::wraithLookDirection()
{
	if (_state3 == SHOOT || _state3 == FLY)
	{
		if (rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}
}

void wraith::wraithFire()
{

	if (skillFireCount++ % 480 == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			float t_angle = skillAngle + (45.0f * i);
			UNITMANAGER->GetProjectileMG()->CreateProjectile("wratihMissile", rc.left, rc.top, atk, t_angle, 5, 50, true, true);
		}
		skillAngle += 20.0f;
	}
/*
	if (skillFireCount % 120 == 0)
	{
		int x = _target->rc.left - rc.left;
		int y = _target->rc.top - rc.top;
		_angle = atan2f(-y, x);
		_angle = _angle * 180 / PI;
		UNITMANAGER->GetProjectileMG()->CreateProjectile("wratihMissile", rc.left, rc.top, 10, _angle - 20, 3, 50, true, true);
		UNITMANAGER->GetProjectileMG()->CreateProjectile("wratihMissile", rc.left, rc.top, 10, _angle, 3, 50, true, true);
		UNITMANAGER->GetProjectileMG()->CreateProjectile("wratihMissile", rc.left, rc.top, 10, _angle + 20, 3, 50, true, true);

	}
*/
}

void wraith::wraithHitAttack()
{
	if (isHit) 
	{
		_hitCount++;
		if (_hitCount == 30) {
			SOUNDMANAGER->play("유령무기발사소리", 0.6f);
			UNITMANAGER->GetProjectileMG()->CreateProjectile("wratihMissile", &_target->rc, GetCenterX(), GetCenterY(), 10, shootToTarget(), 2.5f, 20, true, true, true);
		}
		if (_hitCount == 60) {
			SOUNDMANAGER->play("유령무기발사소리", 0.6f);
			UNITMANAGER->GetProjectileMG()->CreateProjectile("wratihMissile", &_target->rc, GetCenterX(), GetCenterY(), 10, shootToTarget(), 2.5f, 20, true, true, true);
		}
		if (_hitCount == 90) {
			SOUNDMANAGER->play("유령무기발사소리", 0.6f);
			UNITMANAGER->GetProjectileMG()->CreateProjectile("wratihMissile", &_target->rc, GetCenterX(), GetCenterY(), 10, shootToTarget(), 2.5f, 20, true, true, true);
		}
		if (_hitCount == 120) {
			SOUNDMANAGER->play("유령무기발사소리", 0.6f);
			UNITMANAGER->GetProjectileMG()->CreateProjectile("wratihMissile", &_target->rc, GetCenterX(), GetCenterY(), 10, shootToTarget(), 2.5f, 20, true, true, true);
		}
		if (_hitCount == 150)
		{
			SOUNDMANAGER->play("유령무기발사소리", 0.6f);
			UNITMANAGER->GetProjectileMG()->CreateProjectile("wratihMissile", &_target->rc, GetCenterX(), GetCenterY(), 10, shootToTarget(), 2.5f, 20, true, true, true);
		}
		if (_hitCount >= 600)
		{
			isHit = false;
			_hitCount = 0;
		}
	}
}


void wraith::dead()
{
	EFFECTMANAGER->ShowEffectFrame(EFFECTMANAGER->smokeEff, GetCenterPoint(), 4, true);

	UNITMANAGER->AddUnits(dropItem.itemKey, { GetCenterX(),GetCenterY() });

	tileIndex = _map->GetTileIndex({ GetCenterX(), GetCenterY() });
	_map->SetConquer(_map->GetIslandX(this->tileIndex), _map->GetIslandY(this->tileIndex));
}



