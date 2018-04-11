#include "PlayerLayer.h"
#include <algorithm>

static bool SortByIndex(CMahjongMenuImage *pImageFir, CMahjongMenuImage *pImageSec)
{
	if (pImageFir->GetIndex() < pImageSec->GetIndex())
	{
		return true;
	}
	return false;
}


CPlayerLayer::~CPlayerLayer()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool CPlayerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_pCurImage = NULL;
	m_bIsFilled = false;
	m_bIsTing = false;
	m_bChoseTing = false;
	m_bIsAnimateEnd = true;
	m_nMahjongNumber = 0;
	m_nTingStatus = 0;
	m_nTimeStatus = 0;

	Size winSize = Director::getInstance()->getWinSize();
	setContentSize(Size(winSize.width, winSize.height / 4));
	setPosition(Vec2(0, winSize.height / 8));
	
	Menu *pMenu = Menu::create();
	pMenu->setTag(1000);
	pMenu->setPosition(Point::ZERO);
	addChild(pMenu);
	scheduleUpdate();

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(CPlayerLayer::NotiCallBack), ENEMY_NOTIFICATION, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(CPlayerLayer::DeleteCallBack), ENEMY_NOTIFICATION_DELETE, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(CPlayerLayer::TingCallBack), PLAYER_NOTIFICATION_CHANGE, NULL);

	m_pSequencePlayer = Sequence::create(CallFuncN::create(CC_CALLBACK_1(CPlayerLayer::TimeCallBack, this)), DelayTime::create(10.0f), CallFuncN::create(CC_CALLBACK_1(CPlayerLayer::TimeCallBack, this)), NULL);
	m_pSequencePlayer->retain();

	m_pSequenceTing = Sequence::create(NULL);


	/*MenuItemSprite *pMenuItem = MenuItemSprite::create(Sprite::create("Hu.png"), NULL, CC_CALLBACK_1(CPlayerLayer::HufanCallBack, this));
	pMenuItem->setPosition(Vec2(984, 100));
	pMenu->addChild(pMenuItem);*/

	return true;
}


void CPlayerLayer::onEnter()
{
	EventListenerTouchOneByOne *pListener = EventListenerTouchOneByOne::create();
	//pListener->setSwallowTouches(true);
	pListener->onTouchBegan = CC_CALLBACK_2(CPlayerLayer::ccTouchBegan, this);
	pListener->onTouchEnded = CC_CALLBACK_2(CPlayerLayer::ccTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);

	Layer::onEnter();	
}

void CPlayerLayer::onExit()
{
	_eventDispatcher->removeAllEventListeners();

	Layer::onExit();
}

