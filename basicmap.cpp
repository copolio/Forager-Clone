#include "stdafx.h"
#include "basicmap.h"

HRESULT basicmap::init()
{
	watertile = IMAGEMANAGER->addImage("watertile", "Images/이미지/타일/img_tile_water.bmp", TILESIZE, TILESIZE);
	plaintile = IMAGEMANAGER->addFrameImage("plaintile", "Images/이미지/타일/img_tile_plain.bmp", 224, 56, 4, 1);
	plainedge = IMAGEMANAGER->addFrameImage("plainedge", "Images/이미지/타일/img_tile_plainEdge.bmp", 224, 112, 4, 2, true, RGB(255, 0, 255));
	wave = IMAGEMANAGER->addImage("wave", "Images/이미지/타일/img_tile_wave.bmp", 56, 56);
	underwater = IMAGEMANAGER->addImage("underwater", "Images/이미지/타일/img_tile_bottomGround.bmp", 56, 56, true, RGB(255, 0, 255));
	_rcCam = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_rcPlayer = RectMakeCenter(WINSIZEX/2, WINSIZEY/2, 10, 10);

	_count = wavetick = 0;

	berry = IMAGEMANAGER->addFrameImage("berry", "Images/이미지/오브젝트/resource/img_object_berry.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	rock = IMAGEMANAGER->addFrameImage("rock", "Images/이미지/오브젝트/resource/img_object_rock.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	tree = IMAGEMANAGER->addFrameImage("tree", "Images/이미지/오브젝트/resource/img_object_tree.bmp", 280, 168, 5, 1, true, RGB(255, 0, 255));

	this->mapSetup();

	return S_OK;
}

void basicmap::release()
{
}

void basicmap::update()
{
	//타일 변경
	this->setTile();
	// 카메라 이동
	this->cameraMove();

	_count++;
	if (_count % 10 == 0) {
		wavetick++;
	}
	
	if (_count % 100 == 0) {
		this->setRandomTile();
	}
	if (wavetick > 10) {
		wavetick = 0;
	}
}

void basicmap::render()
{
	//바다 렌더
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			RECT temp;
			if (!IntersectRect(&temp, &_rcCam, &_vTiles[i*MAPTILEY + j].rc)) continue;
			if (_vTiles[i*MAPTILEY + j].terrain == watertile) {
				_vTiles[i*MAPTILEY + j].terrain->render(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top);
			}
		}
	}
	//지형 렌더
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			RECT temp;
			if (!IntersectRect(&temp, &_rcCam, &_vTiles[i*MAPTILEY + j].rc)) continue;
			if (_vTiles[i*MAPTILEY + j].terrain != watertile) {
				_vTiles[i*MAPTILEY + j].terrain->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, _vTiles[i*MAPTILEY + j].terrainFrameX, _vTiles[i*MAPTILEY + j].terrainFrameY);
				//textOut(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, to_string(_vTiles[i*MAPTILEY + j].rc.left).c_str());
				//서북 꼭짓점
				if (j - 1 >= 0 && _vTiles[(i)*MAPTILEY + (j - 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, 0, 1);
				}
				//동북 꼭짓점
				if (i - 1 >= 0 && j + 1 < MAPTILEX && _vTiles[(i - 1)*MAPTILEY +(j + 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, 1, 1);
				}
				//동남 꼭짓점
				if (i + 1 < MAPTILEY && j + 1 < MAPTILEX && _vTiles[(i + 1)*MAPTILEY +(j + 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, 2, 1);
				}
				//서남 꼭짓점
				if (i + 1 < MAPTILEY && j - 1 >= 0 && _vTiles[(i + 1)*MAPTILEY +(j - 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, 3, 1);
				}
				//서
				if (j-1 >= 0 && _vTiles[i*MAPTILEY +(j - 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, 0, 0);
				}
				//동
				if (j + 1 < MAPTILEX && _vTiles[i*MAPTILEY +(j + 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, 1, 0);
				}
				//북
				if (i - 1 >= 0 && _vTiles[(i - 1)*MAPTILEY +j].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, 2, 0);
				}
				//남
				if (i + 1 < MAPTILEY && _vTiles[(i + 1)*MAPTILEY +j].terrain == watertile) {
					plainedge->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, 3, 0);
					underwater->render(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.bottom);
					wave->alphaRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.bottom+20+wavetick, 100);

				}

			}
		}
	}
	//오브젝트 렌더
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			RECT temp;
			if (!IntersectRect(&temp, &_rcCam, &_vTiles[i*MAPTILEY + j].rc)) continue;
			if (_vTiles[i*MAPTILEY + j].objHp > 0) {
				_vTiles[i*MAPTILEY + j].object->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.bottom- _vTiles[i*MAPTILEY + j].object->getFrameHeight(), _vTiles[i*MAPTILEY + j].objFrameX, _vTiles[i*MAPTILEY + j].objFrameY);
				//Rectangle(getMemDC(), _vTiles[i*MAPTILEY + j].rc);
			}
		}
	}

	int playerCenterX = _rcPlayer.left + (_rcPlayer.right - _rcPlayer.left) / 2;
	int playerCenterY = _rcPlayer.top + (_rcPlayer.bottom - _rcPlayer.top) / 2;
	textOut(getMemDC(), 0, 0, (to_string(CAMRANGE)+" "+ to_string(getDistance(playerCenterX - CAMSPEED, playerCenterY, WINSIZEX / 2, WINSIZEY / 2))).c_str());
	Rectangle(getMemDC(), _rcPlayer);
}

