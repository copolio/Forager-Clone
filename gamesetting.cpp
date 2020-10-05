#include "stdafx.h"
#include "gamesetting.h"

HRESULT gamesetting::init()
{
	return S_OK;
}

void gamesetting::release()
{
}

void gamesetting::update()
{
}

void gamesetting::render(HDC hdc)
{
	IMAGEMANAGER->alphaRender("inventory_background", hdc, 180);
	IMAGEMANAGER->render("inventory_Kinds", hdc, WINSIZEX / 2 - 240, 15);
	IMAGEMANAGER->render("Q", hdc, 320, 70);
	IMAGEMANAGER->render("E", hdc, 890, 70);
	IMAGEMANAGER->render("game_setting", hdc, 785, 30);
	
}
