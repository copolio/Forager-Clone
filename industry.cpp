#include "stdafx.h"
#include "industry.h"
#include "earth.h"

HRESULT industry::init()
{
	_target = false;
	_targetBox = new targetingBox;
	_targetBox->init();
	IndustryRc *push = new IndustryRc;

	push->kind = INDUSTRY_STEELWORK;
	push->rc = RectMake(WINSIZEX - 267, 115, 220, 50);
	push->name = "steelwork";
	indu_rc.push_back(push);
	
	push = new IndustryRc;
	push->kind = INDUSTRY_ANVIL;
	push->name = "anvil";
	push->rc = RectMake(WINSIZEX - 267, 175, 220, 50);
	indu_rc.push_back(push);

	push = new IndustryRc;
	push->kind = INDUSTRY_SEWINGMACHINE;
	push->name = "sewingmachine";
	push->rc = RectMake(WINSIZEX - 267, 235 , 220, 50);
	indu_rc.push_back(push);

	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 295, 220, 50);
	indu_rc.push_back(push);

	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 355, 220, 50);
	indu_rc.push_back(push);


	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 415, 220, 50);
	indu_rc.push_back(push);

	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 475, 220, 50);
	indu_rc.push_back(push); 

	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 535, 220, 50);
	indu_rc.push_back(push);
	
	//건물 건설 확인 렌더용 이미지 및 변수
	is_building_check = false;
	greentile = IMAGEMANAGER->addImage("greentile", "Images/이미지/타일/img_tile_green.bmp", 56, 56);
	redtile = IMAGEMANAGER->addImage("redtile", "Images/이미지/타일/img_tile_red.bmp", 56, 56);
	IMAGEMANAGER->addImage("steelworkdesign", "Images/이미지/오브젝트/용광로.bmp", 112 / 2, 160 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("steelwork", "Images/이미지/오브젝트/building/img_object_steelwork.bmp", 336 / 2, 168 / 2, 3, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void industry::release()
{
}

void industry::update()
{
	if (_target) {
		_targetBox->update();
	}
	mouse_targetBox();
	industryItemCheck();
	addBuilding();
}

void industry::render(HDC hdc)
{
	for (int i = 0; i < indu_rc.size(); i++) {
		switch (indu_rc[i]->kind)
		{
		case INDUSTRY_MISSING:
			IMAGEMANAGER->render("img_missing_icon", hdc, indu_rc[i]->rc.left, indu_rc[i]->rc.top);
			break;
		case INDUSTRY_STEELWORK:
			IMAGEMANAGER->render("img_steelwork_icon", hdc, indu_rc[i]->rc.left, indu_rc[i]->rc.top);
			break;
		case INDUSTRY_ANVIL:
			IMAGEMANAGER->render("img_anvil_icon", hdc, indu_rc[i]->rc.left, indu_rc[i]->rc.top);
			break;
		case INDUSTRY_SEWINGMACHINE:
			IMAGEMANAGER->render("img_sewingmachine_icon", hdc, indu_rc[i]->rc.left, indu_rc[i]->rc.top);
			break;
		}

	}
	if (is_building_check) {
		//건설 가능 타일 렌더
		//POINT _ptBuilding = { _ptMouse.x - 1, _ptMouse.y + IMAGEMANAGER->findImage(building)->getHeight() / 2 };
		
		tile* tile = _map->tileMouseTarget();
		if (tile->hasUnit || tile->terrKey != "plaintile") {
			redtile->alphaRender(hdc, CAMERA->GetRelativeX(tile->rc.left), CAMERA->GetRelativeY(tile->rc.top), 100);
		}
		else {
			greentile->alphaRender(hdc, CAMERA->GetRelativeX(tile->rc.left), CAMERA->GetRelativeY(tile->rc.top), 100);
		}
		string buildingdesign = building + "design";
		IMAGEMANAGER->alphaRender(buildingdesign, hdc,
			CAMERA->GetRelativeX(CAMERA->GetMouseRelativePos(_ptMouse).x - IMAGEMANAGER->findImage(buildingdesign)->getWidth() / 2),
			CAMERA->GetRelativeY(CAMERA->GetMouseRelativePos(_ptMouse).y - IMAGEMANAGER->findImage(buildingdesign)->getHeight() / 2), 160);
	}
	_targetBox->render(hdc);
}


void industry::mouse_targetBox()
{
	for (int i = 0; i < indu_rc.size(); i++) {
		if (PtInRect(&indu_rc[i]->rc, _ptMouse)) {
			_targetBox->SetTarget(indu_rc[i]->rc, 2, i, 4, false);
			_target = true;
			break;
		}

	}
}

void industry::RemoveTarget()
{
	_targetBox->RemoveTarget();
}

bool industry::industryItemCheck()
{
	for (int i = 0; i < indu_rc.size(); i++) {
		if (PtInRect(&indu_rc[i]->rc, _ptMouse) && indu_rc[i]->kind != INDUSTRY_MISSING&& INPUT->GetKeyDown(VK_LBUTTON)) {
			cout << "map size: " << _map->GetTiles().size() << endl;
			if (indu_rc[i]->kind == INDUSTRY_STEELWORK) {
				if (ITEMMANAGER->Item_industry_check("steelwork")) {
					is_building_check = true;
					building = "steelwork";
				}
				//is_building_check = true;
				//building = "steelwork";
				return ITEMMANAGER->Item_industry_check("steelwork");
			}
			else if (indu_rc[i]->kind == INDUSTRY_ANVIL) {
				is_building_check = true;
				building = "anvilicon";
				return ITEMMANAGER->Item_industry_check("anvil");
			}
			else if (indu_rc[i]->kind == INDUSTRY_SEWINGMACHINE) {
				is_building_check = true;
				building = "sewingmachine";
				return ITEMMANAGER->Item_industry_check("sewingmachine");
			}
		}
	}
	return false;
}

void industry::addBuilding()
{
	if (INPUT->GetKey(VK_LBUTTON)) {

		if (is_building_check) {
			tile* ptile = _map->tileMouseTarget();

			if (!ptile->hasUnit && ptile->terrKey == "plaintile") {

				ptile->hasUnit = true;

				//_map->setTileHasUnit(_map->tileMouseTargetIndex());
				vector<tile*> tiles;
				tiles.push_back(ptile);
				is_building_check = false;
				UNITMANAGER->AddBuilding(building, tiles);
			}
		}

		
	}
}
