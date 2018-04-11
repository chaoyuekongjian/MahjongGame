#ifndef _MAHJONGSPRITE_H_
#define _MAHJONGSPRITE_H_
#include "cocos2d.h"
USING_NS_CC;

class CMahjongSprite : public Sprite , public EventListenerMouse
{
public:
	CMahjongSprite();
	virtual void onEnter();
	virtual void onExit();
	static CMahjongSprite* create(int nIndex);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

private:
	
	

};



#endif