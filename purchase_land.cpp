#include "stdafx.h"
#include "purchase_land.h"
#include "earth.h"

HRESULT purchase_land::init()
{
	_targetBox = new targetingBox;
	_targetBox->init();
	balance = new int;
	
	IMAGEMANAGER->addImage("greenisland", "Images/이미지/타일/img_tile_green.bmp", 56*6, 56 * 6);
	IMAGEMANAGER->addImage("redisland", "Images/이미지/타일/img_tile_red.bmp", 56 * 6, 56 * 6);

	return S_OK;
}

void purchase_land::release()
{
}

void purchase_land::update()
{
	_targetBox->update();
	_tileIndex = _map->tileColMouseTargetIndex();
	_targetIslandrc = _map->GetIslandRc(_map->GetIslandX(_tileIndex), _map->GetIslandY(_tileIndex));

	_targetBox->SetTarget(CAMERA->GetRelativeRc(_targetIslandrc), 4, _tileIndex, 4, false);

	if (INPUT->GetKey(VK_LBUTTON)) {
		if (!_map->HasIsland(_map->GetIslandX(_tileIndex), _map->GetIslandY(_tileIndex)) &&
			ITEMMANAGER->getMoney() >= LANDPRICE) {
			_map->setIsland(_map->GetIslandX(_tileIndex), _map->GetIslandY(_tileIndex));
			*balance = ITEMMANAGER->getMoney() - LANDPRICE;
			ITEMMANAGER->setMoney(balance);
		}
	}
}

void purchase_land::render(HDC hdc)
{
	_targetBox->render(hdc);

	IMAGEMANAGER->render("inventory_Kinds", hdc, WINSIZEX / 2 - 240, 15);
	IMAGEMANAGER->render("Q", hdc, 320, 70);
	IMAGEMANAGER->render("E", hdc, 890, 70);
	IMAGEMANAGER->render("purchase_land", hdc, 672, 30);

	if (CAMERA->GetZoom() <= 0.5f) renderBuildableTile(hdc);
}

void purchase_land::renderBuildableTile(HDC hdc)
{
	if (_map->HasIsland(_map->GetIslandX(_tileIndex), _map->GetIslandY(_tileIndex))) {
		IMAGEMANAGER->alphaRender("redisland", hdc, (CAMERA->GetRelativeRc(_targetIslandrc).left), (CAMERA->GetRelativeRc(_targetIslandrc).top), 150);
	}
	else {
		IMAGEMANAGER->alphaRender("greenisland", hdc, (CAMERA->GetRelativeRc(_targetIslandrc).left), (CAMERA->GetRelativeRc(_targetIslandrc).top), 150);
	}
}
