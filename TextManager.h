#pragma once
#include "singletonBase.h"
class TextManager : public singletonBase<TextManager>
{

public:
	void init();
	void release();

	// align = 0 : 왼쪽 정렬, 1 : 가운데 정렬, 2 : 오른쪽 정렬
	void ShowText(HDC hdc, string str = "Test", POINT ptPos = { 10, 10 }, int size = 15, int align = 0, COLORREF color = RGB(255, 255, 255), bool isBoundary = false, COLORREF colorBoundary = RGB(0, 0, 0));

};

