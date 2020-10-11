#include "stdafx.h"
#include "skull.h"

HRESULT skull::init()
{
	skullMoveCount = 0;
	skullIdleCount = 0;
	searchCount = 0;
	skullHitCount = 0;
	skullHitWaitCount = 0;
	skullAttackRange = 80;

	hitPlayer = false;
	tryAttack = false;

	Atk = 15;
	
	return S_OK;
}

void skull::update()
{
	skullAnimation();
	switch (_state)
	{
	case STAY:
		skullMove();
		break;
	case ATTACK:
		break;
	case APPEAR:
		break;
	case IDLE2:
		break;
	default:
		break;
	}
	
	if (_state != APPEAR ) {
		canAttackCheck();
	}
	skullLookDirection();
}

void skull::render(HDC hdc)
{
	switch (_state)
	{
	case STAY:
		IMAGEMANAGER->frameRender("skull", hdc, CAMERA->GetRelativeX(rc.left - 13 ),
			CAMERA->GetRelativeY(rc.top - 10) , objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case ATTACK:
		IMAGEMANAGER->frameRender("skullAttack", hdc, CAMERA->GetRelativeX(rc.left -53),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case APPEAR:
		IMAGEMANAGER->frameRender("skullAppear", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case IDLE2:
		IMAGEMANAGER->frameRender("skullIdle", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());

	}
}

//1Å¸ÀÏ¾¿ »óÇÏÁÂ¿ì ·£´ý¿òÁ÷ÀÌ´Âµ¥, ÃÑ 5¹ø 
void skull::skullMove()
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

void skull::canAttackCheck()
{
	if (!tryAttack)
	{
		if (abs(_target->rc.left - rc.left) <= skullAttackRange && abs(_target->rc.top - rc.top) <= skullAttackRange)
		{
			tryAttack = true;
		}
		else
			_state = STAY;
	}
	else
	{
		_state = IDLE2;
		skullHitWaitCount++;
		if (skullHitWaitCount > 120)
		{
			if (skullHitCount == 23) {
				if (abs(_target->rc.left - rc.left) <= skullAttackRange && abs(_target->rc.top - rc.top) <= skullAttackRange)
					IMAGEMANAGER->findImage("½ºÅ×¹Ì³ª")->setWidth(15);
			}
			_state = ATTACK;
		}
		
	}
}

void skull::skullAnimation()
{
	switch (_state)
	{
		//ÇØ°ñ ¶Ù´ó±è
	case STAY:
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
		if (skullHitCount++ % 10 == 0)
		{
			if (_attackIndex++ > 5)
			{
				skullHitCount = 1;
				_attackIndex = 0;
				skullHitWaitCount = 0;
				tryAttack = false;
			}
		}
		
		break;

	}
}

void skull::skullLookDirection()
{
	if (_state == STAY || _state == ATTACK || _state == IDLE2)
	{
		if (rc.right > _target->rc.right && rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}
}

