#include "MahjongLayer.h"



bool CMahjongLayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();
	setContentSize(Size(winSize.width * 7 / 8, winSize.height * 7 / 8)); // 896  672
	setPosition(Vec2(winSize.width / 16, winSize.height / 16));

	Sprite *sprite = Sprite::create("ToolsBack.png");
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(0, 120));
	addChild(sprite);

	Menu *pMenu = Menu::create();
	pMenu->setPosition(Point::ZERO);
	addChild(pMenu);

	m_pItemSpriteCur = NULL;

	std::vector<int> vectData = CMahjongManager::GetInstance().GetMahjongVect();
	SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();
	m_nVectSize = vectData.size();
	for (int i = 0; i < vectData.size(); i++)
	{
		SpriteFrame *pSpriteFrame = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png", vectData.at(i))->getCString());
		MenuItemSprite *pItemSprite = MenuItemSprite::create(Sprite::createWithSpriteFrame(pSpriteFrame), NULL, CC_CALLBACK_1(CMahjongLayer::MenuCallBack, this));
		pItemSprite->setScale(0.7);
		pItemSprite->setAnchorPoint(Vec2(0, 0));
		pItemSprite->setPosition(Vec2(10 + 60 * (i % 14), 400 - 100 * (i / 14)));
		pItemSprite->setTag(i);
		pMenu->addChild(pItemSprite);
		m_vectItemSprite.pushBack(pItemSprite);
	}

	scheduleUpdate();

	return true;
}


void CMahjongLayer::update(float dt)
{
	if (m_nVectSize != CMahjongManager::GetInstance().GetMahjongVect().size())
	{
		MenuItemSprite *pItemSprite = m_vectItemSprite.at(m_vectItemSprite.size() - 1);
		m_vectItemSprite.popBack();
		pItemSprite->removeFromParent();

		m_nVectSize = CMahjongManager::GetInstance().GetMahjongVect().size();
		m_pItemSpriteCur = NULL;
	}

}

void CMahjongLayer::MenuCallBack(Ref *pSender)
{
	MenuItemSprite *pItemSprite = (MenuItemSprite *)pSender;
	if (pItemSprite == m_pItemSpriteCur)
	{
		m_pItemSpriteCur = NULL;
		log("MenuItem = %d", ((MenuItemSprite *)pSender)->getTag());
		return;
	}

	if (m_pItemSpriteCur != NULL && m_pItemSpriteCur != pItemSprite)
	{
		Point pointFir = pItemSprite->getPosition();
		Point pointSec = m_pItemSpriteCur->getPosition();
		m_pItemSpriteCur->setPosition(pointFir);
		pItemSprite->setPosition(pointSec);

		int nTagCur = m_pItemSpriteCur->getTag();
		int nTagSpr = pItemSprite->getTag();
		m_pItemSpriteCur->setTag(nTagSpr);
		pItemSprite->setTag(nTagCur);
		m_vectItemSprite.swap(nTagCur, nTagSpr);
		CMahjongManager::GetInstance().SwapVect(m_pItemSpriteCur->getTag(), pItemSprite->getTag());

		m_pItemSpriteCur = NULL;
		return;
	}


	m_pItemSpriteCur = pItemSprite;
}


