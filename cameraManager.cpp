#include "stdafx.h"
#include "cameraManager.h"

#define TILESIZE 56

void cameraManager::init(int posX, int posY, int targetX, int targetY, float anchorX, float anchorY, int width, int height, int minX, int minY, int maxX, int maxY)
{
	_zoomRate = 1.0f;
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

	zoomOffset = 0;
	zoomCount = 0;
	_currentZoomForce = 0;
	_isZoomForce = false;
	_zoomRecoilBack = false;
	movelimit = true;
}



void cameraManager::targetFollow(int targetX, int targetY)
{
	if (INPUT->GetKeyDown('5')) {
		_zoomRate += 0.1f;

	}
	else if (INPUT->GetKeyDown('6')) {
		_zoomRate -= 0.1f;
	}
	else if (INPUT->GetKeyDown('9')) {
		movelimit = false;
		forceZoomIn(-0.5f, -0.01f, false);
	}
	else if (INPUT->GetKeyDown('0')) {
		movelimit = true;
		forceZoomIn(0, 0.01f, false);
	}


	if (movelimit) {
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


		int t_left = _targetX - (_targetX * _zoomRate);
		int t_top = _targetY - (_targetY * _zoomRate);
		int t_width = _cameraWidth + (_cameraWidth * _zoomRate);
		int t_height = _cameraHeight + (_cameraHeight * _zoomRate);

		_rcCamBound = RectMakeCenter(t_left, t_top, t_width, t_height);
	}
	
}

void cameraManager::camFocusCursor(POINT ptMouse)
{
	

	if (!movelimit) {

		int speed = 5;

		// 우측으로 이동
		if (ptMouse.x >= (WINSIZEX / 2) + 150) {
			_posX += speed;
		}
		// 좌측으로
		else if (ptMouse.x <= (WINSIZEX / 2) - 150) {
			_posX -= speed;
		}		
		// 아래로 이동
		if (ptMouse.y >= (WINSIZEY / 2) + 150) {
			_posY += speed;
		}
		// 위로
		else if (ptMouse.y <= (WINSIZEY / 2) - 150) {
			_posY -= speed;
		}


		
	}
	else {
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

		lerpValueX = (distanceX < 50) ? .1f :
			(distanceX < 100) ? .15f :
			(distanceX < 250) ? .2f : .25f;
		lerpValueY = (distanceY < 50) ? .1f :
			(distanceY < 150) ? .15f :
			(distanceY < 250) ? .2f : .25f;

		lerpX = (float)(distanceX)* lerpValueX;
		lerpY = (float)(distanceY)* lerpValueY;


		_posX += (IsRight) ? lerpX : -lerpX;
		_posY += (IsDown) ? lerpY : -lerpY;

		_rcCamRealBound = RectMakeCenter(_posX + ptMouse.x, _posY + ptMouse.y, _cameraWidth, _cameraHeight);
	}
}

void cameraManager::forceZoomIn(float force, float zoomSpeed, bool isAutoOriginBack)
{
	_isAutoBack = isAutoOriginBack;
	_isZoomForce = true;
	_zoomRecoilBack = false;
	zoomCount = 0;
	_zoomForce = force;
	_zoomSpeed = zoomSpeed;
}

int cameraManager::GetRelativeX(int posX)
{
	zoomOffset = TILESIZE * (GetZoom() * 10) - TILESIZE * 10;
	return posX - _posX - ceilf(zoomOffset);
}

int cameraManager::GetRelativeY(int posY)
{
	zoomOffset = TILESIZE * (GetZoom() * 10) - TILESIZE * 10;
	return posY - _posY - ceilf(zoomOffset);
}

RECT cameraManager::GetRelativeRc(RECT rc)
{
	if (GetZoom() == 1) {
		return { long(rc.left*GetZoom()),
			long(rc.top*GetZoom()),
			long(rc.right*GetZoom()),
			long(rc.bottom*GetZoom()) };
	}
	else {
		return { long(GetRelativeX(rc.left) * GetZoom()),
				long(GetRelativeY(rc.top)* GetZoom()),
				long(GetRelativeX(rc.right)* GetZoom()),
				long(GetRelativeY(rc.bottom)* GetZoom()) };
	}


	
	
}

//RECT cameraManager::GetRelativeRc(RECT rc)
//{
//	return { GetRelativeX(rc.left),
//		GetRelativeY(rc.top*GetZoom()),
//		GetRelativeX(rc.right*GetZoom()),
//		GetRelativeY(rc.bottom*GetZoom()) };
//}



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

void cameraManager::update()
{
	if (_isZoomForce) {
		if (zoomCount++ % 1 == 0) {
			if (!_zoomRecoilBack) {
				_currentZoomForce += _zoomSpeed;

				if (_zoomForce >= 0) {
					if (_currentZoomForce >= _zoomForce) {
						if (_isAutoBack)
							_zoomRecoilBack = true;
						else
							_isZoomForce = false;
					}
				}
				else {
					if (_currentZoomForce <= _zoomForce) {
						if (_isAutoBack)
							_zoomRecoilBack = true;
						else
							_isZoomForce = false;
					}
				}

			}
			else {
				_currentZoomForce -= _zoomSpeed;
				if (_currentZoomForce <= 0) {
					_currentZoomForce = 0;
					_isZoomForce = false;
					_zoomRecoilBack = false;
				}
			}


		}

	}
}

