#include "stdafx.h"
#include "TextManager.h"

void TextManager::init()
{
	AddFontResource("Fonts/BMJUA.ttf");
}

void TextManager::release()
{
	RemoveFontResource("Fonts/BMJUA.ttf");
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



