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
private:
	void animation();
	void checkNearPlayer();
	void showDialogue();
	void countTimer();

};

