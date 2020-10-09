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

	float _zoomRate;				// 기본 줌 값
	float zoomOffset;				// 줌 오프셋

	// 줌 애니메이션 관련
	int zoomCount;					// 줌 애니메이션 처리용
	float _zoomForce;				// 강제로 줌할 목표치.
	float _currentZoomForce;		// 현재 줌된 값
	float _zoomSpeed;				// 줌 스피드
	bool _isZoomForce;				// 강제로 줌 시키는 중인지
	bool _zoomRecoilBack;			// 줌 강제 원위치 시작
	bool _isAutoBack;				// 줌 강제 원위치를 시킬지
	
public:
	// 초기화
	void init(int posX, int posY, int targetX, int targetY, float anchorX, float anchorY, int width, int height, int minX, int minY, int maxX, int maxY);

	// 타겟 추적
	void targetFollow(int targetX, int targetY);
	// 마우스 커서에 초점
	void camFocusCursor(POINT ptMouse);

	void forceZoomIn(float force, float zoomSpeed, bool isAutoOriginBack = true);

	// 테스트용 빨간색 프레임 렌더 (테스트 끝나면 지워도 됨)
	void render(HDC hdc);
	void update();

	// 상대좌표
	int GetRelativeX(int posX);
	int GetRelativeY(int posY);
	float GetZoom() { return _zoomRate + _currentZoomForce; };
	
	// 마우스 상대좌표 (마우스는 절대 좌표로 화면에 그려지고, 클릭할 때는 상대좌표를 얻어와서 타일과 충돌여부 판단)
	POINT GetMouseRelativePos(POINT ptMouse);

	// 카메라 렌더 범위 렉트 가져옴.
	RECT GetCameraRect() { return _rcCamBound; }

	//줌 수치 설정
	void SetZoomRate(float rate) { _zoomRate = rate; };
};

