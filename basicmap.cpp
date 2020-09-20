#include "stdafx.h"
#include "basicmap.h"

HRESULT basicmap::init()
{
	//IMAGEMANAGER->addImage("watertile", "Images/이미지/타일/img_tile_water.bmp", TILESIZE, TILESIZE);
	//IMAGEMANAGER->addFrameImage("plaintile", "Images/이미지/타일/img_tile_plain.bmp", TILESIZE, TILESIZE, 4, 1);
	//IMAGEMANAGER->addFrameImage("plainedge", "Images/이미지/타일/img_tile_plainEdge.bmp", TILESIZE, TILESIZE, 4, 2, true, RGB(255, 0, 255));
	watertile = new image;
	watertile->init("Images/이미지/타일/img_tile_water.bmp", TILESIZE, TILESIZE, 1, 1);
	plaintile = new image;
	plaintile->init("Images/이미지/타일/img_tile_plain.bmp", 224, 56, 4, 1);
	plainedge = new image;
	plainedge->init("Images/이미지/타일/img_tile_plainEdge.bmp", 224, 112, 4, 2, true, RGB(255, 0, 255));

	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			_tiles[i][j].rc = RectMake(0 + j * TILESIZE, 0 + i * TILESIZE, TILESIZE, TILESIZE);
			_tiles[i][j].level = TERRAIN;
			_tiles[i][j].terrain = watertile;
		}
	}
	return S_OK;
}

void basicmap::release()
{
	watertile->release();
	SAFE_DELETE(watertile);
	plaintile->release();
	SAFE_DELETE(plaintile);
	plainedge->release();
	SAFE_DELETE(plainedge);
}

void basicmap::update()
{

	if (INPUT->GetKey(VK_LBUTTON)) {
		for (int i = 0; i < TILEY; i++) {
			bool stop = false;
			for (int j = 0; j < TILEX; j++) {
				_tiles[i][j].rc;
				RECT temp;
				if (PtInRect(&_tiles[i][j].rc, _ptMouse)) {
					_tiles[i][j].terrain = plaintile;
					stop = true;
					break;
				}
			}
			if (stop) break;
		}
	}
	if (INPUT->GetKey(VK_RBUTTON)) {
		for (int i = 0; i < TILEY; i++) {
			bool stop = false;
			for (int j = 0; j < TILEX; j++) {
				_tiles[i][j].rc;
				RECT temp;
				if (PtInRect(&_tiles[i][j].rc, _ptMouse)) {
					_tiles[i][j].terrain = watertile;
					stop = true;
					break;
				}
			}
			if (stop) break;
		}
	}
}

void basicmap::render()
{
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			if (_tiles[i][j].terrain == watertile) {
				_tiles[i][j].terrain->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 0, 0);
			}
			else {
				_tiles[i][j].terrain->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 0, 0);
				//서북 꼭짓점
				if (i - 1 >= 0 && j - 1 >= 0 && _tiles[i - 1][j - 1].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 0, 1);
				}
				//동북 꼭짓점
				if (i - 1 >= 0 && j + 1 < TILEX && _tiles[i - 1][j + 1].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 1, 1);
				}
				//동남 꼭짓점
				if (i + 1 < TILEY && j + 1 < TILEX && _tiles[i + 1][j + 1].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 2, 1);
				}
				//서남 꼭짓점
				if (i + 1 < TILEY && j - 1 >= 0 && _tiles[i + 1][j - 1].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 3, 1);
				}
				//서
				if (j-1 >= 0 && _tiles[i][j-1].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 0, 0);
				}
				//동
				if (j + 1 < TILEX && _tiles[i][j + 1].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 1, 0);
				}
				//북
				if (i - 1 >= 0 && _tiles[i-1][j].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 2, 0);
				}
				//남
				if (i + 1 < TILEY && _tiles[i + 1][j].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top, 3, 0);
				}

			}
		}
	}
}
