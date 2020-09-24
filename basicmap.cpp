#include "stdafx.h"
#include "basicmap.h"


HRESULT basicmap::init()
{
	_player = new ForagerPlayer;
	_statManager = new ForagerStatManager;

	_player->init();
	_statManager->init();

	_player->setPMLink(this);
	is_item_check = true;
	//인벤토리
	_inventory = new inventory;
	_inventory->init();
	_inventory->setIMLink(this);

	//지형
	watertile = IMAGEMANAGER->addImage("watertile", "Images/이미지/타일/img_tile_water.bmp", TILESIZE, TILESIZE);
	plaintile = IMAGEMANAGER->addFrameImage("plaintile", "Images/이미지/타일/img_tile_plain.bmp", 224, 56, 4, 1);
	plainedge = IMAGEMANAGER->addFrameImage("plainedge", "Images/이미지/타일/img_tile_plainEdge.bmp", 224, 112, 4, 2, true, RGB(255, 0, 255));
	wave = IMAGEMANAGER->addImage("wave", "Images/이미지/타일/img_tile_wave.bmp", 56, 56);
	underwater = IMAGEMANAGER->addImage("underwater", "Images/이미지/타일/img_tile_bottomGround.bmp", 56, 56, true, RGB(255, 0, 255));
	_rcCam = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_rcPlayer = _player->getPlayerRect();

	_count = wavetick = 0;

	//자원
	berry = IMAGEMANAGER->addFrameImage("berry", "Images/이미지/오브젝트/resource/img_object_berry.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	rock = IMAGEMANAGER->addFrameImage("rock", "Images/이미지/오브젝트/resource/img_object_rock.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	tree = IMAGEMANAGER->addFrameImage("tree", "Images/이미지/오브젝트/resource/img_object_tree.bmp", 280, 168, 5, 1, true, RGB(255, 0, 255));

	berryDrop = IMAGEMANAGER->addImage("berryDrop", "Images/이미지/아이템/berry.bmp", 56, 56, true, RGB(255, 0, 255));
	rockDrop = IMAGEMANAGER->addImage("rockDrop", "Images/이미지/아이템/돌.bmp", 56, 56, true, RGB(255, 0, 255));
	treeDrop = IMAGEMANAGER->addImage("treeDrop", "Images/이미지/아이템/wood.bmp", 56, 56, true, RGB(255, 0, 255));

	//건물
	steelwork = IMAGEMANAGER->addFrameImage("steelwork", "Images/이미지/오브젝트/building/img_object_steelwork.bmp", 336/2, 168/2, 3, 1, true, RGB(255,0,255));

	this->mapSetup();
	

	_playerPos = getPlayerPos();

	// 카메라
	CAMERA->init(_ptPlayerPos.x, _ptPlayerPos.y, _ptPlayerPos.x, _ptPlayerPos.y, 0.5f, 0.5f, WINSIZEX + 250, WINSIZEY + 250, -2000, -2000, 2000, 2000);

	// 타겟팅 박스 설정
	_targetingBox = new targetingBox;
	_targetingBox->init();

	//_farming->setBMLink(_vTiles);



	
	

	return S_OK;
}

void basicmap::release()
{
	_player->release();
	_statManager->release();
	_inventory->release();
}

void basicmap::update()
{
	_rcPlayer = _player->getPlayerRect();
	//타일 변경
	this->setTile();
	// 카메라 이동
	/*this->cameraMove();
	this->cameraFocus();*/

	_count++;
	if (_count % 10 == 0) {
		wavetick++;
	}
	
	if (_count % RESGENTIME == 0) {
		this->setRandomTile();
	}
	if (wavetick > 10) {
		wavetick = 0;
	}

	//플레이어 업데이트
	//if (!_inventory->inventory_alreadyopen()) {
		_player->update();
	//} 인벤토리 창을 열었을경우 플레이어 움직임 멈춤
	
	CAMERA->camFocusCursor(_ptMouse); // 마우스 커서에 따른 카메라 포거싱.

	_statManager->update();
	_inventory->update();

	//마우스 타겟팅
	this->tileMouseTarget();
	_targetingBox->update();

	dropItemCollision();

}

void basicmap::render()
{
	//바다 렌더
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &_vTiles[i*MAPTILEY + j].rc)) continue;
			if (_vTiles[i*MAPTILEY + j].terrain == watertile) {
				_vTiles[i*MAPTILEY + j].terrain->render(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top));
			}
		}
	}
	//지형 렌더
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &_vTiles[i*MAPTILEY + j].rc)) continue;
			if (_vTiles[i*MAPTILEY + j].terrain != watertile) {
				_vTiles[i*MAPTILEY + j].terrain->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top), _vTiles[i*MAPTILEY + j].terrainFrameX, _vTiles[i*MAPTILEY + j].terrainFrameY);
				//textOut(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.top, to_string(_vTiles[i*MAPTILEY + j].rc.left).c_str());
				//서북 꼭짓점
				if (j - 1 >= 0 && _vTiles[(i)*MAPTILEY + (j - 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top), 0, 1);
				}
				//동북 꼭짓점
				if (i - 1 >= 0 && j + 1 < MAPTILEX && _vTiles[(i - 1)*MAPTILEY +(j + 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top), 1, 1);
				}
				//동남 꼭짓점
				if (i + 1 < MAPTILEY && j + 1 < MAPTILEX && _vTiles[(i + 1)*MAPTILEY +(j + 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top), 2, 1);
				}
				//서남 꼭짓점
				if (i + 1 < MAPTILEY && j - 1 >= 0 && _vTiles[(i + 1)*MAPTILEY +(j - 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top), 3, 1);
				}
				//서
				if (j-1 >= 0 && _vTiles[i*MAPTILEY +(j - 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top), 0, 0);
				}
				//동
				if (j + 1 < MAPTILEX && _vTiles[i*MAPTILEY +(j + 1)].terrain == watertile) {
					plainedge->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top), 1, 0);
				}
				//북
				if (i - 1 >= 0 && _vTiles[(i - 1)*MAPTILEY +j].terrain == watertile) {
					plainedge->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top), 2, 0);
				}
				//남
				if (i + 1 < MAPTILEY && _vTiles[(i + 1)*MAPTILEY +j].terrain == watertile) {
					plainedge->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.top), 3, 0);
					underwater->render(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.bottom));
					wave->alphaRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.bottom+20+wavetick), 100);

				}
			}
		}
	}
	//플레이어 위치 좌표 렉트
	//Rectangle(getMemDC(), _vTiles[_playerPos].rc);
	//플레이어
	_player->render();
	_statManager->render();

	//오브젝트 렌더
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &_vTiles[i*MAPTILEY + j].rc)) continue;
			if (_vTiles[i*MAPTILEY + j].objHp > 0) {
				//if (_vTiles[i*MAPTILEY + j].object == steelwork) {
				//	if (_vTiles[i*MAPTILEY + j + 1].object == steelwork &&
				//		_vTiles[(i+1)*MAPTILEY + j].object == steelwork &&
				//		_vTiles[(i + 1)*MAPTILEY + j+1].object == steelwork) {
				//		steelwork->frameRender(getMemDC(), 
				//			_vTiles[(i-1)*MAPTILEY + j].rc.left, 
				//			_vTiles[(i-1)*MAPTILEY + j].rc.top, 
				//			_vTiles[i*MAPTILEY + j].objFrameX,  
				//			_vTiles[i*MAPTILEY + j].objFrameY);
				//	}
				//}
				//else {
				//	_vTiles[i*MAPTILEY + j].object->frameRender(getMemDC(), _vTiles[i*MAPTILEY + j].rc.left, _vTiles[i*MAPTILEY + j].rc.bottom - _vTiles[i*MAPTILEY + j].object->getFrameHeight(), _vTiles[i*MAPTILEY + j].objFrameX, _vTiles[i*MAPTILEY + j].objFrameY);
				//}
				_vTiles[i*MAPTILEY + j].object->frameRender(getMemDC(), CAMERA->GetRelativeX(_vTiles[i*MAPTILEY + j].rc.left), CAMERA->GetRelativeY(_vTiles[i*MAPTILEY + j].rc.bottom - _vTiles[i*MAPTILEY + j].object->getFrameHeight()), _vTiles[i*MAPTILEY + j].objFrameX, _vTiles[i*MAPTILEY + j].objFrameY);
				//Rectangle(getMemDC(), _vTiles[i*MAPTILEY + j].rc);
			}
			
			//부수면 열매나옴
			if (_vTiles[i*MAPTILEY + j].objHp == 0 && (_vTiles[i*MAPTILEY + j].object == IMAGEMANAGER->findImage("berry")))
			{
				IMAGEMANAGER->findImage("스테미나")->setWidth(1);
				int dropItemLot = RANDOM->range(2, 3);
				for (int c = 0; c < dropItemLot; c++)
				{
					float dX = (_vTiles[i*MAPTILEY + j].rc.left + RANDOM->range(-30,30));
					float dY = (_vTiles[i*MAPTILEY + j].rc.bottom - _vTiles[i*MAPTILEY + j].object->getFrameHeight()+ RANDOM->range(-30, 30));
					
					dropItem _dropItem;

					_dropItem.dropItems = berryDrop;
					_dropItem.imgName = "열매";
					_dropItem.dropItemX = dX;
					_dropItem.dropItemY = dY;
					_dropItem.rc = RectMakeCenter(_dropItem.dropItemX, _dropItem.dropItemY, 56, 56);
					_vDropItems.push_back(_dropItem);
				}
				
				_vTiles[i*MAPTILEY + j].objHp = -5;
			
			}

			//부수면 통나무나옴
			else if (_vTiles[i*MAPTILEY + j].objHp == 1 && (_vTiles[i*MAPTILEY + j].object == IMAGEMANAGER->findImage("tree")))
			{
				IMAGEMANAGER->findImage("스테미나")->setWidth(1);
				int dropItemLot = RANDOM->range(2, 3);
				for (int c = 0; c < dropItemLot; c++)
				{
					float dX = (_vTiles[i*MAPTILEY + j].rc.left + _vTiles[i*MAPTILEY + j].rc.right) / 2 + RANDOM->range(-20, 20);
					float dY = (_vTiles[i*MAPTILEY + j].rc.top + _vTiles[i*MAPTILEY + j].rc.bottom) / 2 + RANDOM->range(-20, 20);
					cout << dX << endl;
					cout << dY << endl;
					dropItem _dropItem;

					_dropItem.dropItems = treeDrop;
					_dropItem.imgName = "목재";
					_dropItem.dropItemX = dX;
					_dropItem.dropItemY = dY;
					_dropItem.rc = RectMakeCenter(_dropItem.dropItemX, _dropItem.dropItemY, 56, 56);
					_vDropItems.push_back(_dropItem);
				}

				_vTiles[i*MAPTILEY + j].objHp = -5;
			}

			//부수면 돌나옴 
			else if (_vTiles[i*MAPTILEY + j].objHp == 0 && (_vTiles[i*MAPTILEY + j].object == IMAGEMANAGER->findImage("rock")))
			{
				IMAGEMANAGER->findImage("스테미나")->setWidth(1);
				int dropItemLot = RANDOM->range(2, 3);
				for (int c = 0; c < dropItemLot; c++)
				{
					float dX = (_vTiles[i*MAPTILEY + j].rc.left + _vTiles[i*MAPTILEY + j].rc.right) / 2 + RANDOM->range(-30, 30);
					float dY = (_vTiles[i*MAPTILEY + j].rc.top + _vTiles[i*MAPTILEY + j].rc.bottom) / 2 + RANDOM->range(-30, 30);

					dropItem _dropItem;

					_dropItem.dropItems = rockDrop;
					_dropItem.imgName = "돌";
					_dropItem.dropItemX = dX;
					_dropItem.dropItemY = dY;
					_dropItem.rc = RectMakeCenter(_dropItem.dropItemX, _dropItem.dropItemY, 56, 56);
					_vDropItems.push_back(_dropItem);
				}

				_vTiles[i*MAPTILEY + j].objHp = -5;
			}
		}
	}

	_targetingBox->render(getMemDC());

	//int playerCenterX = _rcPlayer.left + (_rcPlayer.right - _rcPlayer.left) / 2;
	//int playerCenterY = _rcPlayer.top + (_rcPlayer.bottom - _rcPlayer.top) / 2;
	//textOut(getMemDC(), 0, 0, (to_string(CAMRANGE)+" "+ to_string(getDistance(playerCenterX - CAMSPEED, playerCenterY, WINSIZEX / 2, WINSIZEY / 2))).c_str());
	//textOut(getMemDC(), 0, 0, ("플레이어 좌표 : "+ to_string(_playerPos)).c_str());
	//Rectangle(getMemDC(), _rcPlayer);
	
	//드랍아이템 벡터 rc위치에 해당하는 드랍아이템 이미지 그리기 
	for (int i = 0; i < _vDropItems.size(); i++)
	{
		_vDropItems[i].dropItems->render(getMemDC(), CAMERA->GetRelativeX(_vDropItems[i].rc.left), CAMERA->GetRelativeY(_vDropItems[i].rc.top));
	}

	_inventory->render();
	// 커서 렌더
	IMAGEMANAGER->findImage("TitleCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
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
		if (_inventory->getBuildingStatus()) {
			//POINT _ptBuilding = { _ptMouse.x - 1, _ptMouse.y + IMAGEMANAGER->findImage("용광로")->getHeight() / 2 };
			for (int i = 0; i < TILEY*MAPY; i++) {
				bool stop = false;
				for (int j = 0; j < MAPTILEX; j++) {
					if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, CAMERA->GetMouseRelativePos(_ptMouse))) {
						//타일 4개
						//if (_vTiles[i*MAPTILEY + j].objHp == 0 &&
						//	_vTiles[i*MAPTILEY + j].terrain == IMAGEMANAGER->findImage("plaintile") &&
						//	_vTiles[i*MAPTILEY + j + 1].objHp == 0 &&
						//	_vTiles[i*MAPTILEY + j + 1].terrain == IMAGEMANAGER->findImage("plaintile") &&
						//	_vTiles[(i - 1)*MAPTILEY + j].objHp == 0 &&
						//	_vTiles[(i - 1) *MAPTILEY + j].terrain == IMAGEMANAGER->findImage("plaintile") &&
						//	_vTiles[(i - 1)*MAPTILEY + j + 1].objHp == 0 &&
						//	_vTiles[(i - 1) * MAPTILEY + j + 1].terrain == IMAGEMANAGER->findImage("plaintile")) {
						//	_vTiles[i*MAPTILEY + j].object = steelwork;
						//	_vTiles[i*MAPTILEY + j].objHp = 10;
						//	_vTiles[i*MAPTILEY + j].objFrameX = 0;
						//	_vTiles[i*MAPTILEY + j].objFrameY = 0;
						//	_vTiles[i*MAPTILEY + j + 1].object = _vTiles[i*MAPTILEY + j].object;
						//	_vTiles[i*MAPTILEY + j + 1].objHp = _vTiles[i*MAPTILEY + j].objHp;
						//	_vTiles[i*MAPTILEY + j + 1].objFrameX = _vTiles[i*MAPTILEY + j].objFrameX;
						//	_vTiles[i*MAPTILEY + j + 1].objFrameY = _vTiles[i*MAPTILEY + j].objFrameY;
						//	_vTiles[(i - 1)*MAPTILEY + j].object = _vTiles[i*MAPTILEY + j].object;
						//	_vTiles[(i - 1)*MAPTILEY + j].objHp = _vTiles[i*MAPTILEY + j].objHp;
						//	_vTiles[(i - 1)*MAPTILEY + j].objFrameX = _vTiles[i*MAPTILEY + j].objFrameX;
						//	_vTiles[(i - 1)*MAPTILEY + j].objFrameY = _vTiles[i*MAPTILEY + j].objFrameY;
						//	_vTiles[(i - 1)*MAPTILEY + j + 1].object = _vTiles[i*MAPTILEY + j].object;
						//	_vTiles[(i - 1)*MAPTILEY + j + 1].objHp = _vTiles[i*MAPTILEY + j].objHp;
						//	_vTiles[(i - 1)*MAPTILEY + j + 1].objFrameX = _vTiles[i*MAPTILEY + j].objFrameX;
						//	_vTiles[(i - 1)*MAPTILEY + j + 1].objFrameY = _vTiles[i*MAPTILEY + j].objFrameY;
						//	_inventory->setBuildingStatus(false);
						//}
						if (_vTiles[i*MAPTILEY + j].objHp == 0 && 
							_vTiles[i*MAPTILEY + j].terrain == IMAGEMANAGER->findImage("plaintile")) {
								_vTiles[i*MAPTILEY + j].object = steelwork;
								_vTiles[i*MAPTILEY + j].objHp = 500;
								_vTiles[i*MAPTILEY + j].objFrameX = 0;
								_vTiles[i*MAPTILEY + j].objFrameY = 0;
								_inventory->setBuildingStatus(false);
						}
						stop = true;
						break;
					}
				}
				if (stop) break;
			}
		}
		for (int i = 0; i < TILEY*MAPY; i++) {
			bool stop = false;
			for (int j = 0; j < MAPTILEX; j++) {
				if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, CAMERA->GetMouseRelativePos(_ptMouse))) {
					_targetingBox->RemoveTarget();
					_targetingBox->SetTarget(_vTiles[i*MAPTILEY + j].rc);
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
				if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, CAMERA->GetMouseRelativePos(_ptMouse))) {
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


#pragma region 카메라 매니저로 대체 (cameraMove, cameraFocus)

/* 카메라 메니저로 대체
void basicmap::cameraMove()
{
	int playerCenterX = _rcPlayer.left + (_rcPlayer.right - _rcPlayer.left) / 2;
	int playerCenterY = _rcPlayer.top + (_rcPlayer.bottom - _rcPlayer.top) / 2;
	if (_ptMouse.x > (WINSIZEX / 2) + 100 &&
		_vTiles.back().rc.right > WINSIZEX &&
		getDistance(playerCenterX - CAMSPEED, playerCenterY, WINSIZEX/2, WINSIZEY/2) < CAMRANGE) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.left -= CAMSPEED;
				_vTiles[i*MAPTILEY + j].rc.right -= CAMSPEED;
			}
		}
		//_rcPlayer.left -= CAMSPEED;
		//_rcPlayer.right -= CAMSPEED;
		RECT playerPos = _player->getPlayerRect();
		playerPos.left -= CAMSPEED;
		playerPos.right -= CAMSPEED;
		_player->setPlayerRect(playerPos);

		for (int i = 0; i < _vDropItems.size(); i++)
		{
			_vDropItems[i].rc.left -= CAMSPEED;
			_vDropItems[i].rc.right -= CAMSPEED;
		}
	}
	if (_ptMouse.x < (WINSIZEX / 2) - 100 &&
		_vTiles[0].rc.left < 0 &&
		getDistance(playerCenterX + CAMSPEED, playerCenterY, WINSIZEX / 2, WINSIZEY / 2) < CAMRANGE) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.left += CAMSPEED;
				_vTiles[i*MAPTILEY + j].rc.right += CAMSPEED;
			}
		}
		//_rcPlayer.left += CAMSPEED;
		//_rcPlayer.right += CAMSPEED;
		RECT playerPos = _player->getPlayerRect();
		playerPos.left += CAMSPEED;
		playerPos.right += CAMSPEED;
		_player->setPlayerRect(playerPos);

		for (int i = 0; i < _vDropItems.size(); i++)
		{
			_vDropItems[i].rc.left += CAMSPEED;
			_vDropItems[i].rc.right += CAMSPEED;
		}
	}
	if (_ptMouse.y > WINSIZEY / 2 + 100 &&
		_vTiles.back().rc.bottom > WINSIZEY &&
		getDistance(playerCenterX, playerCenterY - CAMSPEED, WINSIZEX / 2, WINSIZEY / 2) < CAMRANGE) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.top -= CAMSPEED;
				_vTiles[i*MAPTILEY + j].rc.bottom -= CAMSPEED;
			}
		}
		//_rcPlayer.top -= CAMSPEED;
		//_rcPlayer.bottom -= CAMSPEED;
		RECT playerPos = _player->getPlayerRect();
		playerPos.top -= CAMSPEED;
		playerPos.bottom -= CAMSPEED;
		_player->setPlayerRect(playerPos);

		for (int i = 0; i < _vDropItems.size(); i++)
		{
			_vDropItems[i].rc.top -= CAMSPEED;
			_vDropItems[i].rc.bottom -= CAMSPEED;
		}
	}
	if (_ptMouse.y < WINSIZEY / 2 - 100 &&
		_vTiles[0].rc.top < 0 &&
		getDistance(playerCenterX, playerCenterY + CAMSPEED, WINSIZEX / 2, WINSIZEY / 2) < CAMRANGE) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.top += CAMSPEED;
				_vTiles[i*MAPTILEY + j].rc.bottom += CAMSPEED;
			}
		}
		//_rcPlayer.top += CAMSPEED;
		//_rcPlayer.bottom += CAMSPEED;

		RECT playerPos = _player->getPlayerRect();
		playerPos.top += CAMSPEED;
		playerPos.bottom += CAMSPEED;
		_player->setPlayerRect(playerPos);

		for (int i = 0; i < _vDropItems.size(); i++)
		{
			_vDropItems[i].rc.top += CAMSPEED;
			_vDropItems[i].rc.bottom += CAMSPEED;
		}
	}
}
*/



/* 카메라 메니저로 대체
void basicmap::cameraFocus()
{
	//if (_ptmouse.x < winsizex / 2 - 100 ||
	//	_ptmouse.x > winsizex / 2 + 100 ||
	//	_ptmouse.y < winsizey / 2 - 100 ||
	//	_ptmouse.y > winsizey / 2 + 100) return;
	int playerCenterX = _rcPlayer.left + (_rcPlayer.right - _rcPlayer.left) / 2;
	int playerCenterY = _rcPlayer.top + (_rcPlayer.bottom - _rcPlayer.top) / 2;
	if (playerCenterX != WINSIZEX/2) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.left += WINSIZEX/2 - playerCenterX < 0 ? -1 : 1;
				_vTiles[i*MAPTILEY + j].rc.right += WINSIZEX / 2 - playerCenterX < 0 ? -1 : 1;
			}
		}
		RECT playerPos = _player->getPlayerRect();
		playerPos.left += WINSIZEX / 2 - playerCenterX < 0 ? -1 : 1;
		playerPos.right += WINSIZEX / 2 - playerCenterX < 0 ? -1 : 1;
		_player->setPlayerRect(playerPos);

		for (int i = 0; i < _vDropItems.size(); i++)
		{
			_vDropItems[i].rc.left += WINSIZEX / 2 - playerCenterX < 0 ? -1 : 1;
			_vDropItems[i].rc.right += WINSIZEX / 2 - playerCenterX < 0 ? -1 : 1;
		}
	}
	if (playerCenterY != WINSIZEY/2) {
		for (int i = 0; i < MAPTILEY; i++) {
			for (int j = 0; j < MAPTILEX; j++) {
				_vTiles[i*MAPTILEY + j].rc.top += WINSIZEY / 2 - playerCenterY < 0 ? -1 : 1;
				_vTiles[i*MAPTILEY + j].rc.bottom += WINSIZEY / 2 - playerCenterY < 0 ? -1 : 1;
			}
		}
		RECT playerPos = _player->getPlayerRect();
		playerPos.top += WINSIZEY / 2 - playerCenterY < 0 ? -1 : 1;
		playerPos.bottom += WINSIZEY / 2 - playerCenterY < 0 ? -1 : 1;
		_player->setPlayerRect(playerPos);

		for (int i = 0; i < _vDropItems.size(); i++)
		{
			_vDropItems[i].rc.top += WINSIZEY / 2 - playerCenterY < 0 ? -1 : 1;
			_vDropItems[i].rc.bottom += WINSIZEY / 2 - playerCenterY < 0 ? -1 : 1;
		}
	}
}
*/

#pragma endregion


void basicmap::setRandomTile()
{
	
	if (this->getResRatio() > RESRATIOLIMIT) return;
	while (true) {
		int i = RANDOM->range(TILEY*MAPY);
		int j = RANDOM->range(MAPTILEX);
		//현재 플레이어가 서있는 타일은 스킵
		if (i + j == getPlayerPos()) continue;
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
			break;
		}
	}
}

