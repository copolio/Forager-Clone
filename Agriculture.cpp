#include "stdafx.h"
#include "Agriculture.h"
#include "earth.h"

HRESULT Agriculture::init()
{
	_target = false;
	_targetBox = new targetingBox;
	_targetBox->init();
	tooltip = new construction_tool_tip;
	AGRICULTURERc *push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_BRIDGE;
	push->name = "bridge";
	push->rc = RectMake(WINSIZEX - 267, 235, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_FISHTRAP;
	push->name = "fishtrap";
	push->rc = RectMake(WINSIZEX - 267, 295, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 355, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 415, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 475, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 535, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 595, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 655, 220, 50);
	agriRc.push_back(push);

	//건물 건설 확인 렌더용 이미지 및 변수
	is_building_check = false;
	IMAGEMANAGER->addImage("bridgedesign", "Images/이미지/오브젝트/다리.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bridge", "Images/이미지/오브젝트/building/img_object_bridge.bmp", 224, 56, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("fishtrapdesign", "Images/이미지/오브젝트/통발.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fishtrap", "Images/이미지/오브젝트/building/img_object_fishtrap.bmp", 168, 56, 3, 1, true, RGB(255, 0, 255));


	return S_OK;
}

void Agriculture::release()
{
}

void Agriculture::update()
{
	if (_target) {
		_targetBox->update();
	}
	mouse_targetBox();
	agricultureItemCheck();
	addBuilding();
}

void Agriculture::render(HDC hdc)
{
	for (int i = 0; i < agriRc.size(); i++) {
		switch (agriRc[i]->kind)
		{
		case AGRICULTUREKIND_MISSING:
			IMAGEMANAGER->render("img_Agriculture_missing_icon", hdc, agriRc[i]->rc.left, agriRc[i]->rc.top);
			break;
		case AGRICULTUREKIND_BRIDGE:
			IMAGEMANAGER->render("img_bridge_icon", hdc, agriRc[i]->rc.left, agriRc[i]->rc.top);
			break;
		case AGRICULTUREKIND_FISHTRAP:
			IMAGEMANAGER->render("img_fish_trap_icon", hdc, agriRc[i]->rc.left, agriRc[i]->rc.top);
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


void Agriculture::mouse_targetBox()
{
	for (int i = 0; i < agriRc.size(); i++) {
		if (PtInRect(&agriRc[i]->rc, _ptMouse)) {
			_targetBox->SetTarget(agriRc[i]->rc, 2, i, 4, false);
			_target = true;
			break;
		}

	}
}

void Agriculture::RemoveTarget()
{
	_targetBox->RemoveTarget();
}

void Agriculture::renderBuildableTile(HDC hdc)
{
	_tileIndex = _map->tileMouseTargetIndex();
	tile t_tile = _map->GetTile(_tileIndex);
	POINT t_ptMouse = CAMERA->GetMouseRelativePos(_ptMouse);
	string buildingdesign = building + "design";
	image* t_imgBuilding = IMAGEMANAGER->findImage(buildingdesign);

	if (t_tile.hasUnit || t_tile.terrKey != "watertile") 
		IMAGEMANAGER->alphaRender("redtile", hdc, CAMERA->GetRelativeX(t_tile.rc.left), CAMERA->GetRelativeY(t_tile.rc.top), 100);
	else 
		IMAGEMANAGER->alphaRender("greentile", hdc, CAMERA->GetRelativeX(t_tile.rc.left), CAMERA->GetRelativeY(t_tile.rc.top), 100);
	
	IMAGEMANAGER->alphaRender(buildingdesign, hdc,
		CAMERA->GetRelativeX(t_ptMouse.x - t_imgBuilding->getWidth() / 2),
		CAMERA->GetRelativeY(t_ptMouse.y - t_imgBuilding->getHeight() / 2), 160);

}

bool Agriculture::agricultureItemCheck()
{
	for (int i = 0; i < agriRc.size(); i++) {
		if (PtInRect(&agriRc[i]->rc, _ptMouse) && agriRc[i]->kind != AGRICULTUREKIND_MISSING && INPUT->GetKeyUp(VK_LBUTTON)) {
			SOUNDMANAGER->play("건설탭클릭");
			if (agriRc[i]->kind == AGRICULTUREKIND_BRIDGE) {
				if (ITEMMANAGER->Item_industry_check("bridge")) {
					is_building_check = true;
					building = "bridge";
				}
				return ITEMMANAGER->Item_industry_check("bridge");
			}
			else if (agriRc[i]->kind == AGRICULTUREKIND_FISHTRAP) {
				if (ITEMMANAGER->Item_industry_check("fishtrap")) {
					is_building_check = true;
					building = "fishtrap";
				}
				return ITEMMANAGER->Item_industry_check("fishtrap");
			}
		}
	}
	return false;
}

void Agriculture::addBuilding()
{
	if (INPUT->GetKey(VK_LBUTTON)) {
		if (is_building_check) {

			tile* t_pTile = _map->GetTileP(_tileIndex);

			if (!t_pTile->hasUnit && t_pTile->terrKey == "watertile")
			{
				is_building_check = false;
				_map->setTileHasUnit(_tileIndex);
				UNITMANAGER->AddBuilding(building, t_pTile, _tileIndex);
				ITEMMANAGER->_Item_industry_decrease(building);
				SOUNDMANAGER->play("건설성공");
			}
		}
		else if (is_building_check) {
			if (!SOUNDMANAGER->isPlaySound("건설실패")) {
				SOUNDMANAGER->play("건설실패");
			}
		}
	}
	if (INPUT->GetKey(VK_RBUTTON)) {
		is_building_check = false;
		if (!SOUNDMANAGER->isPlaySound("건설취소")) {
			SOUNDMANAGER->play("건설취소");
		}
	}
}
void Agriculture::tooltiprender(HDC hdc)
{
	for (int i = 0; i < agriRc.size(); i++) {
		if (PtInRect(&agriRc[i]->rc, _ptMouse) && agriRc[i]->kind != AGRICULTUREKIND_MISSING) {
			tooltip->render(hdc, agriRc[i]->name, agriRc[i]->rc);
		}
	}
}
