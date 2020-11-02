#include "stdafx.h"
#include "cursor.h"
#include "earth.h"
#include "quick_slot.h"
void cursor::init()
{
	vUnit = UNITMANAGER->GetUnits();
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
		if (_unit->objKey != "fishtrap") {
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
	itemPush();

}

void cursor::render(HDC hdc)
{
	if (CAMERA->movelimit) {
		_targetingBox.render(hdc);
		if (isbuilding) {
			if (_unit->objKey != "fishtrap") {
				IMAGEMANAGER->render("BuildingInteractionE", hdc,
					CAMERA->GetRelativeX(_unit->GetCenterX() - 20),
					CAMERA->GetRelativeY(_unit->GetCenterY() - 20));
			}
		}
		if (interaction) {
			UPGRADEMANAGER->targertrender(hdc, vUnit[number]->objKey);
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
						if (_unit->objKey != "bridge" && _unit->objKey != "tombLeft" && _unit->objKey != "tombRight") {
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

void cursor::itemPush()
{
	vector<unit*> t_vUnit = UNITMANAGER->GetUnits();
	for (int i = 0; i < t_vUnit.size(); i++) {
		if (t_vUnit[i]->tag == TAG::ITEM) {
			/*POINT camera_Mouse;
			camera_Mouse.x = CAMERA->GetRelativeX(_ptMouse.x);
			camera_Mouse.y = CAMERA->GetRelativeX(_ptMouse.y);*/
			RECT item = RectMake(CAMERA->GetRelativeX(t_vUnit[i]->rc.left), CAMERA->GetRelativeY(t_vUnit[i]->rc.top), (t_vUnit[i]->rc.right - t_vUnit[i]->rc.left), (t_vUnit[i]->rc.bottom - t_vUnit[i]->rc.top));
			if (PtInRect(&item, _ptMouse))
			{
				SOUNDMANAGER->play("아이템충돌");
				t_vUnit[i]->collision();
				TEXTMANAGER->AppearItemText(t_vUnit[i]->dropItem.itemKey);
				// 인벤토리에 아이템 추가 (키값ex : treeDrop, berryDrop)
				tagItem item = DATABASE->GetItem(t_vUnit[i]->dropItem.itemKey);
				if (item.itemType == ItemType::EQUIPMENT) {
					ITEMMANAGER->vequip_push(t_vUnit[i]->dropItem.itemKey);
					_quick->quick_slot_update();
				}
				else {
					ITEMMANAGER->vItem_push(t_vUnit[i]->dropItem.itemKey);
					_quick->quick_slot_update();
				}
				_quick->quick_slot_update();
			}
			
		}
	}
}