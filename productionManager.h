#pragma once

struct tagProduction
{
	RECT rc;
	string image_name;
	int count;
	int alpha;
	bool countStart;
	

};

class productionManager
{

private:
	vector<tagProduction*>  _production;

	int count;
public:
	void settion(RECT rc);
	void init();
	void relese();
	void update();
	void render(HDC hdc);
	
	void count_increase();
	vector<tagProduction*> getProduction() {
		return _production;
	};

public:

	int isCilck(RECT rc);
	void isCount(RECT rc);
};

