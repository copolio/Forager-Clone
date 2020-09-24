#include "stdafx.h"
#include "cameraManager.h"

void cameraManager::init(int posX, int posY, int targetX, int targetY, float anchorX, float anchorY, int width, int height, int minX, int minY, int maxX, int maxY)
{
	_posX = posX;
	_posY = posY;
	_targetX = targetX;
	_targetY = targetY;
	_anchorX = anchorX;
	_anchorY = anchorY;
	_cameraWidth = width; 
	_cameraHeight = height;
	_minX = minX;
	_minY = minY;
	_maxX = maxX;
	_maxY = maxY;
	_rcCamRealBound = RectMakeCenter(_posX, _posY, _cameraWidth, _cameraHeight);
	_rcCamBound = RectMakeCenter(_posX, _posY, _cameraWidth, _cameraHeight);
}

void cameraManager::targetFollow(int targetX, int targetY)
{
	_targetX = targetX;
	_targetY = targetY;

	// 카메라 중심은 (타겟 위치 - 화면 사이즈 고정비)
	int centerX = _targetX - (WINSIZEX * _anchorX);
	int centerY = _targetY - (WINSIZEY * _anchorY);
	
	// 카메라 중심이 왼쪽끝 오른쪽끝을 넘지 않게 예외처리
	if (centerX - (_cameraWidth * 0.5f) <= _minX)
		_posX = _minX;
	else if (centerX + (_cameraWidth * 0.5f) >= _maxX)
		_posX = _maxX - (_cameraWidth * 0.5f);
	else
		_posX = centerX;


	// 카메라 중심이 위 아래 끝을 넘지 않게 예외처리.
	if (_targetY <= _minY)
		_posY = _minY;
	else if (_targetY + (_cameraHeight * 0.5f) >= _maxY)
		_posY = _maxY - (_cameraHeight * 0.5f);
	else
		_posY = centerY;

	_rcCamBound = RectMakeCenter(_targetX, _targetY, _cameraWidth, _cameraHeight);
}

void cameraManager::camFocusCursor(POINT ptMouse)
{
	int limitX = 250;
	int limitY = 250;
	float lerpX = .0f;
	float lerpY = .0f;
	float lerpValueX = .0f;
	float lerpValueY = .0f;

	int relativeMouseX = (_posX + ptMouse.x);
	int relativeMouseY = (_posY + ptMouse.y);


	int distanceX = _targetX - relativeMouseX;
	int distanceY = _targetY - relativeMouseY;

	bool IsRight = (distanceX <= 0) ? true : false;
	bool IsDown = (distanceY <= 0) ? true : false;

	distanceX = abs(distanceX);
	distanceY = abs(distanceY);

	lerpValueX = (distanceX < 50) ?  .1f :
				 (distanceX < 100) ? .15f :
				 (distanceX < 250) ? .2f : .25f;
	lerpValueY = (distanceY < 50) ?  .1f :
	 			 (distanceY < 150) ? .15f :
	 			 (distanceY < 250) ? .2f : .25f;

	lerpX = (float)(distanceX) * lerpValueX;
	lerpY = (float)(distanceY) * lerpValueY;

	cout << lerpX << endl;

	_posX += (IsRight)? lerpX : -lerpX;
	_posY += (IsDown) ? lerpY : -lerpY;

	_rcCamRealBound = RectMakeCenter(_posX + ptMouse.x, _posY + ptMouse.y, _cameraWidth, _cameraHeight);
}

int cameraManager::GetRelativeX(int posX)
{
	return  posX - _posX;
}

int cameraManager::GetRelativeY(int posY)
{
	return posY - _posY;
}

POINT cameraManager::GetMouseRelativePos(POINT ptMouse)
{
	ptMouse.x += _posX;
	ptMouse.y += _posY;

	return ptMouse;
}


// 테스트용
void cameraManager::render(HDC hdc)
{
	FrameRect(hdc, _rcCamBound, RGB(255, 0, 0));
}

