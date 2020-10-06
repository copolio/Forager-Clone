#include "stdafx.h"
#include "earth.h"

HRESULT earth::init()
{
	//지형
	watertile = IMAGEMANAGER->addImage("watertile", "Images/이미지/타일/img_tile_water.bmp", TILESIZE, TILESIZE);
	plaintile = IMAGEMANAGER->addFrameImage("plaintile", "Images/이미지/타일/img_tile_plain.bmp", 224, 56, 4, 1);
	plainedge = IMAGEMANAGER->addFrameImage("plainedge", "Images/이미지/타일/img_tile_plainEdge.bmp", 224, 112, 4, 2, true, RGB(255, 0, 255));
	wave = IMAGEMANAGER->addImage("wave", "Images/이미지/타일/img_tile_wave.bmp", 56, 56);
	underwater = IMAGEMANAGER->addImage("underwater", "Images/이미지/타일/img_tile_bottomGround.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleBG", "Images/이미지/img_Background.bmp", 2000, 1300, true, RGB(255, 0, 255));
	
	_count = wavetick = _frameCount = 0;

	//월드맵 초기화
	this->mapSetup();

	return S_OK;
}

void earth::release()
{
}


void earth::update()
{
	_count++;
	if (_count % RESGENTIME == 0) {
		this->setRandomObject();
	}
	if (_count % 10 == 0) {
		wavetick++;
	}
	if (wavetick > 10) {
		wavetick = 0;
	}

	//유닛매니저 업데이트
	UNITMANAGER->update();
}

void earth::render(HDC hdc)
{
	//<텍스쳐 매니저 구현 전까지 사용>
	// 물배경 렌더
	IMAGEMANAGER->findImage("TitleBG")->render(hdc, -500, -400);

	//<텍스쳐 매니저 구현 전까지 사용>
	//지형 렌더
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			RECT temp;

			// 카메라 범위만 렌더
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &_vTile[i*MAPTILEY + j].rc)) continue;

			// 지형 렌더
			if (_vTile[i*MAPTILEY + j].terrKey != "watertile") {
				IMAGEMANAGER->frameRender(_vTile[i*MAPTILEY + j].terrKey, hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), _vTile[i*MAPTILEY + j].terrainFrameX, _vTile[i*MAPTILEY + j].terrainFrameY);
				//서북 꼭짓점
				if (j - 1 >= 0 && _vTile[(i)*MAPTILEY + (j - 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 0, 1);
				}
				//동북 꼭짓점
				if (i - 1 >= 0 && j + 1 < MAPTILEX && _vTile[(i - 1)*MAPTILEY + (j + 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 1, 1);
				}
				//동남 꼭짓점
				if (i + 1 < MAPTILEY && j + 1 < MAPTILEX && _vTile[(i + 1)*MAPTILEY + (j + 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 2, 1);
				}
				//서남 꼭짓점
				if (i + 1 < MAPTILEY && j - 1 >= 0 && _vTile[(i + 1)*MAPTILEY + (j - 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 3, 1);
				}
				//서
				if (j - 1 >= 0 && _vTile[i*MAPTILEY + (j - 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 0, 0);
				}
				//동
				if (j + 1 < MAPTILEX && _vTile[i*MAPTILEY + (j + 1)].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 1, 0);
				}
				//북
				if (i - 1 >= 0 && _vTile[(i - 1)*MAPTILEY + j].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 2, 0);
				}
				//남
				if (i + 1 < MAPTILEY && _vTile[(i + 1)*MAPTILEY + j].terrKey == "watertile") {
					plainedge->frameRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.top), 3, 0);
					underwater->render(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.bottom));
					wave->alphaRender(hdc, CAMERA->GetRelativeX(_vTile[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTile[i*MAPTILEY + j].rc.bottom + 20 + wavetick), 100);

				}
			}
		}
	}
	
	// 유닛 렌더
	UNITMANAGER->render(hdc);
}

void earth::mapSetup()
{
	//바다초기화
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			tile _tile;
			_tile.rc = RectMake(WINSIZEX / 2 - (MAPTILEX*TILESIZE / 2.0f) + j * TILESIZE, WINSIZEY / 2 - (MAPTILEY*TILESIZE / 2.0f) + i * TILESIZE, TILESIZE, TILESIZE);
			_tile.tag = TAG::TERRAIN;
			_tile.layer = LAYER::TERRAIN;
			_tile.terrKey = "watertile";
			_tile.terrainFrameX = 0;
			_tile.terrainFrameY = 0;
			_tile.hasUnit = false;
			_vTile.push_back(_tile);
		}
	}
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			_vTile[(3 * MAPTILEY*TILEY + i * MAPTILEY) + 3 * TILEX + j].terrKey = "plaintile";
			_vTile[(3 * MAPTILEY*TILEY + i * MAPTILEY) + 3 * TILEX + j].terrainFrameX = RANDOM->range(4);
		}
	}
}

void earth::setRandomObject()
{
	if (this->getResRatio() > RESRATIOLIMIT) return;
	while (true) {
		int i = RANDOM->range(TILEY*MAPY);
		int j = RANDOM->range(MAPTILEX);

		//현재 플레이어가 서있는 타일은 스킵
		if (i + j == _player->GetPlayerTilePos()) continue;

		if (!_vTile[i*MAPTILEY + j].hasUnit &&
			_vTile[i*MAPTILEY + j].terrKey == "plaintile") {
			_vTile[i*MAPTILEY + j].hasUnit = true;

			// 유닛 매니저에 추가
			UNITMANAGER->AddUnits(&_vTile[i*MAPTILEY + j]);
			break;
		}	
	}
}

float earth::getResRatio()
{
	float nResTile = 0;
	float nPlainTile = 0;
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (_vTile[i*MAPTILEY + j].terrKey == "plaintile" &&
				!_vTile[i*MAPTILEY + j].hasUnit) {
				nPlainTile++;
			}
			else if (_vTile[i*MAPTILEY + j].terrKey == "plaintile" &&
				_vTile[i*MAPTILEY + j].hasUnit) {
				nResTile++;
			}
		}
	}
	return nResTile / float(nPlainTile);
}
