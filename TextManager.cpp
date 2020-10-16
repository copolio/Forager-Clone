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
	updateFloatingText();
	updateItemText();
}

void TextManager::render(HDC hdc)
{
	renderFloatingText(hdc);
	renderItemText(hdc);
}

void TextManager::updateFloatingText()
{
	// ÇÏ³ª¶óµµ ÀÖÀ¸¸é
	if (_count > 0) {

		// ÇÃ·ÎÆÃ ÅØ½ºÆ® À§·Î ÃµÃµÈ÷ »ó½Â
		for (int i = 0; i < FLOATINGTEXT_MAX; i++) {

			if (_floatingTexts[i].isAppear) {


				if (_floatingTexts[i].count < 30)
					_floatingTexts[i].y -= 1;

				else if (_floatingTexts[i].count < 60 && _floatingTexts[i].count % 2 == 0)
					_floatingTexts[i].y -= 1;
				else if (_floatingTexts[i].count < 90 && _floatingTexts[i].count % 3 == 0)
					_floatingTexts[i].y -= 1;


				_floatingTexts[i].count++;

				// Å¸ÀÌ¸Ó µÇ¸é ¼Ò¸ê
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

void TextManager::renderFloatingText(HDC hdc)
{
	// ÇÏ³ª¶óµµ ÀÖÀ» °æ¿ì,
	if (_count > 0) {

		SetTextAlign(hdc, TA_CENTER);
		HFONT hFont;
		HFONT oldFont;
		hFont = CreateFont(_size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("¹è´ÞÀÇ¹ÎÁ· ÁÖ¾Æ"));
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



void TextManager::ShowText(HDC hdc, bool isRelative, string str, POINT ptPos, int size, int align, COLORREF color, bool isBoundary, COLORREF colorBoundary, int interval)
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
		hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("¹è´ÞÀÇ¹ÎÁ· ÁÖ¾Æ"));
		oldFont = (HFONT)SelectObject(hdc, hFont);
		isOldFont = true;
		if(!isRelative)
			TextOut(hdc, ptPos.x - interval, ptPos.y + interval, str.c_str(), strlen(str.c_str()));
		else
			TextOut(hdc, CAMERA->GetRelativeX(ptPos.x - interval), CAMERA->GetRelativeY(ptPos.y + interval), str.c_str(), strlen(str.c_str()));
	}

	SetTextColor(hdc, color);
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("¹è´ÞÀÇ¹ÎÁ· ÁÖ¾Æ"));
	if(isOldFont)
		SelectObject(hdc, hFont);
	else
		oldFont = (HFONT)SelectObject(hdc, hFont);

	if(!isRelative)
		TextOut(hdc, ptPos.x, ptPos.y, str.c_str(), strlen(str.c_str()));
	else
		TextOut(hdc, CAMERA->GetRelativeX(ptPos.x), CAMERA->GetRelativeY(ptPos.y), str.c_str(), strlen(str.c_str()));


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

	//cout << "FloatingText ¹è¿­ °³¼ö ºÎÁ·!!" << endl;
		

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
	if (pImgKey == "berryDrop") itemText.itemName = "¿­¸Å";
	else if (pImgKey == "treeDrop") itemText.itemName = "³ª¹«";
	else if (pImgKey == "rockDrop") itemText.itemName = "µ¹¸ÍÀÌ";
	else if (pImgKey == "pooDrop") itemText.itemName = "¶Ë";
	else if (pImgKey == "letherDrop") itemText.itemName = "°¡Á×";
	else if (pImgKey == "milkDrop") itemText.itemName = "¿ìÀ¯";
	else if (pImgKey == "skullHeadDrop") itemText.itemName = "ÇØ°ñ";
	else if (pImgKey == "slot_Bow") itemText.itemName = "È°";
	else if (pImgKey == "sword") itemText.itemName = "Ä®";
	else if (pImgKey == "Iron_ore") itemText.itemName = "Ã¶±¤¼®";
	else if (pImgKey == "coal") itemText.itemName = "¼®Åº";
	else if (pImgKey == "±«Ã¶") itemText.itemName = "±«Ã¶";
	else if (pImgKey == "±Ý±«") itemText.itemName = "±Ý±«";
	else if (pImgKey == "±Ý±¤¼®") itemText.itemName = "±Ý±¤¼®";
	else if (pImgKey == "brick") itemText.itemName = "º®µ¹";
	else if (pImgKey == "img_game_money_icon") itemText.itemName = "ÄÚÀÎ";
	else itemText.itemName = pImgKey;
	_vFieldItemText.push_back(itemText);
}