void basicmap::mapSetup()
{
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			tile _tile;
			_tile.rc = RectMake(WINSIZEX / 2 - (MAPTILEX*TILESIZE / 2.0f) + j * TILESIZE, WINSIZEY / 2 - (MAPTILEY*TILESIZE / 2.0f) + i * TILESIZE, TILESIZE, TILESIZE);
			_tile.level = TERRAIN;
			_tile.terrain = watertile;
			_tile.terrainFrameX = 0;
			_tile.terrainFrameY = 0;
			_tile.terrainHp = _tile.objHp = 0;
			_tile.object = tree;
			_tile.objHp = 0;
			_tile.objFrameX = 0;
			_tile.objFrameY = 0;

			_vTiles.push_back(_tile);
		}
	}
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			_vTiles[(3 * MAPTILEY*TILEY + i * MAPTILEY) + 3 * TILEX + j].terrain = plaintile;
			_vTiles[(3 * MAPTILEY*TILEY + i * MAPTILEY) + 3 * TILEX + j].terrainFrameX = RANDOM->range(4);
			_vTiles[(3 * MAPTILEY*TILEY + i * MAPTILEY) + 3 * TILEX + j].terrainHp = PLAINHP;
		}
	}
}

void basicmap::setTile()
{
	//지형 체력 0 -> 바다 타일로 바꿈
	for (int i = 0; i < TILEY*MAPY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (_vTiles[i*MAPTILEY + j].terrainHp <= 0) {
				_vTiles[i*MAPTILEY + j].terrain = watertile;
				_vTiles[i*MAPTILEY + j].terrainFrameX = 0;
				_vTiles[i*MAPTILEY + j].terrainHp = 0;
			}
		}
	}
	if (INPUT->GetKey(VK_LBUTTON)) {
		for (int i = 0; i < TILEY*MAPY; i++) {
			bool stop = false;
			for (int j = 0; j < MAPTILEX; j++) {
				if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, _ptMouse)) {
					if (_vTiles[i*MAPTILEY + j].objHp > 0) {
						_vTiles[i*MAPTILEY + j].objHp -= 1;
					}
					else {
						_vTiles[i*MAPTILEY + j].terrainHp -= 1;
					}					
					stop = true;
					break;
				}
			}
			if (stop) break;
		}
	}
	if (INPUT->GetKey(VK_RBUTTON)) {
		for (int i = 0; i < MAPTILEY; i++) {
			bool stop = false;
			for (int j = 0; j < MAPTILEX; j++) {
				if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, _ptMouse)) {
					_vTiles[i*MAPTILEY + j].terrain = plaintile;
					_vTiles[i*MAPTILEY + j].terrainFrameX = RANDOM->range(4);
					_vTiles[i*MAPTILEY + j].terrainHp = PLAINHP;
					stop = true;
					break;
				}
			}
			if (stop) break;
		}
	}
}

