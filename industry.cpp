#include "stdafx.h"
#include "industry.h"
#include "earth.h"

HRESULT industry::init()
{
	tooltip = new construction_tool_tip;
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
	IMAGEMANAGER->addImage("steelworkdesign", "Images/이미지/오브젝트/용광로.bmp", 112, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("anvildesign", "Images/이미지/오브젝트/모루.bmp", 100, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sewingmachinedesign", "Images/이미지/오브젝트/재봉소.bmp", 127, 155, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("steelwork", "Images/이미지/오브젝트/building/img_object_steelwork.bmp", 336, 168, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("anvil", "Images/이미지/오브젝트/building/img_object_anvil.bmp", 285, 95, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sewingmachine", "Images/이미지/오브젝트/building/img_object_sewingmachine.bmp", 378, 155, 3, 1, true, RGB(255, 0, 255));
	
	buildCount = 0;

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
		renderBuildableTile(hdc);
	}
	tooltiprender(hdc);
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

void industry::renderBuildableTile(HDC hdc)
{
	_tileIndex = _map->tileMouseTargetIndex();
	tile t_tile = _map->GetTile(_tileIndex);
	POINT t_ptMouse = CAMERA->GetMouseRelativePos(_ptMouse);
	string buildingdesign = building + "design";
	image* t_imgBuilding = IMAGEMANAGER->findImage(buildingdesign);

	if (_map->GetTile(_tileIndex).hasUnit ||
		_map->GetTile(_tileIndex).terrKey != "plaintile" ||
		_map->GetTile(_tileIndex + 1).hasUnit ||
		_map->GetTile(_tileIndex + 1).terrKey != "plaintile" ||
		_map->GetTile(_tileIndex + MAPTILEX).hasUnit ||
		_map->GetTile(_tileIndex + MAPTILEX).terrKey != "plaintile" ||
		_map->GetTile(_tileIndex + MAPTILEX + 1).hasUnit ||
		_map->GetTile(_tileIndex + MAPTILEX + 1).terrKey != "plaintile" ) {
		IMAGEMANAGER->alphaRender("redtile", hdc, CAMERA->GetRelativeX(_map->GetTile(_tileIndex).rc.left), CAMERA->GetRelativeY(_map->GetTile(_tileIndex).rc.top), 100);
		IMAGEMANAGER->alphaRender("redtile", hdc, CAMERA->GetRelativeX(_map->GetTile(_tileIndex + 1).rc.left), CAMERA->GetRelativeY(_map->GetTile(_tileIndex + 1).rc.top), 100);
		IMAGEMANAGER->alphaRender("redtile", hdc, CAMERA->GetRelativeX(_map->GetTile(_tileIndex + MAPTILEX).rc.left), CAMERA->GetRelativeY(_map->GetTile(_tileIndex + MAPTILEX).rc.top), 100);
		IMAGEMANAGER->alphaRender("redtile", hdc, CAMERA->GetRelativeX(_map->GetTile(_tileIndex + MAPTILEX + 1).rc.left), CAMERA->GetRelativeY(_map->GetTile(_tileIndex + MAPTILEX +1).rc.top), 100);
	}
	else {
		IMAGEMANAGER->alphaRender("greentile", hdc, CAMERA->GetRelativeX(_map->GetTile(_tileIndex).rc.left), CAMERA->GetRelativeY(_map->GetTile(_tileIndex).rc.top), 100);
		IMAGEMANAGER->alphaRender("greentile", hdc, CAMERA->GetRelativeX(_map->GetTile(_tileIndex + 1).rc.left), CAMERA->GetRelativeY(_map->GetTile(_tileIndex + 1).rc.top), 100);
		IMAGEMANAGER->alphaRender("greentile", hdc, CAMERA->GetRelativeX(_map->GetTile(_tileIndex + MAPTILEX).rc.left), CAMERA->GetRelativeY(_map->GetTile(_tileIndex + MAPTILEX).rc.top), 100);
		IMAGEMANAGER->alphaRender("greentile", hdc, CAMERA->GetRelativeX(_map->GetTile(_tileIndex + MAPTILEX + 1).rc.left), CAMERA->GetRelativeY(_map->GetTile(_tileIndex + MAPTILEX + 1).rc.top), 100);
	}
	IMAGEMANAGER->alphaRender(buildingdesign, hdc,
		CAMERA->GetRelativeX(CAMERA->GetMouseRelativePos(_ptMouse).x - IMAGEMANAGER->findImage(buildingdesign)->getWidth() / 2),
		CAMERA->GetRelativeY(CAMERA->GetMouseRelativePos(_ptMouse).y - IMAGEMANAGER->findImage(buildingdesign)->getHeight() / 2), 160);

}

bool industry::industryItemCheck()
{
	for (int i = 0; i < indu_rc.size(); i++) {

		if (PtInRect(&indu_rc[i]->rc, _ptMouse) && indu_rc[i]->kind != INDUSTRY_MISSING&& INPUT->GetKeyUp(VK_LBUTTON)) {
			SOUNDMANAGER->play("건설탭클릭");
			if (indu_rc[i]->kind == INDUSTRY_STEELWORK) {
				if (ITEMMANAGER->Item_industry_check("steelwork")) {
					is_building_check = true;
					buildCount++;
					building = "steelwork";
				}
				return ITEMMANAGER->Item_industry_check("steelwork");
			}
			else if (indu_rc[i]->kind == INDUSTRY_ANVIL) {
				if (ITEMMANAGER->Item_industry_check("steelwork")) {
					is_building_check = true;
					buildCount++;
					building = "anvil";
				}
				return ITEMMANAGER->Item_industry_check("anvil");
			}
			else if (indu_rc[i]->kind == INDUSTRY_SEWINGMACHINE) {
				if (ITEMMANAGER->Item_industry_check("steelwork")) {
					is_building_check = true;
					buildCount++;
					building = "sewingmachine";
				}
				return ITEMMANAGER->Item_industry_check("sewingmachine");
			}
		}
	}
	return false;
}

void industry::addBuilding()
{
	RECT darkback = RectMake(960, 0, WINSIZEX - 960, WINSIZEY);
	if (INPUT->GetKey(VK_LBUTTON) && !PtInRect(&darkback, CAMERA->GetMouseRelativePos(_ptMouse))) {
		if (is_building_check && buildCount > 0 &&
			!_map->GetTileP(_tileIndex)->hasUnit &&
			!_map->GetTileP(_tileIndex+1)->hasUnit &&
			!_map->GetTileP(_tileIndex+MAPTILEX)->hasUnit &&
			!_map->GetTileP(_tileIndex+MAPTILEX+1)->hasUnit &&
			_map->GetTileP(_tileIndex)->terrKey == "plaintile" &&
			_map->GetTileP(_tileIndex+1)->terrKey == "plaintile" &&
			_map->GetTileP(_tileIndex+MAPTILEX)->terrKey == "plaintile" &&
			_map->GetTileP(_tileIndex+MAPTILEX+1)->terrKey == "plaintile") {


			_map->setTileHasUnit(_tileIndex);
			_map->setTileHasUnit(_tileIndex+1);
			_map->setTileHasUnit(_tileIndex+MAPTILEX);
			_map->setTileHasUnit(_tileIndex+MAPTILEX+1);
			vector<tile*> tiles;
			tiles.push_back(_map->GetTileP(_tileIndex));
			tiles.push_back(_map->GetTileP(_tileIndex+1));
			tiles.push_back(_map->GetTileP(_tileIndex+MAPTILEX));
			tiles.push_back(_map->GetTileP(_tileIndex+MAPTILEX+1));
			buildCount--;
			if (buildCount == 0) {
				is_building_check = false;
			}
			UNITMANAGER->AddBuilding(building, tiles, _tileIndex);
			ITEMMANAGER->_Item_industry_decrease(building);
			SOUNDMANAGER->play("건설성공");
		}
		else if (is_building_check) {
			if (!SOUNDMANAGER->isPlaySound("건설실패")) {
				SOUNDMANAGER->play("건설실패");
			}
		}
	}
	if (INPUT->GetKey(VK_RBUTTON)) {
		is_building_check = false;
		buildCount = 0;
		if (!SOUNDMANAGER->isPlaySound("건설취소")) {
			SOUNDMANAGER->play("건설취소");
		}
	}
}

void industry::tooltiprender(HDC hdc)
{
	for (int i = 0; i < indu_rc.size(); i++) {
		if (PtInRect(&indu_rc[i]->rc, _ptMouse) && indu_rc[i]->kind != INDUSTRY_MISSING) {
			tooltip->render(hdc, indu_rc[i]->name, indu_rc[i]->rc);
		}
	}
}
