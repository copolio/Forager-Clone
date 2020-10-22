#include "stdafx.h"
#include "muBoss.h"

HRESULT muBoss::init()
{
	_state5 = MIDLE;

	return S_OK;
}

void muBoss::update()
{
	muuAnimation();
}

void muBoss::render(HDC hdc)
{
	switch (_state5)
	{
	case MIDLE:
		IMAGEMANAGER->frameRender("muBoss", hdc, CAMERA->GetRelativeX(rc.left + 60),
			CAMERA->GetRelativeY(rc.top - 20),  objFrameX, objFrameY, CAMERA->GetZoom());

		break;
	case CRY:
		IMAGEMANAGER->frameRender("muBossCry", hdc, CAMERA->GetRelativeX(rc.left + 60),
			CAMERA->GetRelativeY(rc.top - 20), objFrameX, objFrameY, CAMERA->GetZoom());
		break;

	}
	
}

void muBoss::muuAnimation()
{
	//objFrameY = (isLeft) ? 1 : 0;
	//objFrameX = _index;
	//if (_count++ % 10 == 0)
	//{
	//	if (_index++ > 9)
	//		_index = 0;
	//}
	switch (_state5)
	{
	case MIDLE:
		objFrameX = _index;
		objFrameY = 0;
		if (_count++ % 10 == 0)
		{
			if (_index++ > 9)
				_index = 0;
		}
		break;
	case CRY:
		objFrameX = _index;
		objFrameY = 0;
		if (_count++ % 15 == 0)
		{
			if (_index++ > 6)
			{
				_index = 0;
				_state5 = MIDLE;
			}
				
		}
		break;
	}
	
}

void muBoss::hurt(int damage)
{
	_index = 0;
	_count = 0;
	_state5 = CRY;
	currentHp -= damage;

	if(currentHp <= 0){
		UNITMANAGER->AddTreasure("treasureBox", "slot_Bow", { GetCenterX(), GetCenterY()});
	}
}
	
