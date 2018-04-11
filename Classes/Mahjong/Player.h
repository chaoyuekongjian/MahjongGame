#ifndef _CPLAYER_H_
#define _CPLAYER_H_
#include "Hand.h"
#include "Actions.h"
#include <iostream>
using namespace std;

class CPlayer
{
	enum type
	{
		TYPE_NONE = 0,
		TYPE_GANG = 1,
		TYPE_PENG = 2,
		TYPE_CHI  = 3,
	};
public:
	CPlayer();
	virtual ~CPlayer();

	void CheckMahjong(int nValue, int nIndex = -1);

	void DoMahjong();
	void DoMahjongChi(int nIndex);
	void DoMahjongPeng(int nValue);
	void DoMahjongGang(int nValue);
	void DoMahjongGangAn(int nValue);
	
	bool HaveHuMahjong();
	void DoMahjongHu();
	void MahjongPrint();

	CHand& GetPlayerHand();
	CActions& GetPlayerActions();
	int GetMahjongType();
	
	CPlayer& operator = (const CPlayer &player);

private:
	CHand m_playerHand;
	CActions m_playerAction;

	int m_nMahjongType;                          //吃牌杠牌碰牌的三种类型
	int m_nMahjongValue;
	//int m_nMahjongIndex;                        //吃牌vect中的位置

};

#endif