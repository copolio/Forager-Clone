#pragma once
#include "singletonBase.h"
class DialogueManager : public singletonBase<DialogueManager>
{
private:
	struct tagDialogue {
		RECT* rc;
		string str;
		vector<string> vDialogueText;
		int currentLine;
		int count;
		int currentLineTextIndex;
		int waitTime;
	};

	vector<tagDialogue> _vDialogues;

	int TextSpeed = 3;
	
public:
	void update();
	void render(HDC hdc);
	
	void ShowDialogue(vector<string> p_str, RECT* p_pRC);


};

