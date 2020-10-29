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

void muBoss::hurt(int damage, bool onlyEffect)
{
	SOUNDMANAGER->play("무맞을때소리");
	_index = 0;
	_count = 0;
	_state5 = CRY;

	vector<string> t_vStr;
	int t_random = RANDOM->range(0, 3);
	if (t_random == 0)
		t_vStr.push_back("그, 그래도 난 널 믿어...!");
	else if (t_random == 1)
		t_vStr.push_back("갑자기 왜 그러는 거야...!");
	else
		t_vStr.push_back("내, 내가 뭘 잘못한 거니...?!");

	DIALOGUE->ShowDialogue(t_vStr, &rc, 10);
	if (onlyEffect)
		return;

	
	unit::hurt(damage);

}

void muBoss::dead()
{
	UNITMANAGER->AddTreasure("treasureBox", "slot_Bow", { GetCenterX(), GetCenterY() });
	tileIndex = _map->GetTileIndex({ GetCenterX(), GetCenterY() });
	_map->SetConquer(_map->GetIslandX(this->tileIndex), _map->GetIslandY(this->tileIndex));
}
	
