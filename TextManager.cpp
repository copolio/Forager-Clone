#include "stdafx.h"
#include "TextManager.h"

void TextManager::init()
{
	AddFontResource("Fonts/BMJUA.ttf");
	_timer = 120;
	_size = 35;
	_count = 0;
	ZeroMemory(_floatingTexts, sizeof(tagFloatingText) * FLOATINGTEXT_MAX);
	for (int i = 0; i < FLOATINGTEXT_MAX; i++)
		_floatingTexts[i].str = "a";
}

void TextManager::release()
{
	RemoveFontResource("Fonts/BMJUA.ttf");
}

void TextManager::update()
{
	// 하나라도 있으면
	if (_count > 0) {

		// 플로팅 텍스트 위로 천천히 상승
		for (int i = 0; i < FLOATINGTEXT_MAX; i++) {

			if (_floatingTexts[i].isAppear) {


				if(_floatingTexts[i].count < 30)
					_floatingTexts[i].y -= 1;

				else if (_floatingTexts[i].count < 60 && _floatingTexts[i].count % 2 == 0)
					_floatingTexts[i].y -= 1;
				else if (_floatingTexts[i].count < 90 && _floatingTexts[i].count % 3 == 0)
					_floatingTexts[i].y -= 1;


				_floatingTexts[i].count++;

				// 타이머 되면 소멸
				if (_floatingTexts[i].count >= _timer) {
					_floatingTexts[i].isAppear = false;
					_count--;
				}
			}
		}
	}
}

void TextManager::render(HDC hdc)
{
	// 하나라도 있을 경우,
	if (_count > 0) {

		SetTextAlign(hdc, TA_CENTER);
		HFONT hFont;
		HFONT oldFont;
		hFont = CreateFont(_size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("배달의민족 주아"));
		oldFont = (HFONT)SelectObject(hdc, hFont);

		for (int i = 0; i < FLOATINGTEXT_MAX; i++) {

			if (_floatingTexts[i].isAppear) {

				SetTextColor(hdc, _floatingTexts[i].bgColor);
				TextOut(hdc, CAMERA->GetRelativeX(_floatingTexts[i].x - 3), CAMERA->GetRelativeY(_floatingTexts[i].y + 3), _floatingTexts[i].str.c_str(), strlen(_floatingTexts[i].str.c_str()));
				SetTextColor(hdc, _floatingTexts[i].color);
				TextOut(hdc, CAMERA->GetRelativeX(_floatingTexts[i].x), CAMERA->GetRelativeY(_floatingTexts[i].y), _floatingTexts[i].str.c_str(), strlen(_floatingTexts[i].str.c_str()));
			}
		}

		SetTextAlign(hdc, TA_LEFT);
		DeleteObject((HFONT)SelectObject(hdc, oldFont));
	}
	
}



void TextManager::ShowText(HDC hdc, string str, POINT ptPos, int size, int align, COLORREF color, bool isBoundary, COLORREF colorBoundary)
{

	if (align == 1)
		SetTextAlign(hdc, TA_CENTER);
	else if (align == 2)
		SetTextAlign(hdc, TA_RIGHT);
	
	HFONT hFont;
	HFONT oldFont;
	bool isOldFont = false;
	if (isBoundary) {

		SetTextColor(hdc, colorBoundary);
		hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("배달의민족 주아"));
		oldFont = (HFONT)SelectObject(hdc, hFont);
		isOldFont = true;
		TextOut(hdc, ptPos.x - 3, ptPos.y + 3, str.c_str(), strlen(str.c_str()));
	}

	SetTextColor(hdc, color);
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("배달의민족 주아"));
	if(isOldFont)
		SelectObject(hdc, hFont);
	else
		oldFont = (HFONT)SelectObject(hdc, hFont);

	TextOut(hdc, ptPos.x, ptPos.y, str.c_str(), strlen(str.c_str()));



	SetTextAlign(hdc, TA_LEFT);
	DeleteObject((HFONT)SelectObject(hdc, oldFont));
}

void TextManager::ShowFloatingText(string str, POINT ptPos, COLORREF color, COLORREF bgColor)
{
	for (int i = 0; i < FLOATINGTEXT_MAX; i++) {

		if (!_floatingTexts[i].isAppear) {
			_floatingTexts[i].isAppear = true;
			_floatingTexts[i].x = ptPos.x;
			_floatingTexts[i].y = ptPos.y;
			_floatingTexts[i].str = str;
			cout << _floatingTexts[i].str << endl;
			_floatingTexts[i].color = color;
			_floatingTexts[i].bgColor = bgColor;
			_floatingTexts[i].count = 0;
			_count++;
			return;
		}

	}

	cout << "FloatingText 배열 개수 부족!!" << endl;
		

}



