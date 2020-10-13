#pragma once
#include "earth.h"

#define MAX_X MAPTILEX
#define MAX_Y MAPTILEY

//노드상태
enum NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_WALL,
	NODE_EMPTY
};

//노드 클래스
class node
{
public:
	RECT rc;				//렉트
	int idx, idy;			//인덱스
	int F, G, H;			//F = G + H, G => 시작 to 현재, H = 현재 to 종료
	node* parentNode;		//부모를 가리킬 노드(이전 노드)
	NODESTATE nodeState;	//노드상태 (시작, 종료, 벽, 빈노드)

	//노드 생성자
	node() {}
	//노드 생성자 (생성자 오버로딩)
	node(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		nodeState = NODE_EMPTY;
		parentNode = NULL;
	}
};


class Astar
{
private:
	vector<tile> _vTiles;
private:
	node* _totalNode[MAPTILEX][MAPTILEY];		//전체노드 25개(보드판 역할)
	node* _startNode;					//시작노드
	node* _endNode;						//종료노드
	node* _curNode;						//현재노드

	vector<node*> _openList;			//오픈리스트 (탑색할 노드들을 담아둘 벡터)
	vector<node*> _closeList;			//길을 찾은 노드들을 담아둘 벡터
	//vector<node*> _finalList;			//클로즈리스트에 담겨있는 노드들을 리버스시켜서 담아둘 벡터
	vector<int> _finalList;			//클로즈리스트에 담겨있는 노드들을 리버스시켜서 담아둘 벡터

public:
	void init(vector<tile> vTile);

	/*중요함수*/
	//길찾기 함수
	vector<int> pathFinding(vector<tile> vTile, int startidx, int endidx, bool checkwall=true, bool checkdiagonal=true);
	//오픈리스트 추가
	void addOpenList(int idx, int idy);
	//오픈리스트 삭제
	void delOpenList(int index);
};

