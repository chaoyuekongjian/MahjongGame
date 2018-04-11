#include "TimeSprite.h"




CTimeSprite* CTimeSprite::create()
{
	CTimeSprite *sprite = new (std::nothrow) CTimeSprite();

	Animation *runAnimation = Animation::create();
	SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();
	Sprite *pBacSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("Clock.jpg"));
	pBacSprite->setPosition(Vec2(100, 10));
	pBacSprite->setScale(0.3);
	

	for (int i = 9; i > -1; i--)
	{
		SpriteFrame *pSpriteFrame = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("0%d.jpg", i)->getCString());
		runAnimation->addSpriteFrame(pSpriteFrame);
	}
	runAnimation->setDelayPerUnit(1.0f);
	Sprite *pMySprite = Sprite::create();
	pMySprite->setScale(0.5);
	pMySprite->setPosition(Vec2(100, 10));
	
	pMySprite->runAction(RepeatForever::create(Animate::create(runAnimation)));

	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}