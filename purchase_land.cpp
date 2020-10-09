#include "stdafx.h"
#include "purchase_land.h"
#include "earth.h"

HRESULT purchase_land::init()
{
	_targetBox = new targetingBox;
	_targetBox->init();
	return S_OK;
}

void purchase_land::release()
{
}

void purchase_land::update()
{
	_targetBox->update();
	int _tileIndex = _map->tileMouseTargetIndex();
	//_targetBox->SetTarget(CAMERA->GetRelativeRc(_map->tileMouseTarget()->rc), 1, _map->tileMouseTargetIndex(), 4, false);
	_targetBox->SetTarget(CAMERA->GetRelativeRc(
		_map->GetIslandRc(
			_map->GetIslandX(_tileIndex),
			_map->GetIslandY(_tileIndex))),
		1, _map->tileMouseTargetIndex(), 4, false);
	cout << _tileIndex << " " << _map->GetIslandX(_tileIndex) << ", " << _map->GetIslandY(_tileIndex) << endl;

}

void purchase_land::render(HDC hdc)
{
	_targetBox->render(hdc);

	IMAGEMANAGER->render("inventory_Kinds", hdc, WINSIZEX / 2 - 240, 15);
	IMAGEMANAGER->render("Q", hdc, 320, 70);
	IMAGEMANAGER->render("E", hdc, 890, 70);
	IMAGEMANAGER->render("purchase_land", hdc, 672, 30);
}
