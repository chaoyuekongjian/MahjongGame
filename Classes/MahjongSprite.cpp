#include "MahjongSprite.h"

CMahjongSprite::CMahjongSprite()
{

}

CMahjongSprite* CMahjongSprite::create(int nIndex)
{
	CMahjongSprite *pSprite = new CMahjongSprite();
	CCSpriteFrameCache *pSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSpriteFrame *pSpriteFrame = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png",nIndex)->getCString());
	pSprite->initWithSpriteFrame(pSpriteFrame); 
	pSprite->setAnchorPoint(ccp(0, 0));
	pSprite->setScale(0.15);



	return pSprite;
}

void  CMahjongSprite::onEnter()
{
	EventListenerTouchOneByOne *pListener = EventListenerTouchOneByOne::create();
	//pListener->setSwallowTouches(true);
	pListener->onTouchBegan = CC_CALLBACK_2(CMahjongSprite::ccTouchBegan, this);
	pListener->onTouchEnded = CC_CALLBACK_2(CMahjongSprite::ccTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
	
	CCSprite::onEnter();
}

void  CMahjongSprite::onExit()
{


	CCSprite::onExit();
}

static bool nStatus = true;
//54 70.65
bool CMahjongSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (nStatus)
	{
		
		CCPoint pointSprite = this->getPosition();
		CCPoint pointTouch = pTouch->getLocation();
		if (pointTouch.x >= pointSprite.x && pointTouch.x < pointSprite.x + 54)
		{
			if (pointTouch.y >= pointSprite.y && pointTouch.y < pointSprite.y + 70.65)
			{
				nStatus = false;
				this->setPosition(ccp(pointSprite.x, pointSprite.y + 30));
			}
		}
	}
	
	return true;
}

void CMahjongSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!nStatus)
	{
		nStatus = true;
		CCPoint pointSprite = this->getPosition();
		CCPoint pointTouch = pTouch->getLocation();
		
		this->setPosition(ccp(pointSprite.x, pointSprite.y - 30));

	}
}
