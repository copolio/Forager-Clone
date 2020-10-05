#include "stdafx.h"
#include "purchase_land.h"

HRESULT purchase_land::init()
{
	return S_OK;
}

void purchase_land::release()
{
}

void purchase_land::update()
{
}

void purchase_land::render(HDC hdc)
{
	IMAGEMANAGER->render("inventory_Kinds", hdc, WINSIZEX / 2 - 240, 15);
	IMAGEMANAGER->render("Q", hdc, 320, 70);
	IMAGEMANAGER->render("E", hdc, 890, 70);
	IMAGEMANAGER->render("purchase_land", hdc, 672, 30);


}
