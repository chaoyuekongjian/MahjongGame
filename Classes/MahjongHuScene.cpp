#include "MahjongHuScene.h"
#include "HelloWorldScene.h"
#include "UTFManager.h"



CMahjongHuScene::CMahjongHuScene()
{
	m_nMahjongFan = 0;
	m_sMahjongName = "";
}

cocos2d::Scene* CMahjongHuScene::createScene()
{
	
	return CMahjongHuScene::create();
}

bool CMahjongHuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	Sprite *pBackSprite = Sprite::create("MahjongFan.png");
	pBackSprite->setPosition(Vec2(0, 0));
	pBackSprite->setAnchorPoint(Vec2(0, 0));
	addChild(pBackSprite);
	
	return true;
}


void CMahjongHuScene::MenuCallBack(Ref *pSender)
{
	HelloWorld *pScene = HelloWorld::create();
	CMahjongManager::GetInstance().ResetStatus();
	CCTransitionFlipAngular *flipAngular = CCTransitionFlipAngular::create(1, pScene);
	Director::getInstance()->replaceScene(flipAngular);

}

void CMahjongHuScene::SetMahjongFan(int nNumber)
{
	m_nMahjongFan = nNumber;

}

void CMahjongHuScene::SetMahjongName(vector<string> vectMahjongName)
{
	if (!m_vectMahjongName.empty())
	{
		m_vectMahjongName.clear();
	}

	m_vectMahjongName.insert(m_vectMahjongName.begin(), vectMahjongName.begin(), vectMahjongName.end());
}

void CMahjongHuScene::onEnterTransitionDidFinish()
{
	MenuItemSprite *pItemSprite = MenuItemSprite::create(Sprite::create("Again.png"), NULL, CC_CALLBACK_1(CMahjongHuScene::MenuCallBack, this));
	pItemSprite->setPosition(150, 200);

	Menu *pMenu = Menu::create(pItemSprite, NULL);
	pMenu->setPosition(Point::ZERO);
	addChild(pMenu);

	log("%d", m_vectMahjongName.size());
	for (int i = 0; i < m_vectMahjongName.size(); i++)
	{
		LabelTTF *pLabelTTF = LabelTTF::create(CCString::createWithFormat("%s", CUTFManager::GetInstance().GbkToUtf8(m_vectMahjongName.at(i)).c_str())->getCString(), "", 20);
		pLabelTTF->setPosition(Vec2(100 + 100 * (i % 3), 450 - 50 * (i / 3)));
		pLabelTTF->setColor(ccColor3B(186, 85, 211));
		addChild(pLabelTTF);
	}
	

	LabelTTF *pLabelTTFFan = LabelTTF::create(CCString::createWithFormat("%d", m_nMahjongFan)->getCString(), "", 40);
	pLabelTTFFan->setPosition(Vec2(100, 500));
	pLabelTTFFan->setColor(ccColor3B(220, 20, 60));
	addChild(pLabelTTFFan);

}