float basicmap::getResRatio()
{
	float nResTile = 0;
	float nPlainTile = 0;
	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (_vTiles[i*MAPTILEY + j].terrain == plaintile &&
				_vTiles[i*MAPTILEY + j].objHp == 0) {
				nPlainTile++;
			}
			else if (_vTiles[i*MAPTILEY + j].terrain == plaintile &&
				_vTiles[i*MAPTILEY + j].objHp > 0) {
				nResTile++;
			}
		}
	}
	return nResTile / float(nPlainTile);
}


// 최초 1회 실행
int basicmap::getPlayerPos()
{
	int playerCenterX = _rcPlayer.left + (_rcPlayer.right - _rcPlayer.left) / 2;
	int playerCenterY = _rcPlayer.bottom;
	_ptPlayerPos = { playerCenterX, playerCenterY };


	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, _ptPlayerPos)) {
				return (i*MAPTILEY + j);
			}
		}
	}
}

// 이동 가능 여부 체크
bool basicmap::checkCanMove(int index)
{
	// 이동 가능
	if (_vTiles[_playerPos + index].terrain != watertile &&
		_vTiles[_playerPos + index].objHp <= 0) {


		return false;
	}
		
	RECT t_bound = RectMakeCenter(_ptPlayerPos.x, _ptPlayerPos.y, 20, 10);
	RECT t_temp;
	if (!IntersectRect(&t_temp, &t_bound, &_vTiles[_playerPos + index].rc)) {
		return false;
	}

	// 이동 불가
	return true;
}


