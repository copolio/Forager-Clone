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

	_isAppearNotify = false;
	_notifyCount = 0;
	_notifyMaxCount = 500;
	_notifyPtPos = { 0, 0 };
	_notifyMessage = "temp";
	_notifySize = 0;
}

void TextManager::release()
{
	RemoveFontResource("Fonts/BMJUA.ttf");
}

void TextManager::update()
{
	updateFloatingText();
	updateItemText();
	updateNotify();
}

void TextManager::render(HDC hdc)
{
	renderFloatingText(hdc);
	renderItemText(hdc);
	renderNotify(hdc);
}

void TextManager::updateFloatingText()
{
	// 하나라도 있으면
	if (_count > 0) {

		// 플로팅 텍스트 위로 천천히 상승
		for (int i = 0; i < FLOATINGTEXT_MAX; i++) {

			if (_floatingTexts[i].isAppear) {


				if (_floatingTexts[i].count < 30)
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

void TextManager::updateItemText()
{
	if (_vFieldItemText.size() > 0) {
		for (auto iter = _vFieldItemText.begin(); iter != _vFieldItemText.end();) {
			if (iter->count++ > 350) {
				iter = _vFieldItemText.erase(iter);
			}
			else
				++iter;
		}
	}
}

void TextManager::updateNotify()
{

	if (_isAppearNotify) {

		_notifyCount++;
		if (_notifyCount <= 50) {
			if (_notifyCount % 2 == 0)
				_notifyPtPos.y--;
		}
		else if (_notifyCount <= 100) {
			if (_notifyCount % 5 == 0)
				_notifyPtPos.y--;
		}
		else if (_notifyCount <= 200) {
			if (_notifyCount % 10 == 0)
				_notifyPtPos.y--;
		}
		else {
			_notifyPtPos.y = _notifyPtPos.y;
		}
		if (_notifyCount >= _notifyMaxCount)
			_isAppearNotify = false;
	}

}

void TextManager::renderFloatingText(HDC hdc)
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

void TextManager::renderItemText(HDC hdc)
{
	if (_vFieldItemText.size() > 0) {
		for (int i = 0; i < _vFieldItemText.size(); i++) {

			int x = WINSIZEX - 190;
			int y = WINSIZEY - 150 - (i * 70);

			IMAGEMANAGER->render(_vFieldItemText[i].imgKey, hdc, x, y);
			string str = _vFieldItemText[i].itemName + " x ";
			str.append(to_string(_vFieldItemText[i].num));
			TEXTMANAGER->ShowText(hdc, false, str, { x + 65, y + 14 }, 25, 0, RGB(255,255,255), true, RGB(0,0,0), 2);
		}

	}

}

void TextManager::renderNotify(HDC hdc)
{
	if (_isAppearNotify) {

		ShowText(hdc, false, _notifyMessage, _notifyPtPos, _notifySize, 1, _notifyFontColor, true, _notifyFontShadow, _notifyInterval);

	}
}



void TextManager::ShowText(HDC hdc, bool isRelative, string str, POINT ptPos, int size, int align, COLORREF color, bool isBoundary, COLORREF colorBoundary, int interval)
{

	if (align == 1)
		SetTextAlign(hdc, TA_CENTER);
	else if (align == 2)
		SetTextAlign(hdc, TA_RIGHT);
	
	HFONT hFont;
	HFONT oldFont = nullptr;
	bool isOldFont = false;
	if (isBoundary) {

		SetTextColor(hdc, colorBoundary);
		hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("배달의민족 주아"));
		oldFont = (HFONT)SelectObject(hdc, hFont);
		isOldFont = true;
		if(!isRelative)
			TextOut(hdc, ptPos.x - interval, ptPos.y + interval, str.c_str(), strlen(str.c_str()));
		else
			TextOut(hdc, CAMERA->GetRelativeX(ptPos.x - interval) * CAMERA->GetZoom(), CAMERA->GetRelativeY(ptPos.y + interval) * CAMERA->GetZoom(), str.c_str(), strlen(str.c_str()));
	}

	SetTextColor(hdc, color);
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("배달의민족 주아"));
	if(isOldFont)
		SelectObject(hdc, hFont);
	else
		oldFont = (HFONT)SelectObject(hdc, hFont);

	if(!isRelative)
		TextOut(hdc, ptPos.x, ptPos.y, str.c_str(), strlen(str.c_str()));
	else
		TextOut(hdc, CAMERA->GetRelativeX(ptPos.x) * CAMERA->GetZoom(), CAMERA->GetRelativeY(ptPos.y) * CAMERA->GetZoom(), str.c_str(), strlen(str.c_str()));


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
			_floatingTexts[i].color = color;
			_floatingTexts[i].bgColor = bgColor;
			_floatingTexts[i].count = 0;
			_count++;
			return;
		}

	}

	//cout << "FloatingText 배열 개수 부족!!" << endl;
		

}

void TextManager::ShowNotifyText(string str, POINT ptPos, int size, COLORREF color, COLORREF bgColor, int interval)
{
	_notifyCount = 0;
	_isAppearNotify = true;
	_notifyMessage = str;
	_notifyPtPos = ptPos;
	_notifySize = size;
	_notifyFontColor = color;
	_notifyFontShadow = bgColor;
	_notifyInterval = interval;
}

void TextManager::AppearItemText(string pImgKey)
{
	for (int i = 0; i < _vFieldItemText.size(); i++) {
		if (_vFieldItemText[i].imgKey == pImgKey) {
			_vFieldItemText[i].num++;
			_vFieldItemText[i].count = 0;
			return;
		}
	}
	tagFloatingFieldItem itemText;
	itemText.count = 0;
	itemText.num = 1;
	itemText.imgKey = pImgKey;
	itemText.itemName = DATABASE->GetItem(pImgKey).itemName;
	_vFieldItemText.push_back(itemText);
}



