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
			if (_unit->objKey == "fishtrap") {
				if (_unit->hasRes) {
					_unit->hasRes = false;
					//isbuilding = false;
					//interaction = false;
					UNITMANAGER->AddUnits("fish", CAMERA->GetMouseRelativePos(_ptMouse));
				}
			}
			else {
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

}

void cursor::render(HDC hdc)
{
	if (CAMERA->movelimit) {
		_targetingBox.render(hdc);
		if (isbuilding) {
			IMAGEMANAGER->render("BuildingInteractionE", hdc,
				CAMERA->GetRelativeX(_unit->GetCenterX() - 20),
				CAMERA->GetRelativeY(_unit->GetCenterY() - 20));
		}
		if (interaction) {
			_buildinginteraction->targertrender(hdc, vUnit[number]->objKey);
		}
	}

}


void cursor::CheckObject()
{
	if (!interaction) {
		vUnit.clear();
		vUnit = UNITMANAGER->GetUnits();

		isbuilding = false;


		// 특정 태그만 타겟팅
		int player_rc_centerX;
		int player_rc_centerY;
		for (int i = 0; i < vUnit.size(); i++) {
			if ((*vUnit[i]).tag == TAG::PLAYER) {
				player_rc_centerX = vUnit[i]->rc.left + (vUnit[i]->rc.right - vUnit[i]->rc.left) / 2;
				player_rc_centerY = vUnit[i]->rc.top + (vUnit[i]->rc.bottom - vUnit[i]->rc.top) / 2;
				break;
			}
		}

		for (int i = 0; i < vUnit.size(); i++) {
			RECT t_rc = (*vUnit[i]).rc;
			int t_rc_centerX = t_rc.left + (t_rc.right - t_rc.left) / 2;
			int t_rc_centerY = t_rc.top + (t_rc.bottom - t_rc.top) / 2;
			int distancePO = ABS(getDistance(t_rc_centerX, t_rc_centerY, player_rc_centerX, player_rc_centerY));
			if (distancePO <= MAXTOUCHDISTANCE) {
				if ((*vUnit[i]).tag == TAG::OBJECT || (*vUnit[i]).tag == TAG::ENEMY || (*vUnit[i]).tag == TAG::NPC) {
					if (PtInRect(&t_rc, CAMERA->GetMouseRelativePos(_ptMouse))) {
						_targetingBox.SetTarget(t_rc, 3, i, 2, true);
						_unit = &(*vUnit[i]);
						return;
					}
				}
				if ((*vUnit[i]).tag == TAG::BUILDING) {
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

		}


		_unit = nullptr;
		_targetingBox.RemoveTarget();
	}
}