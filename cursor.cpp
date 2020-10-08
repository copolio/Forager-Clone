#include "stdafx.h"
#include "cursor.h"



void cursor::init()
{
	_targetingBox.init();
	_unit = nullptr;
	isbuilding = false;

	IMAGEMANAGER->addImage("BuildingInteractionE", "Images/이미지/GUI/E.bmp", 40, 40, true, RGB(255, 0, 255));
}

void cursor::update()
{
	CheckObject();
	_targetingBox.update();
}

void cursor::render(HDC hdc)
{
	_targetingBox.render(hdc);
	if (isbuilding) {
		IMAGEMANAGER->render("BuildingInteractionE", hdc,
			CAMERA->GetRelativeX(_unit->GetCenterX()-20),
			CAMERA->GetRelativeY(_unit->GetCenterY()-20));
	}
}


void cursor::CheckObject()
{

	vector<unit*> vUnit = UNITMANAGER->GetUnits();
	isbuilding = false;
	// 태그가 오브젝트 (자연) 인 것만 타겟팅
	for (int i = 0; i < vUnit.size(); i++) {
		if ((*vUnit[i]).tag == TAG::OBJECT || (*vUnit[i]).tag == TAG::ENEMY) {

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

				_targetingBox.SetTarget(t_rc, 3, i, 2, true);
				_unit = &(*vUnit[i]);
				if (_unit->objKey != "bridge") isbuilding = true;
				return;
			}
		}
	}

	_unit = nullptr;
	_targetingBox.RemoveTarget();

}