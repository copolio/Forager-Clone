#include "stdafx.h"
#include "ForagerStatManager.h"
#include "ForagerPlayer.h"

HRESULT ForagerStatManager::init()
{
	for (int i = 0; i < 3; i++)		//하트모양 체력 3개 
	{
		tagForagerHp* _hp = new tagForagerHp;

		_hp->imgName = "하트모양체력";
		_hp->ForagerHpRc = RectMake(10 + i*40,10,34,30);
		_hp->_isHp = true;
		_foragerHp.push_back(_hp);
	}

	_foragerStamina = new tagStamina;
	_foragerStamina->staminaRc = RectMake(10, 50, 74, 26);

	_foragerExp = new tagExp;
	_foragerExp->expRc = RectMakeCenter(WINSIZEX/ 2, 30, 800, 30);
	_foragerExp->expRc.right = 0;
	
	needExp[0] = 80;

	for (int i = 1; i < 65; i++) {
		needExp[i] = (float)needExp[i - 1] * 2.5f;
	}

	

	currentExp = 0;
	level = 0;

	IMAGEMANAGER->addImage("하트모양체력", "Images/이미지/GUI/하트모양체력.bmp", 34, 30,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("하트모양체력(뒤)", "Images/이미지/GUI/하트모양체력(뒤).bmp", 34, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("스테미나", "Images/이미지/GUI/img_UI_StaminaGaugeBar.bmp", 63, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테미나(뒤)", "Images/이미지/GUI/img_UI_StaminaGaugeBoard.bmp", 74, 26, true, RGB(255, 0, 255));

	//플레이어 경험치 바 이미지
	IMAGEMANAGER->addImage("expBar", "Images/이미지/GUI/img_UI_ExpGaugeBar.bmp", 792, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("expBarBack", "Images/이미지/GUI/img_UI_ExpGaugeBoard.bmp", 800, 30, true, RGB(255, 0, 255));

	_levelNum[0]=IMAGEMANAGER->addImage("0", "Images/이미지/GUI/0.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[1]=IMAGEMANAGER->addImage("1", "Images/이미지/GUI/1.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[2]=IMAGEMANAGER->addImage("2", "Images/이미지/GUI/2.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[3]=IMAGEMANAGER->addImage("3", "Images/이미지/GUI/3.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[4]=IMAGEMANAGER->addImage("4", "Images/이미지/GUI/4.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[5]=IMAGEMANAGER->addImage("5", "Images/이미지/GUI/5.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[6]=IMAGEMANAGER->addImage("6", "Images/이미지/GUI/6.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[7]=IMAGEMANAGER->addImage("7", "Images/이미지/GUI/7.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[8]=IMAGEMANAGER->addImage("8", "Images/이미지/GUI/8.bmp", 15, 19, true, RGB(255, 0, 255));
	_levelNum[9]=IMAGEMANAGER->addImage("9", "Images/이미지/GUI/9.bmp", 15, 19, true, RGB(255, 0, 255));

	_staminaImgSizeMax = IMAGEMANAGER->findImage("스테미나")->getWidth();
	_expImgSizeMax = IMAGEMANAGER->findImage("expBar")->getWidth();
	playerStaminaCount = 0;
	staminaLoss = false;
	

	return S_OK;
}

void ForagerStatManager::release()
{
}

void ForagerStatManager::update()
{
	//플레이어의 스테미나가 다 떨어지면, 다시 차오르게, 한다. 
	if (IMAGEMANAGER->findImage("스테미나")->getWidth() < 0)
	{
		IMAGEMANAGER->findImage("스테미나")->settingWidth(_staminaImgSizeMax);
		for (int i = _foragerHp.size()-1; i >= 0; i--)
		{
			if (!_foragerHp[i]->_isHp)continue;
			_foragerHp[i]->_isHp = false;
			break;
		}
	}
}

void ForagerStatManager::render()
{
	for (int i = 0; i < _foragerHp.size(); i++)
	{
		if (_foragerHp[i]->_isHp)
		{
			IMAGEMANAGER->render("하트모양체력", getMemDC(), _foragerHp[i]->ForagerHpRc.left, _foragerHp[i]->ForagerHpRc.top);
		}
		else
		{
			IMAGEMANAGER->render("하트모양체력(뒤)", getMemDC(), _foragerHp[i]->ForagerHpRc.left, _foragerHp[i]->ForagerHpRc.top);
		}
	}

	IMAGEMANAGER->render("스테미나(뒤)", getMemDC(), _foragerStamina->staminaRc.left, _foragerStamina->staminaRc.top);
	IMAGEMANAGER->render("스테미나", getMemDC(), _foragerStamina->staminaRc.left+6, _foragerStamina->staminaRc.top+4);

	IMAGEMANAGER->render("expBarBack", getMemDC(), _foragerExp->expRc.left, _foragerExp->expRc.top);

	if(level > 0)
		IMAGEMANAGER->render("expBar", getMemDC(), _foragerExp->expRc.left + 4, _foragerExp->expRc.top+3, 0, 0, 
			_expImgSizeMax * (currentExp - (float)(needExp[level - 1])) / (needExp[level] - (float)(needExp[level - 1])), 22);
	else
		IMAGEMANAGER->render("expBar", getMemDC(), _foragerExp->expRc.left+4, _foragerExp->expRc.top+3, 0, 0, 
			_expImgSizeMax * (float)(currentExp / (float)needExp[level]), 22);

	//level = (((float)currentExp / (float)needExp[level]) * 100);
	//
	//int score = level;
	//int i = 0;
	//
	//while (score != NULL)
	//{
	//	switch (score % 10)
	//	{
	//	case 0:
	//		IMAGEMANAGER->findImage("0")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top +3);
	//		break;
	//	case 1:
	//		IMAGEMANAGER->findImage("1")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top + 3);
	//		break;
	//	case 2:
	//		IMAGEMANAGER->findImage("2")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top + 3);
	//		break;
	//	case 3:
	//		IMAGEMANAGER->findImage("3")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top + 3);
	//		break;
	//	case 4:
	//		IMAGEMANAGER->findImage("4")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top + 3);
	//		break;
	//	case 5:
	//		IMAGEMANAGER->findImage("5")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top + 3);
	//		break;
	//	case 6:
	//		IMAGEMANAGER->findImage("6")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top + 3);
	//		break;
	//	case 7:
	//		IMAGEMANAGER->findImage("7")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top + 3);
	//		break;
	//	case 8:
	//		IMAGEMANAGER->findImage("8")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top + 3);
	//		break;
	//	case 9:
	//		IMAGEMANAGER->findImage("9")->render(getMemDC(), _foragerExp->expRc.left - i * 20, _foragerExp->expRc.top + 3);
	//		break;
	//	}
	//	i++;
	//	score /= 10;
	//}
	
}

void ForagerStatManager::IncreaseExp(int exp)
{
	currentExp += exp;
	if (currentExp > needExp[level])
		level++;
}