void CPlayerLayer::update(float dt)
{
	if (PLAYER_ENABLE == CMahjongManager::GetInstance().GetStatus())
	{
		if (CMahjongManager::GetInstance().CheckVectEmpty())
		{
			CMahjongHuScene *pScene = CMahjongHuScene::create();
			TransitionFlipAngular *flipAngular = TransitionFlipAngular::create(1, pScene);
			pScene->SetMahjongFan(0);
			std::vector<string> vectName;
			vectName.push_back("流局");
			pScene->SetMahjongName(vectName);
			Director::getInstance()->replaceScene(flipAngular);
			return;
		}

		CMahjongManager::GetInstance().ChangeStatus();
		CMahjongMenuImage *pNewImage = CMahjongMenuImage::create(CMahjongManager::GetInstance().DispatchMahjong());
		m_vectImageNode.pushBack(pNewImage);
		m_nMahjongNumber = pNewImage->GetIndex();
		Menu *pMenu = (Menu*)this->getChildByTag(1000);

		pNewImage->setPosition(Vec2(210 + 50 * (m_vectImageNode.size() - 1), 85));
		MoveTo *pMoveTo = MoveTo::create(0.3, Vec2(210 + 50 * (m_vectImageNode.size() - 1), 15));
		pNewImage->runAction(pMoveTo);
		pNewImage->initWithCallback(CC_CALLBACK_1(CPlayerLayer::MenuCallBack, this));
		pMenu->addChild(pNewImage);
		runAction(m_pSequencePlayer);
		
		static double dTime = 0;
		struct timeval tv;
		gettimeofday(&tv, nullptr);
		if (dTime != (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000)
		{
			log("timeDistance = %f", (dTime - (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000) / 1000.0);
		}
		log("CurrentTime MillSecond %f", (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000);
		dTime = (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
		
		int nTime = 0;
		for (int i = 0; i < m_vectImageOther.size() - 2; i++)
		{
			if (m_vectImageOther.at(i)->GetIndex() == m_nMahjongNumber                             &&
				m_vectImageOther.at(i)->GetIndex() == m_vectImageOther.at(i + 1)->GetIndex() &&
				m_vectImageOther.at(i + 1)->GetIndex() == m_vectImageOther.at(i + 2)->GetIndex())
			{
				MenuItemSprite *pItemSpriteGang = MenuItemSprite::create(Sprite::create("MahjongGang.png"), NULL, CC_CALLBACK_1(CPlayerLayer::MenuGangCallBack, this));
				pItemSpriteGang->setScale(0.5);
				pItemSpriteGang->setTag(PALYER_PENG_GANG);
				pItemSpriteGang->setPosition(Vec2(400, 100));
				pMenu->addChild(pItemSpriteGang);
				nTime = 8;
				break;
			}
		}

		if (m_userPlayer.GetPlayerHand().CheckMahjongGang(pNewImage->GetIndex()))
		{
			if (!(m_bIsTing && m_bChoseTing))
			{
				MenuItemSprite *pItemSpriteGang = MenuItemSprite::create(Sprite::create("MahjongGang.png"), NULL, CC_CALLBACK_1(CPlayerLayer::MenuGangCallBack, this));
				pItemSpriteGang->setScale(0.5);
				pItemSpriteGang->setTag(PLAYER_SELF_GANG);
				pItemSpriteGang->setPosition(Vec2(400, 100));
				pMenu->addChild(pItemSpriteGang);
				nTime = 8;
			}
			else
			{
				vector<int> vectMahjong;
				vectMahjong = m_userPlayer.GetPlayerHand().CheckMahjongTing();
				m_userPlayer.GetPlayerHand().DeleteMahjong(pNewImage->GetIndex());
				m_userPlayer.GetPlayerHand().DeleteMahjong(pNewImage->GetIndex());
				m_userPlayer.GetPlayerHand().DeleteMahjong(pNewImage->GetIndex());
				vector<int> vectMahjongCur;
				vectMahjongCur = m_userPlayer.GetPlayerHand().CheckMahjongTing();
				if (vectMahjong.size() != vectMahjongCur.size())
				{
					m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());
					m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());
					m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());

				}
				else
				{
					for (int i = 0; i < vectMahjong.size(); i++)
					{
						if (vectMahjong.at(i) != vectMahjongCur.at(i))
						{
							m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());
							m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());
							m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());
							
							break;
						}
						if (i == vectMahjong.size() - 1)
						{
							m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());
							m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());
							m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());

							MenuItemSprite *pItemSpriteGang = MenuItemSprite::create(Sprite::create("MahjongGang.png"), NULL, CC_CALLBACK_1(CPlayerLayer::MenuGangCallBack, this));
							pItemSpriteGang->setScale(0.5);
							pItemSpriteGang->setTag(PLAYER_SELF_GANG);
							pItemSpriteGang->setPosition(Vec2(400, 100));
							pMenu->addChild(pItemSpriteGang);
							nTime = 8;
						}
					}
				}
			}
			
		}

		m_userPlayer.GetPlayerHand().HandAddMahjong(pNewImage->GetIndex());
		if (m_userPlayer.GetPlayerHand().CheckMahjongHu())
		{
			MenuItemSprite *pItemSpriteHu = MenuItemSprite::create(Sprite::create("MahjongHu.png"), NULL, CC_CALLBACK_1(CPlayerLayer::MenuHuCallBack, this));
			pItemSpriteHu->setScale(0.5);
			pItemSpriteHu->setTag(PLAYER_SELF_HU);
			pItemSpriteHu->setPosition(Vec2(560, 100));
			pMenu->addChild(pItemSpriteHu);
			nTime = 8;
		}

		m_pSequenceTing = Sequence::create(DelayTime::create(1.8 + nTime), CallFunc::create([=](){
			if (m_bIsTing && m_bChoseTing)
			{
				if (!m_userPlayer.GetPlayerHand().CheckMahjongHu())
				{
					m_userPlayer.GetPlayerHand().DeleteMahjong(pNewImage->GetIndex());
					m_vectImageNode.popBack();
					m_vectImageDel.pushBack(pNewImage);
					pNewImage->setScale(0.4);
					pNewImage->setEnabled(false);
					SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();
					SpriteFrame *pSpriteFrameDis = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png", pNewImage->GetIndex() + 100)->getCString());
					pNewImage->setDisabledImage(Sprite::createWithSpriteFrame(pSpriteFrameDis));

					if (14 > m_vectImageDel.size())
					{
						pNewImage->setPosition(Vec2(230 + m_vectImageDel.size() * 40, 270));
					}
					else
					{
						pNewImage->setPosition(Vec2(230 + (m_vectImageDel.size() - 13) * 40, 210));
					}

					NotificationCenter::getInstance()->postNotification(PLAYER_NOTIFICATION, (Ref *)pNewImage->GetIndex());
					CMahjongManager::GetInstance().ChangeStatus();

					Menu *pMenu = (Menu *)this->getChildByTag(1000);
					MenuItemSprite *pItemSpriteGang = (MenuItemSprite *)pMenu->getChildByTag(PALYER_PENG_GANG);
					if (NULL != pItemSpriteGang)
					{
						pItemSpriteGang->removeFromParent();
					}

					MenuItemSprite *pItemSpriteSelfGang = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_SELF_GANG);
					if (NULL != pItemSpriteSelfGang)
					{
						pItemSpriteSelfGang->removeFromParent();
					}

					MenuItemSprite *pItemSprite = (MenuItemSprite *)getChildByTag(PLAYER_TING);
					if (NULL != pItemSprite)
					{
						pItemSprite->removeFromParent();
					}

					if (!m_bIsAnimateEnd)
					{
						stopAction(m_pSequencePlayer);
						runAction(CallFuncN::create(CC_CALLBACK_1(CPlayerLayer::DeleCallBack, this)));
						m_nTimeStatus = 0;
					}

					//m_pSequenceTing->release();
				}
			}
		}), NULL);
		m_pSequenceTing->setTag(PLAYER_ANIMATION);

		if (m_bIsTing && m_bChoseTing)
		{
			runAction(m_pSequenceTing);
		}


		NotificationCenter::getInstance()->postNotification(PLAYER_NOTIFICATION_CHANGE);
		return;
	}


	for (int i = 0; i < m_vectImageOther.size(); i++)
	{
		m_vectImageOther.at(i)->setDisabledImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName(CCString::createWithFormat("%d.png", m_vectImageOther.at(i)->GetIndex())->getCString())));
		m_vectImageOther.at(i)->setEnabled(false);
	}

}


bool CPlayerLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	log("asdasdsadasdsa");

	return true;
}

void CPlayerLayer::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{


}

void CPlayerLayer::AddMenuSprite(CMahjongMenuImage *pMenuImage, Point point)
{
	pMenuImage->initWithCallback(CC_CALLBACK_1(CPlayerLayer::MenuCallBack, this));
	pMenuImage->setPosition(point);
	Menu *pMenu = (Menu*)this->getChildByTag(1000);
	m_userPlayer.GetPlayerHand().HandAddMahjong(pMenuImage->GetIndex());
	m_vectImageNode.pushBack(pMenuImage);
	pMenu->addChild(pMenuImage);
	pMenuImage->release();

	if (13 <= m_vectImageNode.size() && !m_bIsFilled)
	{
		m_bIsFilled = true;
		sort(m_vectImageNode.begin(), m_vectImageNode.end(), SortByIndex);
		SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();
		SpriteFrame *pSpriteFrameDis = pSpriteFrameCache->spriteFrameByName(CCString::create("Mahjong_back.png")->getCString());
		for (int i = 0; i < m_vectImageNode.size(); i++)
		{
			ScaleTo *pScaleTo = ScaleTo::create(0.5, 0.7, 0);
			ScaleTo *pScaleBack = ScaleTo::create(0.5, 0.7, 0.7);
			Sequence *pSequence = Sequence::create(DelayTime::create(0.5), pScaleTo, CallFunc::create([=](){
				m_vectImageNode.at(i)->setNormalImage(Sprite::createWithSpriteFrame(pSpriteFrameDis));
			}), ScaleTo::create(0.5, 0.7, -0.5), pScaleTo, CallFunc::create([=](){
				m_vectImageNode.at(i)->setPosition(200 + 50 * i, 15);
				SpriteFrame *pSpriteFrame = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png", m_vectImageNode.at(i)->GetIndex())->getCString());
				m_vectImageNode.at(i)->setNormalImage(Sprite::createWithSpriteFrame(pSpriteFrame));
			}), pScaleBack, NULL);
			m_vectImageNode.at(i)->runAction(pSequence);
		}

		Sequence *pSequenceChange = Sequence::create(DelayTime::create(2.5), CallFunc::create([=](){
			CMahjongManager::GetInstance().ChangeStatus();
		}), NULL);
		runAction(pSequenceChange);
	}
	
}

