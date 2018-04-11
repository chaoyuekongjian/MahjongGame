#ifndef _MAHJONGPOOL_H_
#define _MAHJONGPOOL_H_
#include <vector>
#include <assert.h>
#include "Player.h"
#include <iostream>
#include <time.h>
//#include "cocos2d.h"
using std::vector;

#define PLAYER_NOTIFICATION              "PLAYER_NOTIFICATION"
#define PLAYER_NOTIFICATION_DELETE       "PLAYER_NOTIFICATION_DELETE"
#define PLAYER_NOTIFICATION_CHANGE       "PLAYER_NOTIFICATION_CHANGE"
#define ENEMY_NOTIFICATION               "ENEMY_NOTIFICATION"
#define ENEMY_NOTIFICATION_DELETE        "ENEMY_NOTIFICATION_DELETE"
#define ENEMY_NOTIFICATION_CHANGE        "ENEMY_NOTIFICATION_CHANGE"

enum Status               //控制流程
{
	GAME_BEGIN       = -1,
	PLAYER_ENABLE    = 0,
	PLAYER_BEGIN     = 1,
	PLYAER_MID       = 2,
	ENEMY_ENABLE     = 3,
	ENEMY_END        = 4,
	ENEMY_MID        = 5
};

//麻将池
class CMahjongManager
{
public:
	CMahjongManager();
	static CMahjongManager& GetInstance();
	virtual ~CMahjongManager();


	void FillMahjong();
	int GetVectSize();
	int DispatchMahjong();
	bool CheckVectEmpty();// 检测牌组是否为空

	void ResetStatus();
	void ChangeStatus();
	void BackStatus();
	int GetStatus();

	//------------------------------测试处理---------------------------------------------
	vector<int> GetMahjongVect();
	void SwapVect(int nIndexFir, int nIndexSec);
	
private:
	vector<int> m_vectMahjong;
	vector<int> m_vectMahjongQiang;
	vector<int> m_vectMahjongDel;
	CPlayer m_playerUser;

	int m_nStatus;
	bool m_bControl;
};

#endif