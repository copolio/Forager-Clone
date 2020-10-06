#pragma once
#include "targetingBox.h"
#include "industry.h"
#include "Agriculture.h"

enum CONSTRUCTIONKIND
{
	INDUSTRY,
	AGRICULTURE,
};

struct Con_Info
{
	CONSTRUCTIONKIND kind;
	RECT rc;
	bool isInfo;
};

class construction
{
private:
	targetingBox *_targetBox;
	vector<Con_Info*> _industry_Rc;
	industry* _industry;
	Agriculture* _agriculture;
	bool isCheck;
	bool agrocultureCheck;
	bool isTargetBox;
public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void BoxMove();
	void mouse_targetBox();

	void mouse_Click();

	void setIsCheck(bool check) {
		isCheck = check;
	}

	void setisTargetBox(bool check) {
		isTargetBox = check;
	}
public:
	void setInMapLink(earth* map) { _industry->setInMapLink(map); };
};

