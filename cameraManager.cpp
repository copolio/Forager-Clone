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

	zoomOffset = 0;
	zoomCount = 0;
	_currentZoomForce = 0;
	_isZoomForce = false;
	_zoomRecoilBack = false;
	movelimit = true;
}



void cameraManager::targetFollow(int targetX, int targetY)
{
	if (movelimit) {
		_targetX = targetX;
		_targetY = targetY;

		// 카메라 중심은 (타겟 위치 - 화면 사이즈 고정비)
		_posX = _targetX - (WINSIZEX * _anchorX);
		_posY = _targetY - (WINSIZEY * _anchorY);

		int t_width = _cameraWidth / GetZoom();
		int t_height = _cameraHeight / GetZoom();

		//_rcCamBound = RectMakeCenter(_posX, _posY, t_width, t_height);
	}
	
}

void cameraManager::camFocusCursor(POINT ptMouse)
{
	

	if (!movelimit) {

		int speed = 8;

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

		int x = _posX + (WINSIZEX * _anchorX) + 360;
		int y = _posY + (WINSIZEY * _anchorY) + 80;
		int t_width = _cameraWidth / GetZoom();
		int t_height = _cameraHeight / GetZoom();

		_rcCamRealBound = RectMakeCenter(x, y, t_width, t_height);
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

		lerpValueX = (distanceX < 50) ? .125f :
			(distanceX < 100) ? .15f :
			(distanceX < 250) ? .175f : .2f;
		lerpValueY = (distanceY < 50) ? .125f :
			(distanceY < 150) ? .15f :
			(distanceY < 250) ? .175f : .2f;

		lerpX = (float)(distanceX)* lerpValueX;
		lerpY = (float)(distanceY)* lerpValueY;


		_posX += (IsRight) ? lerpX : -lerpX;
		_posY += (IsDown) ? lerpY : -lerpY;
		int x = _posX + (WINSIZEX * _anchorX);
		int y = _posY + (WINSIZEY * _anchorY);
		int t_width = (_cameraWidth + 56) / GetZoom();
		int t_height = (_cameraHeight + 56) / GetZoom();

		_rcCamRealBound = RectMakeCenter(x, y, t_width, t_height);
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
	if (CAMERA->movelimit) {
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


POINT cameraManager::GetMouseRelativePos(POINT ptMouse)
{

	ptMouse.x += _posX;
	ptMouse.y += _posY;

	return ptMouse;
}

// 테스트용
void cameraManager::render(HDC hdc)
{
	RECT t_rc = _rcCamRealBound;
	t_rc.left = GetRelativeX(t_rc.left)  * GetZoom();
	t_rc.right = GetRelativeX(t_rc.right) * GetZoom();
	t_rc.top = GetRelativeY(t_rc.top) * GetZoom();
	t_rc.bottom = GetRelativeY(t_rc.bottom) * GetZoom();

	//FrameRect(hdc, t_rc, RGB(255, 0, 0));
}

void cameraManager::update()
{
	if (_isZoomForce) {
		if (zoomCount++ % 1 == 0) {
			if (!_zoomRecoilBack) {
				_currentZoomForce += _zoomSpeed;

				if (_zoomForce >= 0) {
					if (_currentZoomForce >= _zoomForce) {
						_currentZoomForce = _zoomForce;
						if (_isAutoBack)
							_zoomRecoilBack = true;
						else
							_isZoomForce = false;
					}
				}
				else {
					if (_currentZoomForce <= _zoomForce) {
						_currentZoomForce = _zoomForce;
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