void basicmap::cameraMove()
{
	int playerCenterX = _rcPlayer.left + (_rcPlayer.right - _rcPlayer.left) / 2;
	int playerCenterY = _rcPlayer.top + (_rcPlayer.bottom - _rcPlayer.top) / 2;
	if (_ptMouse.x > (WINSIZEX / 2) + 200 &&
		_vTiles.back().rc.right > WINSIZEX &&
		getDistance(playerCenterX - CAMSPEED, playerCenterY, WINSIZEX/2, WINSIZEY/2) < CAMRANGE) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.left -= CAMSPEED;
				_vTiles[i*MAPTILEY + j].rc.right -= CAMSPEED;
			}
		}
		_rcPlayer.left -= CAMSPEED;
		_rcPlayer.right -= CAMSPEED;
	}
	if (_ptMouse.x < (WINSIZEX / 2) - 200 &&
		_vTiles[0].rc.left < 0 &&
		getDistance(playerCenterX + CAMSPEED, playerCenterY, WINSIZEX / 2, WINSIZEY / 2) < CAMRANGE) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.left += CAMSPEED;
				_vTiles[i*MAPTILEY + j].rc.right += CAMSPEED;
			}
		}
		_rcPlayer.left += CAMSPEED;
		_rcPlayer.right += CAMSPEED;
	}
	if (_ptMouse.y > WINSIZEY / 2 + 200 &&
		_vTiles.back().rc.bottom > WINSIZEY &&
		getDistance(playerCenterX, playerCenterY - CAMSPEED, WINSIZEX / 2, WINSIZEY / 2) < CAMRANGE) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.top -= CAMSPEED;
				_vTiles[i*MAPTILEY + j].rc.bottom -= CAMSPEED;
			}
		}
		_rcPlayer.top -= CAMSPEED;
		_rcPlayer.bottom -= CAMSPEED;
	}
	if (_ptMouse.y < WINSIZEY / 2 - 200 &&
		_vTiles[0].rc.top < 0 &&
		getDistance(playerCenterX, playerCenterY + CAMSPEED, WINSIZEX / 2, WINSIZEY / 2) < CAMRANGE) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.top += CAMSPEED;
				_vTiles[i*MAPTILEY + j].rc.bottom += CAMSPEED;
			}
		}
		_rcPlayer.top += CAMSPEED;
		_rcPlayer.bottom += CAMSPEED;
	}
}

void basicmap::setRandomTile()
{
	for (int i = 0; i < TILEY*MAPY; i++) {
		bool stop = false;
		for (int j = 0; j < MAPTILEX; j++) {
			if (_vTiles[i*MAPTILEY + j].terrain == plaintile &&
				_vTiles[i*MAPTILEY + j].objHp == 0) {
				switch (RANDOM->range(NUMOBJECTS)) {
				case 0:
					_vTiles[i*MAPTILEY + j].object = tree;
					break;

				case 1:
					_vTiles[i*MAPTILEY + j].object = berry;
					break;

				case 2:
					_vTiles[i*MAPTILEY + j].object = rock;
					break;
				}
				_vTiles[i*MAPTILEY + j].objFrameX = 0;
				_vTiles[i*MAPTILEY + j].objFrameY = 0;
				_vTiles[i*MAPTILEY + j].objHp = 50;
				stop = true;
				break;
			}
		}
		if (stop) break;
	}
}
