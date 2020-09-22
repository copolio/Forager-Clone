#pragma once

class targetingBox
{
private:
	RECT _rcTargetBox;		// 타겟팅된 상대의 RC
	int _minSize;			// 줌 아웃 최소 사이즈
	int _maxSize;			// 줌 인 최대 사이즈
	int _currentSize;		// 현재 줌 사이즈
	int _count;				// 줌 무빙 인터벌
	int _currentCount;		// 줌 무빙 인터벌 카운트
	int _zoomSpeed;			// 줌 스피드

	bool _isTargetting;		// 타겟팅 중인지 체크
	bool _isZoomIn;			// 줌인 상태인지 줌 아웃 상태인지 구분
	bool _isCursorOn;		// 커서가 올라온 상태인지 체크

public:

	HRESULT init();
	void update();
	void render(HDC hdc);

	void SetTarget(RECT rcTarget);
	void CursorOut();
	void RemoveTarget();



};
