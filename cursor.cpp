#include "stdafx.h"
#include "cursor.h"
#include "earth.h"
void cursor::init()
{
	vUnit = UNITMANAGER->GetUnits();
	_buildinginteraction = new buildinginteraction;
	_buildinginteraction->init();
	_targetingBox.init();
	_unit = nullptr;
	isbuilding = false;
	interaction = false;
	IMAGEMANAGER->addImage("BuildingInteractionE", "Images/이미지/GUI/E.bmp", 40, 40, true, RGB(255, 0, 255));
}

void cursor::update()
{
	CheckObject();
	_targetingBox.update();
	if (isbuilding) {
		if (INPUT->GetKeyDown('E')) {

			if (interaction) {
				interaction = false;
			}
			else {
				interaction = true;
				SOUNDMANAGER->play("건물상호작용");
			}
		}
	}

}

void cursor::render(HDC hdc)
{
	_targetingBox.render(hdc);
	if (isbuilding) {
		IMAGEMANAGER->render("BuildingInteractionE", hdc,
			CAMERA->GetRelativeX(_unit->GetCenterX()-20),
			CAMERA->GetRelativeY(_unit->GetCenterY()-20));
	}
	if (interaction) {
		_buildinginteraction->targertrender(hdc, vUnit[number]->objKey);
	}
}


void cursor::CheckObject()
{
	if (!interaction) {
		vUnit.clear();
		vUnit = UNITMANAGER->GetUnits();

		isbuilding = false;


		// 특정 태그만 타겟팅
		for (int i = 0; i < vUnit.size(); i++) {
			if ((*vUnit[i]).tag == TAG::OBJECT || (*vUnit[i]).tag == TAG::ENEMY || (*vUnit[i]).tag == TAG::NPC){
				RECT t_rc = (*vUnit[i]).rc;
				if (PtInRect(&t_rc, CAMERA->GetMouseRelativePos(_ptMouse))) {
					_targetingBox.SetTarget(t_rc, 3, i, 2, true);
					_unit = &(*vUnit[i]);
					return;
				}
			}
			if ((*vUnit[i]).tag == TAG::BUILDING) {

				RECT t_rc = (*vUnit[i]).rc;
				if (PtInRect(&t_rc, CAMERA->GetMouseRelativePos(_ptMouse))) {
					if (_targetingBox.GetTargetID() != i) {
						SOUNDMANAGER->play("건물커서");
					}
					_targetingBox.SetTarget(t_rc, 3, i, 2, true);
					_unit = &(*vUnit[i]);
					if (_unit->objKey != "bridge") {
						isbuilding = true;
						PRODUCTIONMANAGER->getRc(t_rc);
						number = i;
					}
					return;
				}
			}
		}


		_unit = nullptr;
		_targetingBox.RemoveTarget();
	}
}