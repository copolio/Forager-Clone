#include "stdafx.h"
#include "progressBar.h"

void progressBar::init(const char * frontImg, const char * backImg)
{
	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	_width = 0;
}


void progressBar::render(HDC hdc)
{
	if (CAMERA->movelimit) {
		//렌더링 되는 순서에 의해서 렌더가 되니까 피통부터 렌더 시킨다
		_progressBarBack->render(hdc, _x, _y);
		//앞에 보여지는 체력바 이미지
		_progressBarFront->render(hdc, _x + 4, _y + 5, 0, 0, _width, 10);
	}
}

//체력바 게이지 세팅하기
void progressBar::setGauge(float maxHp, float currentHp, int x, int y)
{
	_width = (currentHp / maxHp) * (float)_progressBarBack->getWidth();
	_x = x + 3;
	_y = y;
	
}
