#include "stdafx.h"
#include "purchase_land.h"
#include "earth.h"

HRESULT purchase_land::init()
{
	balance = new int;
	
	IMAGEMANAGER->addImage("greenisland", "Images/이미지/타일/img_tile_green.bmp", 56*6, 56 * 6);
	IMAGEMANAGER->addImage("redisland", "Images/이미지/타일/img_tile_red.bmp", 56 * 6, 56 * 6);

	return S_OK;
}

void purchase_land::release()
{
	SAFE_DELETE(balance);
	balance = NULL;
}

void purchase_land::update()
{
	_tileIndex = _map->tileColMouseTargetIndex();
	_targetIslandrc = _map->GetIslandRc(_map->GetIslandX(_tileIndex), _map->GetIslandY(_tileIndex));
	_islandIndex = _map->GetIslandY(_tileIndex)*MAPTILEX + _map->GetIslandX(_tileIndex);
	

	if (INPUT->GetKey(VK_LBUTTON)) {
		if (!_map->HasIsland(_map->GetIslandX(_tileIndex), _map->GetIslandY(_tileIndex)) &&
			ITEMMANAGER->getMoney() >= LANDPRICE) {
			SOUNDMANAGER->play("건설성공");
			_map->setIsland(_map->GetIslandX(_tileIndex), _map->GetIslandY(_tileIndex));
			*balance = ITEMMANAGER->getMoney() - LANDPRICE;
			ITEMMANAGER->setMoney(balance);
		}
	}
}

void purchase_land::render(HDC hdc)
{
	IMAGEMANAGER->render("inventory_Kinds", hdc, WINSIZEX / 2 - 240, 15);
	IMAGEMANAGER->render("Q", hdc, 320, 70);
	IMAGEMANAGER->render("E", hdc, 890, 70);
	IMAGEMANAGER->render("purchase_land", hdc, 672, 30);

	if (CAMERA->GetZoom() <= 0.5f) renderBuildableTile(hdc);
}

void purchase_land::renderBuildableTile(HDC hdc)
{
	int tarIsCenterX = CAMERA->GetRelativeRc(_targetIslandrc).left + (CAMERA->GetRelativeRc(_targetIslandrc).right - CAMERA->GetRelativeRc(_targetIslandrc).left) / 2 - 20;
	int tarIsCenterY = CAMERA->GetRelativeRc(_targetIslandrc).top + (CAMERA->GetRelativeRc(_targetIslandrc).bottom - CAMERA->GetRelativeRc(_targetIslandrc).top) / 2;
	if (_map->HasIsland(_map->GetIslandX(_tileIndex), _map->GetIslandY(_tileIndex))) {
		IMAGEMANAGER->alphaRender("redisland", hdc, CAMERA->GetRelativeRc(_targetIslandrc).left, CAMERA->GetRelativeRc(_targetIslandrc).top, 150);
	}
	else if (ITEMMANAGER->getMoney() < LANDPRICE) {
		IMAGEMANAGER->alphaRender("redisland", hdc, CAMERA->GetRelativeRc(_targetIslandrc).left, CAMERA->GetRelativeRc(_targetIslandrc).top, 150);
		IMAGEMANAGER->render("img_game_money_icon", hdc, tarIsCenterX, tarIsCenterY - 40);
		TEXTMANAGER->ShowText(hdc, false, "가격: 10골드", { tarIsCenterX + 10 , tarIsCenterY + 30 }, 35, 1);
	}
	else {
		IMAGEMANAGER->alphaRender("greenisland", hdc, (CAMERA->GetRelativeRc(_targetIslandrc).left), (CAMERA->GetRelativeRc(_targetIslandrc).top), 150);;
		IMAGEMANAGER->render("img_game_money_icon", hdc, tarIsCenterX, tarIsCenterY - 40);
		TEXTMANAGER->ShowText(hdc, false, "가격: 10골드", { tarIsCenterX+10 , tarIsCenterY + 30 }, 35, 1);
	}
}
