#ifndef _CMAHJONGFANLAYER_H_
#define _CMAHJONGFANLAYER_H_

#include "cocos2d.h"
#include "Mahjong\Player.h"
#include "Mahjong\MahjongManager.h"

USING_NS_CC;

class CMahjongFanLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(CMahjongFanLayer);
	virtual bool init();
	
	static CMahjongFanLayer* create(CPlayer player);

private:
	CPlayer m_plyaer;

};




#endif