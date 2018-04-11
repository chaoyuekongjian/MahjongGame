#include "MahjongMenuImage.h"
USING_NS_CC;

CMahjongMenuImage::~CMahjongMenuImage()
{

}

bool CMahjongMenuImage::init()
{


	return true;
}

CMahjongMenuImage* CMahjongMenuImage::create(int nIndex)
{
	CMahjongMenuImage *pMenuImage = new (std::nothrow) CMahjongMenuImage();
	SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();
	SpriteFrame *pSpriteFrame = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png", nIndex)->getCString());
	//SpriteFrame *pSpriteFrameDis = pSpriteFrameCache->spriteFrameByName(CCString::create("Mahjong_back.png")->getCString());
	pMenuImage->initWithNormalSprite(Sprite::createWithSpriteFrame(pSpriteFrame), NULL, NULL, (const ccMenuCallback&)nullptr);
	pMenuImage->setScale(0.7);
	//pMenuImage->setAnchorPoint(Vec2(0.5, 0));
	pMenuImage->m_nIndex = nIndex;
	if (pMenuImage && pMenuImage->init())
	{
		pMenuImage->autorelease();
		return pMenuImage;
	}

	CC_SAFE_DELETE(pMenuImage);
	return nullptr;
}


int CMahjongMenuImage::GetIndex()
{
	return m_nIndex;
}



