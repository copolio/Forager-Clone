#pragma once
#include "singletonBase.h"

#define FLOATINGTEXT_MAX 10

class TextManager : public singletonBase<TextManager>
{
private:
	struct tagFloatingText {
		int x, y;
		string str;
		int count;
		COLORREF color;
		COLORREF bgColor;
		bool isAppear;
	};

private:
	int _count;
	int _timer;
	int _size;
	tagFloatingText _floatingTexts[FLOATINGTEXT_MAX];

public:
	void init();
	void release();
	void update();
	void render(HDC hdc);

	// str : 출력할 텍스트  (디폴트 Test)
	// ptPos : 출력할 위치	(디폴트 10, 10)
	// size : 폰트 사이즈	(디폴드 15)
	// align = 0 : 왼쪽 정렬, 1 : 가운데 정렬, 2 : 오른쪽 정렬 (디폴트 0)
	// color : 폰트 색상 (디폴트 흰색)
	// isBoundary : 텍스트 그림자 활성화 (선명도 강조) (디폴트 꺼짐)
	// colorBoundary : 그림자 색상 (디폴트 검은색)
	void ShowText(HDC hdc, string str = "Test", POINT ptPos = { 10, 10 }, int size = 15, int align = 0, COLORREF color = RGB(255, 255, 255), bool isBoundary = false, COLORREF colorBoundary = RGB(0, 0, 0), int interval = 3);

	void ShowFloatingText(string str, POINT ptPos, COLORREF color = RGB(255, 255, 255), COLORREF bgColor = RGB(0,0,0));
};

