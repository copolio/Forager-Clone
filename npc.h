#pragma once
#include "unit.h"
class npc : public unit
{
private:
	RECT* _rcPlayer;
	image* _img;
	bool _isQuestReceive;
	bool _isQuestComplete;
	bool _isNearPlayer;
	bool _canDialogue;
	vector<string> _vDialogueNormal;
	vector<string> _vDialogueQuestGive;
	vector<string> _vDialogueQuestComplete;
	int _currentWaitCount;
	int _waitCount;
	string _QuestRewardItem;
	string _QuestItem;
	int _questNeedItemNum;


public:
	void setNpc(string p_imgKey, POINT p_ptPos, RECT* p_rcPlayer);
	void update() override;
	void render(HDC hdc) override;
	void hurt(int damage) override;

	bool get_isQuestReceive() {
		return _isQuestReceive;
	}
  
	bool get_isQuestComplete() {
		return _isQuestComplete;
	}

	void set_isQuestReceive(bool receive) {
		_isQuestReceive = receive;
	}

	void set_isQuestComplete(bool complete) {
		_isQuestComplete = complete;
	}

private:
	void animation();
	void checkNearPlayer();
	void showDialogue();
	void countTimer();
};

