#include "stdafx.h"
#include "cursor.h"



void cursor::init()
{
	_targetingBox.init();
	_unit = nullptr;
}

void cursor::update()
{
	CheckObject();
	_targetingBox.update();
}

void cursor::render(HDC hdc)
{
	_targetingBox.render(hdc);
}


void cursor::CheckObject()
{

	vector<unit*> vUnit = UNITMANAGER->GetUnits();
	
	// 태그가 오브젝트 (자연) 인 것만 타겟팅
	for (int i = 0; i < vUnit.size(); i++) {
		if ((*vUnit[i]).tag == TAG::OBJECT) {

			RECT t_rc = (*vUnit[i]).rc;
			if (PtInRect(&t_rc, CAMERA->GetMouseRelativePos(_ptMouse))) {

				_targetingBox.SetTarget(t_rc, 3, i, 2, true);
				_unit = &(*vUnit[i]);
				return;
			}
		}
	}

	_unit = nullptr;
	_targetingBox.RemoveTarget();

}
