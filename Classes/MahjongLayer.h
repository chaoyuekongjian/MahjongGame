#ifndef _CMAHJONGLAYER_H_
#define _CMAHJONGLAYER_H_


#include "cocos2d.h"
#include "Mahjong\MahjongManager.h"

USING_NS_CC;

class CMahjongLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(CMahjongLayer);
	virtual bool init();
	virtual void update(float dt);

	void MenuCallBack(Ref *pSender);
private:
	int m_nVectSize;

	Vector<MenuItemSprite *> m_vectItemSprite;

	MenuItemSprite *m_pItemSpriteCur;
};


#endif