void CPlayerLayer::HufanCallBack(Ref *pSender)
{
	static int nMark = 0;
	if (0 == nMark)
	{
		CMahjongFanLayer *pLayer = CMahjongFanLayer::create(m_userPlayer);
		pLayer->setTag(PLAYER_HUFAN);
		addChild(pLayer);
		
		
		nMark++;
		return;
	}
	if (1 == nMark)
	{
		CMahjongFanLayer *pLayer = (CMahjongFanLayer *)getChildByTag(PLAYER_HUFAN);
		if (NULL != pLayer)
		{
			pLayer->removeFromParent();
		}

		nMark = 0;
	}
}


void CPlayerLayer::MenuCallBack(Ref *pSender)
{
	static int nMark = 0;
	CMahjongMenuImage *pMenuImage = (CMahjongMenuImage *)pSender;
	if (m_pCurImage != pMenuImage)
	{
		nMark = 1;
	}
	if (1 == nMark)
	{
		if (NULL == m_pCurImage)
		{
			pMenuImage->setPosition(Vec2(pMenuImage->getPosition().x, 15 + 15));
		} 
		if (pMenuImage != m_pCurImage && NULL != m_pCurImage)
		{
			pMenuImage->setPosition(Vec2(pMenuImage->getPosition().x,15 + 15));
			m_pCurImage->setPosition(Vec2(m_pCurImage->getPosition().x, 15));
		}

		nMark++;
		m_pCurImage = pMenuImage;

		return;
	}

	if (2 == nMark)
	{
		if (PLAYER_BEGIN == CMahjongManager::GetInstance().GetStatus())
		{
			if (!m_bIsAnimateEnd)
			{
				stopAction(m_pSequencePlayer);
				runAction(CallFuncN::create(CC_CALLBACK_1(CPlayerLayer::DeleCallBack, this)));
				m_nTimeStatus = 0;
			}
			

			Menu *pMenu = (Menu *)this->getChildByTag(1000);
			MenuItemSprite *pItemSpriteGang = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_SELF_GANG);
			if (NULL != pItemSpriteGang)
			{
				pItemSpriteGang->removeFromParent();
			}

			MenuItemSprite *pSpriteGang = (MenuItemSprite *)pMenu->getChildByTag(PALYER_PENG_GANG);
			if (NULL != pSpriteGang)
			{
				pSpriteGang->removeFromParent();
			}

			MenuItemSprite *pItemSpriteHu = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_SELF_HU);
			if (NULL != pItemSpriteHu)
			{
				pItemSpriteHu->removeFromParent();
			}

			MenuItemSprite *pItemSpriteTing = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_TING);
			if (NULL != pItemSpriteTing)
			{
				pItemSpriteTing->removeFromParent();
			}

			if (1 == m_nTingStatus)
			{
				m_nTingStatus--;
			}

			if (m_bIsTing && m_bChoseTing)
			{
				if (m_vectImageNode.at(m_vectImageNode.size() - 1) != m_pCurImage)
				{
					return;
				}
			}

			if (m_bIsTing && !m_bChoseTing)
			{
				for (int i = 0; i < m_vectTing.size(); i++)
				{
					if (m_vectTing.at(i) == m_pCurImage->GetIndex())
					{
						m_bChoseTing = true;
						MenuItemSprite *pMenuItemSprite = (MenuItemSprite *)pMenu->getChildByTag(PALYER_CANCEL);
						if (NULL != pMenuItemSprite)
						{
							pMenuItemSprite->removeFromParent();
						}

						MenuItemSprite *pMenuItem = MenuItemSprite::create(Sprite::create("Hu.png"), NULL, CC_CALLBACK_1(CPlayerLayer::HufanCallBack, this));
						pMenuItem->setPosition(Vec2(984, 100));
						pMenu->addChild(pMenuItem);

						break;
					}
					if (i == m_vectTing.size() - 1)
					{
						return;
					}
				}
			}

			for (int i = 0; i < m_vectTing.size(); i++)
			{
				Sprite *pSprite = (Sprite *)this->getChildByTag(10 + i);
				if (NULL != pSprite)
				{
					pSprite->removeFromParent();
				}
			}

			m_vectImageDel.pushBack(m_pCurImage);
			m_pCurImage->setScale(0.4);
			if (14 > m_vectImageDel.size())
			{
				m_pCurImage->setPosition(Vec2(230 + m_vectImageDel.size() * 40, 270));
			}
			else
			{
				m_pCurImage->setPosition(Vec2(230 + (m_vectImageDel.size() - 13) * 40, 210));
			}
			
			m_pCurImage->setEnabled(false);
			SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();
			SpriteFrame *pSpriteFrameDis = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png", m_pCurImage->GetIndex() + 100)->getCString());
			m_pCurImage->setDisabledImage(Sprite::createWithSpriteFrame(pSpriteFrameDis));

			for (int i = 0; i < m_vectImageNode.size(); i++)
			{
				if (m_vectImageNode.at(i) == m_pCurImage)
				{
					m_vectImageNode.erase(m_vectImageNode.begin() + i);
					break;
				}
			}

			CMahjongMenuImage *pLastMahjong = m_vectImageNode.at(m_vectImageNode.size() - 1);
			sort(m_vectImageNode.begin(), m_vectImageNode.end(), SortByIndex);
			for (int i = 0; i < m_vectImageNode.size(); i++)
			{
				if (m_vectImageNode.at(i) == pLastMahjong && i != m_vectImageNode.size() - 1)
				{
					Point point = pLastMahjong->getPosition();
					MoveTo *pMoveToFir = MoveTo::create(0.1, Vec2(point.x, 85));
					MoveTo *pMoveToSec = MoveTo::create(0.5, Vec2(point.x - 10 - 50 * (m_vectImageNode.size() - i), 85));
					MoveTo *pMoveToThr = MoveTo::create(0.1, Vec2(point.x - 10 - 50 * (m_vectImageNode.size() - i), 15));
					Sequence *pSequence = Sequence::create(pMoveToFir, pMoveToSec, pMoveToThr, NULL);
					pLastMahjong->runAction(pSequence);
					continue;
				}

				Point point = m_vectImageNode.at(i)->getPosition();
				int nDistance = abs(point.x - 200 + 50 * i);
				MoveTo *pMoveTo = MoveTo::create(0.2, Vec2(200 + 50 * i, 15));
				m_vectImageNode.at(i)->runAction(pMoveTo);
			}

			m_userPlayer.GetPlayerHand().DeleteMahjong(m_pCurImage->GetIndex());
			NotificationCenter::getInstance()->postNotification(PLAYER_NOTIFICATION, (Ref *)m_pCurImage->GetIndex());
			m_pCurImage = NULL;

			if (NULL != m_pSequenceTing)
			{
				stopAction(m_pSequenceTing);
			}

			CMahjongManager::GetInstance().ChangeStatus();
			return;
		}
		m_pCurImage->setPosition(Vec2(m_pCurImage->getPosition().x, 15));
		nMark = 0;
		m_pCurImage = pMenuImage;

		return;
	}
	if (0 == nMark)
	{
		m_pCurImage->setPosition(Vec2(m_pCurImage->getPosition().x, 15 + 15));
		nMark = 2;
		m_pCurImage = pMenuImage;

		return;
	}

}


