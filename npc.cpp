#include "stdafx.h"
#include "npc.h"


void npc::setNpc(string p_imgKey, POINT p_ptPos, RECT* p_rcPlayer)
{
	tileIndex = 0;

	// 키 셋팅
	objKey = p_imgKey;
	_img = IMAGEMANAGER->findImage("David");

	// Object 정보 셋팅
	tag = TAG::NPC;
	layer = LAYER::OBJECT;
	x = p_ptPos.x;
	y = p_ptPos.y;
	rc = RectMakeCenter(x, y, 56, 56);

	// 스테이터스 셋팅
	maxHp = 9999;
	currentHp = maxHp;

	// 플레이어 파싱.
	_rcPlayer = p_rcPlayer;

	// NPC 셋팅
	_isNearPlayer = false;
	_isQuestReceive = false;
	_isQuestComplete = false;
	_canDialogue = true;

	_vDialogueNormal.push_back("내가 마실 물이 없어서 그런데...");
	_vDialogueNormal.push_back("나무 열매 10개만 가져다 주면 안 될까?");
	_vDialogueQuestGive.push_back("나무 열매 10개만 가져다 줘");
	_vDialogueQuestComplete.push_back("휴우 덕분에 살았어.");

	// 퀘스트 관련 아이템 (NPC 추가시 자식 클래스에서)
	_QuestRewardItem = "slot_Bow";
	_QuestItem = "berryDrop";
	_questNeedItemNum = 10;

	// 애니메이션 셋팅
	objFrameX = 0;
	objFrameY = 0;
	objMaxFrameX = 4;
	objMaxFrameY = 1;

	currentCount = 0;
	nextCount = 5;

	_currentWaitCount = 0;
	_waitCount = 400;
}

void npc::update()
{
	animation();		// 애니메이션
	checkNearPlayer();	// 플레이어 주변 체크
	showDialogue();		// 말풍선 출력
	countTimer();		// 중복 방지 다이얼로그 타이머 
}

void npc::render(HDC hdc)
{
	int relX = CAMERA->GetRelativeX(rc.left - 25);
	int relY = CAMERA->GetRelativeY(rc.top - 25);
	_img->frameRender(hdc, relX, relY, objFrameX, objFrameY, CAMERA->GetZoom());

	if (_isNearPlayer && _canDialogue) {
		POINT t_ptRelMouse = CAMERA->GetMouseRelativePos(_ptMouse);
		if (abs(GetCenterX() - t_ptRelMouse.x) <= 30 && abs(GetCenterY() - t_ptRelMouse.y) <= 30)
		{
			IMAGEMANAGER->render("E", hdc, relX + 40, relY - 20, CAMERA->GetZoom());
		}
	}
}

void npc::hurt(int damage)
{
	vector<string> str;
	str.push_back("아... 아파...");
	DIALOGUE->ShowDialogue(str, &rc);
}


void npc::animation()
{
	if (currentCount++ > nextCount) {
		currentCount = 0;
		if (objFrameX++ >= objMaxFrameX)
			objFrameX = 0;
	}
}

void npc::checkNearPlayer()
{
	if (abs(_rcPlayer->left - rc.left) <= 80 && abs(_rcPlayer->top - rc.top) <= 80)
		_isNearPlayer = true;
	else
		_isNearPlayer = false;
}

void npc::showDialogue()
{
	if (_isNearPlayer && _canDialogue) {

		if (INPUT->GetKeyDown('E')) {


			// 퀘스트 받기 전
			if (!_isQuestReceive) {
				DIALOGUE->ShowDialogue(_vDialogueNormal, &rc);
				_isQuestReceive = true;
			}
			// 퀘스트 받은 후
			else if (!_isQuestComplete) {

				// 퀘스트 완수
				if (ITEMMANAGER->Item_count_Minus(_QuestItem, 5)) {
					_isQuestComplete = true;
					DIALOGUE->ShowDialogue(_vDialogueQuestComplete, &rc);

					UNITMANAGER->AddProduction(_QuestRewardItem, { rc.left - 50, rc.bottom + 50 });
				}

				// 퀘스트 진행중
				else 
					DIALOGUE->ShowDialogue(_vDialogueQuestGive, &rc);
			}
			// 퀘스트 클리어 후
			else 
				DIALOGUE->ShowDialogue(_vDialogueQuestComplete, &rc);
			
			_canDialogue = false; // 중복 대화 방지
		}
	}
}

void npc::countTimer()
{
	if (!_canDialogue) {
		if (_currentWaitCount++ > _waitCount) {
			_canDialogue = true;
			_currentWaitCount = 0;
		}
	}
}
