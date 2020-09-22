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

	

	IMAGEMANAGER->addImage("하트모양체력", "Images/이미지/GUI/하트모양체력.bmp", 34, 30,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("하트모양체력(뒤)", "Images/이미지/GUI/하트모양체력(뒤).bmp", 34, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("스테미나", "Images/이미지/GUI/img_UI_StaminaGaugeBar.bmp", 63, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테미나(뒤)", "Images/이미지/GUI/img_UI_StaminaGaugeBoard.bmp", 74, 26, true, RGB(255, 0, 255));

	_staminaImgSizeMax = IMAGEMANAGER->findImage("스테미나")->getWidth();
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

	
	

}

void ForagerStatManager::setGauge(float maxHp, float currentHp)
{
	
}