void CPlayerLayer::NotiCallBack(Ref *pSender)
{
	//log("%d", (int)pSender);
	int nMark = 1;
	m_nMahjongNumber = (int)pSender;
	Menu *pMenu = (Menu *)this->getChildByTag(1000);

	if ((!m_userPlayer.GetPlayerHand().CheckMahjongChi(m_nMahjongNumber) && !m_userPlayer.GetPlayerHand().CheckMahjongPeng(m_nMahjongNumber) && !m_userPlayer.GetPlayerHand().CheckMahjongGang(m_nMahjongNumber)) || m_bIsTing)
	{
		m_userPlayer.GetPlayerHand().HandAddMahjong(m_nMahjongNumber);
		if (!m_userPlayer.GetPlayerHand().CheckMahjongHu())
		{
			m_userPlayer.GetPlayerHand().DeleteMahjong(m_nMahjongNumber);
			CMahjongManager::GetInstance().ChangeStatus();
			m_userPlayer.GetPlayerHand().CleanMahjongChi();
			m_userPlayer.GetPlayerHand().CleanMahjongGang();
			m_userPlayer.GetPlayerHand().CleanMahjongPeng();

			return;
		}
		else
		{
			m_userPlayer.GetPlayerHand().DeleteMahjong(m_nMahjongNumber);
		}
	}
	m_userPlayer.GetPlayerHand().CleanMahjongChi();
	m_userPlayer.GetPlayerHand().CleanMahjongGang();
	m_userPlayer.GetPlayerHand().CleanMahjongPeng();


	MenuItemSprite *pItemSpriteGuo = MenuItemSprite::create(Sprite::create("MahjongGuo.png"), NULL, CC_CALLBACK_1(CPlayerLayer::SpriteCallBack, this));
	pItemSpriteGuo->setScale(0.5);
	pItemSpriteGuo->setTag(PLAYER_GUO);
	pItemSpriteGuo->setPosition(Vec2(750, 100));
	pMenu->addChild(pItemSpriteGuo);

	if (!m_bIsTing)
	{
		m_nTimeStatus = 2;
		runAction(m_pSequencePlayer);
		
		if (m_userPlayer.GetPlayerHand().CheckMahjongChi(m_nMahjongNumber))
		{
			MenuItemSprite *pItemSpriteChi = MenuItemSprite::create(Sprite::create("MahjongChi.png"), NULL, CC_CALLBACK_1(CPlayerLayer::SpriteCallBack, this));
			pItemSpriteChi->setScale(0.5);
			pItemSpriteChi->setTag(PLAYER_CHI);
			pItemSpriteChi->setPosition(Vec2(750 - 80 * nMark, 100));
			pMenu->addChild(pItemSpriteChi);
			nMark++;
		}

		if (m_userPlayer.GetPlayerHand().CheckMahjongPeng(m_nMahjongNumber))
		{
			MenuItemSprite *pItemSpritePeng = MenuItemSprite::create(Sprite::create("MahjongPeng.png"), NULL, CC_CALLBACK_1(CPlayerLayer::SpriteCallBack, this));
			pItemSpritePeng->setScale(0.5);
			pItemSpritePeng->setTag(PLAYER_PENG);
			pItemSpritePeng->setPosition(Vec2(750 - 80 * nMark, 100));
			pMenu->addChild(pItemSpritePeng);
			nMark++;
		}

		if (m_userPlayer.GetPlayerHand().CheckMahjongGang(m_nMahjongNumber))
		{
			MenuItemSprite *pItemSpriteGang = MenuItemSprite::create(Sprite::create("MahjongGang.png"), NULL, CC_CALLBACK_1(CPlayerLayer::SpriteCallBack, this));
			pItemSpriteGang->setScale(0.5);
			pItemSpriteGang->setTag(PLAYER_GANG);
			pItemSpriteGang->setPosition(Vec2(750 - 80 * nMark, 100));
			pMenu->addChild(pItemSpriteGang);
			nMark++;
		}
	}

	m_userPlayer.GetPlayerHand().HandAddMahjong(m_nMahjongNumber);
	if (m_userPlayer.GetPlayerHand().CheckMahjongHu())
	{
		if (m_bIsTing)
		{
			m_nTimeStatus = 2;
			runAction(m_pSequencePlayer);
		}
		MenuItemSprite *pItemSpriteHu = MenuItemSprite::create(Sprite::create("MahjongHu.png"), NULL, CC_CALLBACK_1(CPlayerLayer::SpriteCallBack, this));
		pItemSpriteHu->setScale(0.5);
		pItemSpriteHu->setTag(PLAYER_HU);
		pItemSpriteHu->setPosition(Vec2(750 - 80 * nMark, 100));
		pMenu->addChild(pItemSpriteHu);
	}


}

void CPlayerLayer::TingCallBack(Ref *pSender)
{
	if (!m_bIsTing && 0 == m_nTingStatus)
	{
		Menu *pMenu = (Menu*)this->getChildByTag(1000);
		if (!m_vectTing.empty())
		{
			m_vectTing.clear();
		}

		for (int i = 0; i < m_vectImageNode.size(); i++)
		{
			int temp = m_vectImageNode.at(i)->GetIndex();
			m_userPlayer.GetPlayerHand().DeleteMahjong(m_vectImageNode.at(i)->GetIndex());
			if (0 != temp)
			{
				if (0 != m_userPlayer.GetPlayerHand().CheckMahjongTing().size())
				{
					m_vectTing.push_back(temp);
				}
			}
			m_userPlayer.GetPlayerHand().HandAddMahjong(m_vectImageNode.at(i)->GetIndex());
		}
		if (!m_vectTing.empty())
		{
			MenuItemSprite *pItemSprite = MenuItemSprite::create(Sprite::create("MahjongTing.png"), NULL, CC_CALLBACK_1(CPlayerLayer::MenuTingCallBack, this));
			pItemSprite->setScale(0.7);
			pItemSprite->setTag(PLAYER_TING);
			pItemSprite->setPosition(Vec2(350, 100));
			pMenu->addChild(pItemSprite);
			m_nTingStatus = 1;
		}
	}
}

