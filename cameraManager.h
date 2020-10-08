#include"singletonBase.h"

#pragma once
class cameraManager : public singletonBase<cameraManager>
{

private:
	int _posX, _posY;				// 월드 상의 카메라의 위치
	int _targetX, _targetY;			// 월드 상의 타겟 위치 (플레이어)
	float _anchorX, _anchorY;		// 카메라 중심 앵커 (현재 화면 중심)
	int _cameraWidth, _cameraHeight;// 카메라 가로 세로 사이즈 (렌더 범위)
	int _minX, _minY, _maxX, _maxY;	// 카메라 이동 제한 범위
	RECT _rcCamBound;				// 플레이어 중심 렌더용 렉트
	RECT _rcCamRealBound;			// 카메라 이동 렉트

	float _zoomRate;				// 줌 상태
	int zoomCount;
	float _zoomForce;
	float _currentZoomForce;
	float _zoomSpeed;
	bool _isZoomForce;
	bool _zoomRecoilBack;
public:
	// 초기화
	void init(int posX, int posY, int targetX, int targetY, float anchorX, float anchorY, int width, int height, int minX, int minY, int maxX, int maxY);

	// 타겟 추적
	void targetFollow(int targetX, int targetY);
	// 마우스 커서에 초점
	void camFocusCursor(POINT ptMouse);

	void forceZoomIn(float force, float zoomSpeed);

	// 테스트용 빨간색 프레임 렌더 (테스트 끝나면 지워도 됨)
	void render(HDC hdc);
	void update();

	// 상대좌표
	int GetRelativeX(int posX);
	int GetRelativeY(int posY);
	float GetZoom() { return _zoomRate + _currentZoomForce; };
	RECT GetZoooRC(RECT t_rc);

	// 마우스 상대좌표 (마우스는 절대 좌표로 화면에 그려지고, 클릭할 때는 상대좌표를 얻어와서 타일과 충돌여부 판단)
	POINT GetMouseRelativePos(POINT ptMouse);

	// 카메라 렌더 범위 렉트 가져옴.
	RECT GetCameraRect() { return _rcCamBound; }
};

