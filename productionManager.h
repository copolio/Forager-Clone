#pragma once
#include "singletonBase.h"
struct tagProduction
{
	RECT rc;
	string image_name;
	int count;
	int alpha;
	bool countStart;
	

};

class productionManager :public singletonBase<productionManager>
{

private:
	vector<tagProduction*>  _production;

	int count;
	
	RECT Myrc;
private:
	void count_increase();
	int isCilck(RECT rc);


public:
	void settion(RECT rc);
	void init();
	void relese();
	void update();
	void render(HDC hdc);
	
	
	vector<tagProduction*> getProduction() {
		return _production;
	};

public:

	void getRc(RECT _rc) {
		Myrc = _rc;
	}
	void isCount( string name);
	bool is_Item_Cilck(string name);

	void removeBuildingRc(RECT rc);
};