void CPlayerLayer::SpriteCallBack(Ref *pSender)
{
	MenuItemSprite *pItemSprite = (MenuItemSprite *)pSender;
	//pItemSprite->removeFromParent();
	log("%d", pItemSprite->getTag());
	switch (pItemSprite->getTag())
	{
	case PLAYER_HU:
		LayerMahjongHu();
		return;
	case PLAYER_GANG:
		LayerMahjongGang(m_nMahjongNumber);
		break;
	case PLAYER_PENG:
		LayerMahjongPeng(m_nMahjongNumber);
		break;
	case PLAYER_CHI:
		LayerMahjongChi(m_nMahjongNumber);
		break;
	case PLAYER_GUO:
		//m_userPlayer.GetPlayerHand().DeleteMahjong(m_nMahjongNumber);
		m_userPlayer.GetPlayerHand().CleanMahjongChi();
		m_userPlayer.GetPlayerHand().CleanMahjongGang();
		m_userPlayer.GetPlayerHand().CleanMahjongPeng();
		break;
	default:
		break;
	}

	m_nTimeStatus = 1;
	if (PLAYER_GANG == pItemSprite->getTag() || PLAYER_GUO == pItemSprite->getTag())
	{
		if (!m_bIsAnimateEnd)
		{
			stopAction(m_pSequencePlayer);
			runAction(CallFuncN::create(CC_CALLBACK_1(CPlayerLayer::DeleGuoCallBack, this)));
			m_nTimeStatus = 0;
		}
		
	}
	
	RemoveItemSprite();
}


void CPlayerLayer::LayerNewCallBack(Ref *pSender)
{

}


void CPlayerLayer::DeleteCallBack(Ref *pSender)
{
	CMahjongMenuImage *pMenuIamge = m_vectImageDel.at(m_vectImageDel.size() - 1);
	pMenuIamge->removeFromParent();
	m_vectImageDel.popBack();
}

void CPlayerLayer::RemoveItemSprite()
{
	Menu *pMenu = (Menu *)this->getChildByTag(1000);
	MenuItemSprite *pItemSpriteHu = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_HU);
	if (NULL != pItemSpriteHu)
	{
		pItemSpriteHu->removeFromParent();
	}

	MenuItemSprite *pItemSpriteGang = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_GANG);
	if (NULL != pItemSpriteGang)
	{
		pItemSpriteGang->removeFromParent();
	}

	MenuItemSprite *pItemSpritePeng = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_PENG);
	if (NULL != pItemSpritePeng)
	{
		pItemSpritePeng->removeFromParent();
	}

	MenuItemSprite *pItemSpriteChi = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_CHI);
	if (NULL != pItemSpriteChi)
	{
		pItemSpriteChi->removeFromParent();
	}

	MenuItemSprite *pItemSpriteGuo = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_GUO);
	if (NULL != pItemSpriteGuo)
	{
		pItemSpriteGuo->removeFromParent();
	}

	
	CMahjongManager::GetInstance().ChangeStatus();
}

void CPlayerLayer::LayerMahjongPeng(int nNumber)
{
	CMahjongManager::GetInstance().ChangeStatus();
	int nMark = 0;
	CMahjongMenuImage *pItemImage = CMahjongMenuImage::create(nNumber);
	pItemImage->setPosition(Vec2(200, 100));
	Menu *pMenu = (Menu *)this->getChildByTag(1000);
	pMenu->addChild(pItemImage);
	m_vectImageOther.pushBack(pItemImage);

	m_userPlayer.GetPlayerHand().DeleteMahjong(m_nMahjongNumber);
	m_userPlayer.DoMahjongPeng(m_nMahjongNumber);

	for (int i = 0; i < m_vectImageNode.size(); i++)
	{
		if (m_vectImageNode.at(i)->GetIndex() == nNumber)
		{
			m_vectImageOther.pushBack(m_vectImageNode.at(i));
			m_vectImageNode.erase(m_vectImageNode.begin() + i);
			i--;
			nMark++;
		}
		if (2 == nMark)
		{
			break;
		}
	}

	for (int i = 0; i < m_vectImageOther.size(); i++)
	{
		MoveTo *pMoveTo = MoveTo::create(1, Vec2(984 - 40 * i, -50));
		m_vectImageOther.at(i)->setScale(0.5);
		m_vectImageOther.at(i)->runAction(pMoveTo);
	}

	for (int i = 0; i < m_vectImageNode.size(); i++)
	{
		Point point = m_vectImageNode.at(i)->getPosition();
		int nDistance = abs(point.x - 200 + 50 * i);
		MoveTo *pMoveTo = MoveTo::create(nDistance / 1000.0, Vec2(200 + 50 * i, 15));
		m_vectImageNode.at(i)->runAction(pMoveTo);
	}

	m_userPlayer.GetPlayerHand().CleanMahjongChi();
	m_userPlayer.GetPlayerHand().CleanMahjongGang();

	NotificationCenter::getInstance()->postNotification(PLAYER_NOTIFICATION_DELETE);
}

void CPlayerLayer::LayerMahjongGang(int nNumber)
{
	int nMark = 0;
	CMahjongMenuImage *pItemImage = CMahjongMenuImage::create(nNumber);
	pItemImage->setPosition(Vec2(200, 100));
	Menu *pMenu = (Menu *)this->getChildByTag(1000);
	pMenu->addChild(pItemImage);
	m_vectImageOther.pushBack(pItemImage);

	m_userPlayer.GetPlayerHand().DeleteMahjong(m_nMahjongNumber);
	m_userPlayer.DoMahjongGang(m_nMahjongNumber);

	for (int i = 0; i < m_vectImageNode.size(); i++)
	{
		if (m_vectImageNode.at(i)->GetIndex() == nNumber)
		{
			m_vectImageOther.pushBack(m_vectImageNode.at(i));
			m_vectImageNode.erase(m_vectImageNode.begin() + i);
			i--;
			nMark++;
		}
		if (3 == nMark)
		{
			break;
		}
	}

	for (int i = 0; i < m_vectImageOther.size(); i++)
	{
		MoveTo *pMoveTo = MoveTo::create(1, Vec2(984 - 40 * i, -50));
		m_vectImageOther.at(i)->setScale(0.5);
		m_vectImageOther.at(i)->runAction(pMoveTo);
	}

	for (int i = 0; i < m_vectImageNode.size(); i++)
	{
		Point point = m_vectImageNode.at(i)->getPosition();
		int nDistance = abs(point.x - 200 + 50 * i);
		MoveTo *pMoveTo = MoveTo::create(nDistance / 1000.0, Vec2(200 + 50 * i, 15));
		m_vectImageNode.at(i)->runAction(pMoveTo);
	}

	m_userPlayer.GetPlayerHand().CleanMahjongChi();
	m_userPlayer.GetPlayerHand().CleanMahjongPeng();
	NotificationCenter::getInstance()->postNotification(PLAYER_NOTIFICATION_DELETE);
}