//드랍아이템 삭제 
void basicmap::removeDropItem(int index)
{
	_vDropItems.erase(_vDropItems.begin() + index);
}

//드랍아이템과 플레이어 충돌(충돌시 아이템 획득)
void basicmap::dropItemCollision()
{
	RECT temp;
	bool is_check = true;
	for (int i = 0; i < _vDropItems.size(); i++)
	{
		if (IntersectRect(&temp, &_rcPlayer, &_vDropItems[i].rc))
		{
			for (int k = 0; k < _inventory->getPlayerInventory().size(); k++)
			{
				if (_inventory->getPlayerInventory()[k]->item_name == _vDropItems[i].imgName)
				{
					is_item_check = false;
					_inventory->getPlayerInventory()[k]->count++;
					removeDropItem(i);
					
					break;
				}
				else {
					is_check = false;
				}

			}


		}
	}
		
	if (!is_check) {
		for (int i = 0; i < _vDropItems.size(); i++)
		{
			if (IntersectRect(&temp, &_rcPlayer, &_vDropItems[i].rc))
			{

				for (int c = 0; c < _inventory->getPlayerInventory().size(); c++)
				{
					if (_inventory->getPlayerInventory()[c]->img_name != "")continue;		//인벤토리 안에 아이템이 없다면~ 

					if (_vDropItems[i].imgName == "목재")
					{
						_inventory->getPlayerInventory()[c]->isCheck = true;
						_inventory->getPlayerInventory()[c]->Kinds = ITEM_MATERIAL;
						_inventory->getPlayerInventory()[c]->count = 1;
						_inventory->getPlayerInventory()[c]->item_name = "목재";
						_inventory->getPlayerInventory()[c]->img_name = "treeDrop";
					}
					else if (_vDropItems[i].imgName == "돌")
					{
						_inventory->getPlayerInventory()[c]->isCheck = true;
						_inventory->getPlayerInventory()[c]->Kinds = ITEM_MATERIAL;
						_inventory->getPlayerInventory()[c]->count = 1;
						_inventory->getPlayerInventory()[c]->item_name = "돌";
						_inventory->getPlayerInventory()[c]->img_name = "rockDrop";
					}
					else if (_vDropItems[i].imgName == "열매")
					{
						_inventory->getPlayerInventory()[c]->isCheck = true;
						_inventory->getPlayerInventory()[c]->Kinds = ITEM_FOOD;
						_inventory->getPlayerInventory()[c]->count = 1;
						_inventory->getPlayerInventory()[c]->item_name = "열매";
						_inventory->getPlayerInventory()[c]->img_name = "berryDrop";
					}
					removeDropItem(i);
					break;
				}
			}
		}
	}


	
}

