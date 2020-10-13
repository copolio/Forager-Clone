#include "stdafx.h"
#include "wraith.h"

HRESULT wraith::init()
{
	wraithHitCount = 0;
	wraithWaitCount = 0;
	searchCount = 0;
	wraithAttackRange = 200;

	Atk = 30;
	tryAttack = false;

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
	wraithLookDirection();
}

void wraith::render(HDC hdc)
{
	switch (_state3)
	{
	case FLY:
		IMAGEMANAGER->frameRender("wraithIdle", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case SHOOT:
		IMAGEMANAGER->frameRender("wraithAttack", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;

	}
}

void wraith::wraithMove()
{
	if (!checkDestination)
	{
		searchCount++;
		if (searchCount > 200)
		{
			for (int i = 0; i < 5; i++)
			{
				int random = RANDOM->range(0, 3);
				switch (random)
				{
				case 0: _vDestTileIndex.push_back(_enemyTilePos + 1);
					break;
				case 1: _vDestTileIndex.push_back(_enemyTilePos - 1);
					break;
				case 2: _vDestTileIndex.push_back(_enemyTilePos + MAPTILEX);
					break;
				case 3: _vDestTileIndex.push_back(_enemyTilePos - MAPTILEX);
					break;
				}
				_enemyTilePos = _vDestTileIndex[i];
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
	if (!tryAttack)
	{
		if (abs(_target->rc.left - rc.left) <= wraithAttackRange && abs(_target->rc.top - rc.top) <= wraithAttackRange)
		{
			tryAttack = true;
		}
		else
			_state3 = FLY;
	}
	else
	{
		wraithWaitCount++;
		if (wraithWaitCount > 120)
		{
			//if (wraithHitCount == 23) {
			//	if (abs(_target->rc.left - rc.left) <= wraithAttackRange && abs(_target->rc.top - rc.top) <= wraithAttackRange)
			//		_target->hurt(Atk);
			//}
			_state3 = SHOOT;
		}
		else
			_state3 =SHOOT;
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
		if (wraithHitCount++ % 10 == 0)
		{
			if (_attackIndex++ > 5)
			{
				wraithHitCount = 1;
				_attackIndex = 0;
				wraithWaitCount = 0;
				tryAttack = false;
			}
		}
		break;
	}
}

void wraith::wraithLookDirection()
{
	if ( _state3 == SHOOT || _state3 == FLY)
	{
		if (rc.right > _target->rc.right && rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}

}