void CPlayerLayer::LayerMahjongChi(int nNumber)
{
	CMahjongManager::GetInstance().ChangeStatus();
	vector<MahjongChi> vectChi;
	vectChi = m_userPlayer.GetPlayerHand().GetVectChi();

	SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();

	for (int i = 0; i < vectChi.size(); i++)
	{

		MenuItemImage *pItemImage = MenuItemImage::create("MahjongZhao.png", "", "", CC_CALLBACK_1(CPlayerLayer::DoChiCallBack, this));
		pItemImage->setTag(100 + i);
		pItemImage->setPosition(Vec2(400 + 130 * i, 100));
		Sprite *pSpriteFir = Sprite::createWithSpriteFrame(pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png", vectChi.at(i).m_nValueFir)->getCString()));
		pSpriteFir->setScale(0.4);
		pSpriteFir->setPosition(Vec2(9, 6));
		pSpriteFir->setAnchorPoint(Vec2(0, 0));
		pItemImage->addChild(pSpriteFir);

		Sprite *pSpriteSec = Sprite::createWithSpriteFrame(pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png", vectChi.at(i).m_nValueSec)->getCString()));
		pSpriteSec->setScale(0.4);
		pSpriteSec->setPosition(Vec2(9 + 37, 6));
		pSpriteSec->setAnchorPoint(Vec2(0, 0));
		pItemImage->addChild(pSpriteSec);

		Sprite *pSpriteThr = Sprite::createWithSpriteFrame(pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png", vectChi.at(i).m_nValueThd)->getCString()));
		pSpriteThr->setScale(0.4);
		pSpriteThr->setPosition(Vec2(9 + 37 * 2, 6));
		pSpriteThr->setAnchorPoint(Vec2(0, 0));
		pItemImage->addChild(pSpriteThr);

		Menu *pMenu = (Menu *)this->getChildByTag(1000);
		pMenu->addChild(pItemImage);
	}

}

void CPlayerLayer::DoChiCallBack(Ref *pSender)
{
	int nTag = ((MenuItemImage *)pSender)->getTag();
	MahjongChi mahjongChi = m_userPlayer.GetPlayerHand().GetVectChi().at(nTag - 100);
	m_userPlayer.DoMahjongChi(nTag - 100);

	CMahjongMenuImage *pItemImage = CMahjongMenuImage::create(m_nMahjongNumber);
	pItemImage->setPosition(Vec2(200, 100));
	Menu *pMenu = (Menu *)this->getChildByTag(1000);
	pMenu->addChild(pItemImage);

	//如果m_nMahjongNumber是第一个
	int nMark = 0;
	if (mahjongChi.m_nValueFir == m_nMahjongNumber)
	{
		m_vectImageOther.pushBack(pItemImage);
		for (int i = 0; i < m_vectImageNode.size(); i++)
		{
			if (m_vectImageNode.at(i)->GetIndex() == mahjongChi.m_nValueSec && 0 == nMark)
			{
				m_vectImageOther.pushBack(m_vectImageNode.at(i));
				m_vectImageNode.erase(m_vectImageNode.begin() + i);
				i--;
				nMark++;
				continue;
			}
			if (m_vectImageNode.at(i)->GetIndex() == mahjongChi.m_nValueThd)
			{
				m_vectImageOther.pushBack(m_vectImageNode.at(i));
				m_vectImageNode.erase(m_vectImageNode.begin() + i);
				break;
			}
		}
	}
	else if (mahjongChi.m_nValueSec == m_nMahjongNumber)
	{
		//如果m_nMahjongNumber是中间的一个
		nMark = 0;
		for (int i = 0; i < m_vectImageNode.size(); i++)
		{
			if (m_vectImageNode.at(i)->GetIndex() == mahjongChi.m_nValueFir && 0 == nMark)
			{
				m_vectImageOther.pushBack(m_vectImageNode.at(i));
				m_vectImageNode.erase(m_vectImageNode.begin() + i);
				i--;
				nMark++;
				continue;
			}
			if (1 == nMark)
			{
				m_vectImageOther.pushBack(pItemImage);
				nMark++;
				i--;
				continue;
			}
			if (m_vectImageNode.at(i)->GetIndex() == mahjongChi.m_nValueThd)
			{
				m_vectImageOther.pushBack(m_vectImageNode.at(i));
				m_vectImageNode.erase(m_vectImageNode.begin() + i);
				break;
			}
		}
	}
	else
	{
		//如果m_nMahjongNumber是第三个
		nMark = 0;
		for (int i = 0; i < m_vectImageNode.size(); i++)
		{
			if (m_vectImageNode.at(i)->GetIndex() == mahjongChi.m_nValueFir && 0 == nMark)
			{
				m_vectImageOther.pushBack(m_vectImageNode.at(i));
				m_vectImageNode.erase(m_vectImageNode.begin() + i);
				i--;
				nMark++;
				continue;
			}
			if (m_vectImageNode.at(i)->GetIndex() == mahjongChi.m_nValueSec)
			{
				m_vectImageOther.pushBack(m_vectImageNode.at(i));
				m_vectImageNode.erase(m_vectImageNode.begin() + i);
				break;
			}
		}

		m_vectImageOther.pushBack(pItemImage);
	}

	for (int i = 0; i < m_vectImageOther.size(); i++)
	{
		MoveTo *pMoveTo = MoveTo::create(1, Vec2(984 - 40 * i, -50));
		m_vectImageOther.at(i)->setScale(0.5);
		m_vectImageOther.at(i)->runAction(pMoveTo);
	}

	for (int i = 0; i < m_vectImageNode.size(); i++)
	{
		Point point = m_vectImageNode.at(i)->getPosition();
		int nDistance = abs(point.x - 200 + 50 * i);
		MoveTo *pMoveTo = MoveTo::create(nDistance / 1000.0, Vec2(200 + 50 * i, 15));
		m_vectImageNode.at(i)->runAction(pMoveTo);
	}

	for (int i = 100; i < 103; i++)
	{
		MenuItemImage *pItemImage = (MenuItemImage *)pMenu->getChildByTag(i);
		if (NULL != pItemImage)
		{
			pItemImage->removeFromParent();
		}
	}

	m_userPlayer.GetPlayerHand().CleanMahjongChi();
	m_userPlayer.GetPlayerHand().CleanMahjongGang();
	m_userPlayer.GetPlayerHand().CleanMahjongPeng();
	NotificationCenter::getInstance()->postNotification(PLAYER_NOTIFICATION_DELETE);
}

void CPlayerLayer::MenuGangCallBack(Ref *pSender)
{
	CMahjongMenuImage *pItemImage = m_vectImageNode.at(m_vectImageNode.size() - 1);
	log("%d, %d", pItemImage->getPosition().x, pItemImage->getPosition().y);
	m_vectImageNode.popBack();
	
	MenuItemSprite *pItemSprite = (MenuItemSprite *)pSender;
	
	if (pItemSprite->getTag() == PALYER_PENG_GANG)
	{
		m_userPlayer.GetPlayerActions().ChangePengToGang(pItemImage->GetIndex());
	}
	else
	{
		m_vectImageOther.pushBack(pItemImage);
		m_userPlayer.GetPlayerHand().DeleteMahjong(m_nMahjongNumber);
		m_userPlayer.DoMahjongGangAn(m_nMahjongNumber);
	}

	int nMark = 0;
	for (int i = 0; i < m_vectImageNode.size(); i++)
	{
		if (m_vectImageNode.at(i)->GetIndex() == m_nMahjongNumber)
		{
			m_vectImageOther.pushBack(m_vectImageNode.at(i));
			m_vectImageNode.erase(m_vectImageNode.begin() + i);
			i--;
			nMark++;
		}
		if (3 == nMark)
		{
			break;
		}
	}
	
	if (pItemSprite->getTag() == PALYER_PENG_GANG)
	{
		for (int i = 0; i < m_vectImageOther.size(); i++)
		{
			if (m_vectImageOther.at(i)->GetIndex() == pItemImage->GetIndex())
			{
				m_vectImageOther.insert(i, pItemImage);
				break;
			}
		}
	}

	for (int i = 0; i < m_vectImageOther.size(); i++)
	{
		MoveTo *pMoveTo = MoveTo::create(1, Vec2(984 - 40 * i, -50));
		m_vectImageOther.at(i)->setScale(0.5);
		m_vectImageOther.at(i)->runAction(pMoveTo);
	}

	for (int i = 0; i < m_vectImageNode.size(); i++)  
	{
		Point point = m_vectImageNode.at(i)->getPosition();
		int nDistance = abs(point.x - 200 + 50 * i);
		MoveTo *pMoveTo = MoveTo::create(nDistance / 1000.0, Vec2(200 + 50 * i, 15));  
		m_vectImageNode.at(i)->runAction(pMoveTo);
	}

	log("%d, %d", pItemImage->getPosition().x, pItemImage->getPosition().y);

	m_userPlayer.GetPlayerHand().CleanMahjongChi();
	m_userPlayer.GetPlayerHand().CleanMahjongPeng();
	
	CMahjongManager::GetInstance().BackStatus();	
	//MenuItemSprite *pItemSprite = (CMahjongMenuImage *)pSender;

	Menu *pMenu = (Menu *)this->getChildByTag(1000);
	MenuItemSprite *pItemSpriteHu = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_SELF_HU);
	if (NULL != pItemSpriteHu)
	{
		pItemSpriteHu->removeFromParent();
	}

	if (NULL != pItemSprite)
	{
		pItemSprite->removeFromParent();
	}

	
	stopAction(m_pSequenceTing);
	//m_pSequenceTing->release();
	

	if (!m_bIsAnimateEnd)
	{
		stopAction(m_pSequencePlayer);
		runAction(CallFuncN::create(CC_CALLBACK_1(CPlayerLayer::DeleGuoCallBack, this)));
		m_nTimeStatus = 0;
	}
	m_nTimeStatus = 0;
}

void CPlayerLayer::MenuTingCallBack(Ref *pSender)
{
	m_bIsTing = true;
	m_nTingStatus = 2;
	log("status = %d", m_nTingStatus);
	MenuItemSprite *pItemSprite = (MenuItemSprite *)pSender;
	if (NULL != pItemSprite)
	{
		pItemSprite->removeFromParent();
	}
	
	int nIndex = 0;
	for (int i = 0; i < m_vectImageNode.size(); i++)
	{
		if (nIndex == m_vectTing.size())
		{
			break;
		}
		if (m_vectImageNode.at(i)->GetIndex() == m_vectTing.at(nIndex))
		{
			if (i == m_vectImageNode.size() - 1)
			{
				Sprite *pSprite = Sprite::create("Mark.png");
				pSprite->setTag(10 + nIndex);
				pSprite->setScale(0.5);
				pSprite->setPosition(Vec2(210 + 50 * i, 55));
				addChild(pSprite);
				nIndex++;
			}
			else
			{
				Sprite *pSprite = Sprite::create("Mark.png");
				pSprite->setTag(10 + nIndex);
				pSprite->setScale(0.5);
				pSprite->setPosition(Vec2(200 + 50 * i, 55));
				addChild(pSprite);
				nIndex++;
			}
		}
	}

	Menu *pMenu = (Menu *)getChildByTag(1000);
	MenuItemSprite *pMenuItemSprite = MenuItemSprite::create(Sprite::create("MahjongCancel.png"), NULL, CC_CALLBACK_1(CPlayerLayer::MenuCancelCallBack, this));
	pMenuItemSprite->setPosition(Vec2(350, 100));
	pMenuItemSprite->setScale(0.7);
	pMenuItemSprite->setTag(PALYER_CANCEL);
	pMenu->addChild(pMenuItemSprite);

}

void CPlayerLayer::MenuCancelCallBack(Ref *pSender)
{
	m_bIsTing = false;
	m_bChoseTing = false;
	m_nTingStatus = 0;
	MenuItemSprite *pItemSprite = (MenuItemSprite *)pSender;
	if (NULL != pItemSprite)
	{
		pItemSprite->removeFromParent();
	}

	for (int i = 0; i < m_vectTing.size(); i++)
	{
		Sprite *pSprite = (Sprite *)getChildByTag(10 + i);
		if (NULL != pSprite)
		{
			pSprite->removeFromParent();
		}
	}

}

void CPlayerLayer::MenuHuCallBack(Ref *pSender)
{
	m_userPlayer.DoMahjongHu();
	m_userPlayer.GetPlayerActions().SetIsSelfHu(true);
	m_userPlayer.GetPlayerActions().CheckMahjongFan();
	
	CMahjongHuScene *pScene = CMahjongHuScene::create();
	TransitionFlipAngular *flipAngular = TransitionFlipAngular::create(1, pScene);
	pScene->SetMahjongFan(m_userPlayer.GetPlayerActions().GetMahjongFan());
	pScene->SetMahjongName(m_userPlayer.GetPlayerActions().GetVectMahjongName());

	Director::getInstance()->replaceScene(flipAngular);
	m_pSequencePlayer->release();
}

void CPlayerLayer::LayerMahjongHu()
{
	m_userPlayer.DoMahjongHu();
	m_userPlayer.GetPlayerActions().SetIsSelfHu(false);
	m_userPlayer.GetPlayerActions().CheckMahjongFan();

	CMahjongHuScene *pScene = CMahjongHuScene::create();
	TransitionFlipAngular *flipAngular = TransitionFlipAngular::create(1, pScene);
	pScene->SetMahjongFan(m_userPlayer.GetPlayerActions().GetMahjongFan());
	pScene->SetMahjongName(m_userPlayer.GetPlayerActions().GetVectMahjongName());

	Director::getInstance()->replaceScene(flipAngular);
	m_pSequencePlayer->release();
}

void CPlayerLayer::TimeCallBack(Ref *pSender)
{
	if (0 == m_nTimeStatus)
	{
		Animation *runAnimation = Animation::create();
		SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();

		for (int i = 9; i > -1; i--)
		{
			SpriteFrame *pSpriteFrame = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("0%d.jpg", i)->getCString());
			runAnimation->addSpriteFrame(pSpriteFrame);
			
		}
		runAnimation->setDelayPerUnit(1.0f);
		Sprite *pTimeSprite = Sprite::create();
		pTimeSprite->setScale(0.3);
		pTimeSprite->setPosition(Vec2(100, 10));
		pTimeSprite->runAction(RepeatForever::create(Animate::create(runAnimation)));
		pTimeSprite->setTag(1001);
		addChild(pTimeSprite);
		m_nTimeStatus++;
		m_bIsAnimateEnd = false;
		
		log("timeStatus = %d", m_nTimeStatus);
		return;
	}

	if (1 == m_nTimeStatus)
	{
		log("m_ntimeStatus = %d", m_nTimeStatus);
		
		Sprite *pSprite = (Sprite *)getChildByTag(1001);
		if (NULL != pSprite)
		{
			pSprite->removeFromParent();
		}

		Menu *pMenu = (Menu *)this->getChildByTag(1000);
		MenuItemSprite *pItemSprite = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_TING);
		if (NULL != pItemSprite)
		{
			pItemSprite->removeFromParent();
		}

		MenuItemSprite *pItemSpriteHu = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_SELF_HU);
		if (NULL != pItemSpriteHu)
		{
			pItemSpriteHu->removeFromParent();
		}

		CMahjongMenuImage *pNewImage = m_vectImageNode.at(m_vectImageNode.size() - 1);
		m_userPlayer.GetPlayerHand().DeleteMahjong(pNewImage->GetIndex());
		m_vectImageNode.popBack();
		m_vectImageDel.pushBack(pNewImage);
		pNewImage->setScale(0.4);
		pNewImage->setEnabled(false);
		SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();
		SpriteFrame *pSpriteFrameDis = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("%d.png", pNewImage->GetIndex() + 100)->getCString());
		pNewImage->setDisabledImage(Sprite::createWithSpriteFrame(pSpriteFrameDis));

		if (14 > m_vectImageDel.size())
		{
			pNewImage->setPosition(Vec2(230 + m_vectImageDel.size() * 40, 270));
		}
		else
		{
			pNewImage->setPosition(Vec2(230 + (m_vectImageDel.size() - 13) * 40, 210));
		}

		NotificationCenter::getInstance()->postNotification(PLAYER_NOTIFICATION, (Ref *)pNewImage->GetIndex());
		CMahjongManager::GetInstance().ChangeStatus();

		MenuItemSprite *pItemSpriteGang = (MenuItemSprite *)pMenu->getChildByTag(PALYER_PENG_GANG);
		if (NULL != pItemSpriteGang)
		{
			pItemSpriteGang->removeFromParent();
		}

		MenuItemSprite *pItemSpriteSelfGang = (MenuItemSprite *)pMenu->getChildByTag(PLAYER_SELF_GANG);
		if (NULL != pItemSpriteSelfGang)
		{
			pItemSpriteSelfGang->removeFromParent();
		}


		m_pCurImage = NULL;
		m_bIsAnimateEnd = true;
		m_nTimeStatus = 0;
		m_nTingStatus = 0;
		m_bIsTing = false;
		m_bChoseTing = false;

		MenuItemSprite *pMenuItemSprite = (MenuItemSprite *)pMenu->getChildByTag(PALYER_CANCEL);
		if (NULL != pMenuItemSprite)
		{
			pMenuItemSprite->removeFromParent();
		}

		for (int i = 0; i < m_vectTing.size(); i++)
		{
			Sprite *pSprite = (Sprite *)getChildByTag(10 + i);
			if (NULL != pSprite)
			{
				pSprite->removeFromParent();
			}
		}
		
	}

	if (2 == m_nTimeStatus)
	{
		Animation *runAnimation = Animation::create();
		SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();

		for (int i = 9; i > -1; i--)
		{
			SpriteFrame *pSpriteFrame = pSpriteFrameCache->spriteFrameByName(CCString::createWithFormat("0%d.jpg", i)->getCString());
			runAnimation->addSpriteFrame(pSpriteFrame);
		}
		runAnimation->setDelayPerUnit(1.0f);
		Sprite *pTimeSprite = Sprite::create();
		pTimeSprite->setScale(0.3);
		pTimeSprite->setPosition(Vec2(100, 10));
		pTimeSprite->runAction(RepeatForever::create(Animate::create(runAnimation)));
		pTimeSprite->setTag(1001);
		addChild(pTimeSprite);
		m_nTimeStatus++;
		m_bIsAnimateEnd = false;

		return;
	}

	if (3 == m_nTimeStatus)
	{
		Sprite *pSprite = (Sprite *)getChildByTag(1001);
		if (NULL != pSprite)
		{
			pSprite->removeFromParent();
		}

		RemoveItemSprite();
		m_bIsAnimateEnd = true;
		m_nTimeStatus = 0;
	}

}

void CPlayerLayer::DeleCallBack(Ref *pSender)
{
	Sprite *pSprite = (Sprite *)getChildByTag(1001);
	if (NULL != pSprite)
	{
		pSprite->removeFromParent();
	}
	
	//m_userPlayer.GetPlayerHand().DeleteMahjong(m_nMahjongNumber);
	m_bIsAnimateEnd = true;
}

void CPlayerLayer::DeleGuoCallBack(Ref *pSender)
{
	Sprite *pSprite = (Sprite *)getChildByTag(1001);
	if (NULL != pSprite)
	{
		pSprite->removeFromParent();
	}

	m_userPlayer.GetPlayerHand().DeleteMahjong(m_nMahjongNumber);
	m_bIsAnimateEnd = true;
}