tile basicmap::tileMouseTarget()
{
	for (int i = 0; i < TILEY*MAPY; i++) {
		bool stop = false;
		for (int j = 0; j < MAPTILEX; j++) {
			if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, CAMERA->GetMouseRelativePos(_ptMouse))) {
				_targetingBox->RemoveTarget();
				_targetingBox->SetTarget(_vTiles[i*MAPTILEY + j].rc, true);
				return _vTiles[i*MAPTILEY + j];
			}
		}
	}
}


// 플레이어 좌표 세팅.
void basicmap::setPlayerPosTile()
{
	int playerCenterX = _rcPlayer.left + (_rcPlayer.right - _rcPlayer.left) / 2;
	int playerCenterY = _rcPlayer.bottom;
	_ptPlayerPos = { playerCenterX, playerCenterY };

	// 플레이어 좌표 기준 상하좌우 타일중에 
	// 지금 밟고 있는 타일로 좌표 변경
	if (PtInRect(&_vTiles[_playerPos].rc, _ptPlayerPos))
		_playerPos = _playerPos;


	else if (PtInRect(&_vTiles[_playerPos + 1].rc, _ptPlayerPos)) 
		_playerPos += 1;
	else if (PtInRect(&_vTiles[_playerPos - 1].rc, _ptPlayerPos)) 
		_playerPos -= 1;
	else if (PtInRect(&_vTiles[_playerPos + MAPTILEX].rc, _ptPlayerPos)) 
		_playerPos += MAPTILEX;
	else if (PtInRect(&_vTiles[_playerPos - MAPTILEX].rc, _ptPlayerPos))
		_playerPos -= MAPTILEX;


	else if (PtInRect(&_vTiles[_playerPos - MAPTILEX + 1].rc, _ptPlayerPos))
		_playerPos += MAPTILEX + 1;
	else if (PtInRect(&_vTiles[_playerPos - MAPTILEX - 1].rc, _ptPlayerPos))
		_playerPos -= MAPTILEX - 1;
	else if (PtInRect(&_vTiles[_playerPos + MAPTILEX + 1].rc, _ptPlayerPos))
		_playerPos += MAPTILEX + 1;
	else if (PtInRect(&_vTiles[_playerPos + MAPTILEX - 1].rc, _ptPlayerPos))
		_playerPos -= MAPTILEX - 1;

	else 
		_playerPos = getPlayerPos();
	
}
