#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MahjongSprite.h"
#include "MahjongMenuImage.h"

#include "MahjongLayer.h"
#include "Mahjong\MahjongTree.h"


USING_NS_CC;

HelloWorld::HelloWorld()
{
	
}

HelloWorld::~HelloWorld()
{
	m_pRequest->release();
}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	m_isBegin = false;
	CMahjongManager::GetInstance().FillMahjong();
	Sprite *pBackSprite = Sprite::create();
	pBackSprite->initWithFile("BackGround.png");
	pBackSprite->setAnchorPoint(Vec2(0, 0));
	pBackSprite->setPosition(Vec2(0, 0));
	addChild(pBackSprite);


	for (int i = 0; i < CMahjongManager::GetInstance().GetVectSize(); i++)
	{
		if (i < CMahjongManager::GetInstance().GetVectSize() / 2)
		{
			Sprite *pSprite = Sprite::create("Mahjong_left.png");
			if (0 == i % 2)
			{
				pSprite->setPosition(Vec2(150, 200 + 23 * (i / 2)));
			}
			else
			{
				pSprite->setPosition(Vec2(140, 200 + 23 * (i / 2)));
			}
			pSprite->setScale(0.5);
			pSprite->setTag(i);
			addChild(pSprite);
			m_vectSprite.pushBack(pSprite);
		}
		else
		{
			Sprite *pSprite = Sprite::create("Mahjong_right.png");
			if (0 == i % 2)
			{
				pSprite->setPosition(Vec2(890, 200 + 23 * ((i - CMahjongManager::GetInstance().GetVectSize() / 2) / 2)));
			}
			else
			{
				pSprite->setPosition(Vec2(900, 200 + 23 * ((i - CMahjongManager::GetInstance().GetVectSize() / 2) / 2)));
			}
			pSprite->setScale(0.5);
			pSprite->setTag(i);
			addChild(pSprite);
			m_vectSprite.pushBack(pSprite);
		}
		
		
	}

	DelayTime *pDelayTime = DelayTime::create(0.1); 
	Sequence *pSequence = Sequence::create(pDelayTime, CallFunc::create(this, callfunc_selector(HelloWorld::AnimateCallBack)), NULL);
	runAction(pSequence);

	//RotateTo *pRotate = RotateTo::create()
	//FadeOutUpTiles *pFade = FadeOutUpTiles::create(2, CCSizeMake(16, 12));

	/*SpriteFrameCache *pSpriteFrameCache = SpriteFrameCache::getInstance();
	SpriteFrame *pSpriteFrame = pSpriteFrameCache->spriteFrameByName(CCString::create("1.png")->getCString());
	SpriteFrame *pSpriteFrame2 = pSpriteFrameCache->spriteFrameByName(CCString::create("Mahjong_back.png")->getCString());
	Sprite *sprite = Sprite::createWithSpriteFrame(pSpriteFrame);
	sprite->setAnchorPoint(Vec2(0.5, 0.2));
	sprite->setPosition(Vec2(500, 300));
	addChild(sprite);
	RotateTo *pRotate = RotateTo::create(0.5, Vec3(80, 0, 0));
	sprite->runAction(Sequence::create(pRotate, CallFunc::create([=](){
		sprite->initWithSpriteFrame(pSpriteFrame2);
		sprite->setAnchorPoint(Vec2(0.5, 0));
	}), RotateTo::create(0.5, Vec3(110, 0, 0)), RotateTo::create(0.5, Vec3(80, 0, 0)), CallFunc::create([=](){
		sprite->initWithSpriteFrame(pSpriteFrame);
		sprite->setAnchorPoint(Vec2(0.5, 0));
	}), RotateTo::create(0.5, Vec3(0, 0, 0)), NULL));*/

	//auto rt = (sprite->getPosition().x - 512) / 1024;
	//sprite->runAction(OrbitCamera::create(2, 1, 0, 0, 90 + sinf(rt) * 104, 0, 0));
	//OrbitCamera *pOrbit = OrbitCamera::create(2, 1, 0, 0, 180, 90, 0);
	//sprite->runAction(pOrbit);
	m_pRequest = new HttpRequest();
	m_pRequest->setUrl("http://127.0.0.1:3000/user?username=red&password=123456");
	m_pRequest->setRequestType(HttpRequest::Type::POST);
	m_pRequest->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpRequestCompleted, this));

	// write the post data
	//const char* postData = "username=red&password=123456";
	//request->setRequestData(postData, strlen(postData));
	//request->setTag("POST test");
	cocos2d::network::HttpClient::getInstance()->send(m_pRequest);
	
	

	vector<int> vectTree;
	for (int i = 1; i < 8; i++)
	{
		vectTree.push_back(i);
	}
	CMahjongTree tree(vectTree);
	vector<CMahjongData> vectData;
	vectData = tree.GetDateByLevel(5);
	cout << vectData.size() << endl;
	

	MenuItemSprite *pItemSpriteHu = MenuItemSprite::create(Sprite::create("MahjongHu.png"), NULL, CC_CALLBACK_1(HelloWorld::MenuCallBack, this));
	pItemSpriteHu->setScale(0.5);
	pItemSpriteHu->setTag(ENEMY_HU);
	pItemSpriteHu->setPosition(Vec2(300, 40));
	
	Menu *pMenu = Menu::create(/*pItemSpriteHu, NULL*/);
	pMenu->setPosition(Point::ZERO);
	addChild(pMenu);

	MenuItemSprite *pMenuItemSprite = MenuItemSprite::create(Sprite::create("CloseNormal.png"), Sprite::create("CloseSelected.png"), CC_CALLBACK_1(HelloWorld::SpriteCallBack, this));
	pMenuItemSprite->setPosition(980, 720);
	
	/*Menu *pMenu = Menu::create(pMenuItemSprite, NULL);
	pMenu->setPosition(Point::ZERO);*/
	pMenu->addChild(pMenuItemSprite);

	scheduleUpdate();
    return true;
}

void HelloWorld::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	CWebSocket *pWebSocket = new CWebSocket();
	pWebSocket->onSendMessage();

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		log("%s completed", response->getHttpRequest()->getTag());
	}
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	//_labelStatusCode->setString(statusString);
	log("onHttpRequestCompleted");
	log("response code: %d", statusCode);
	log("%s", statusString);
	if (!response->isSucceed())
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	printf("Http Test, dump data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		printf("%c", (*buffer)[i]);
	}
	printf("\n");
}

void HelloWorld::SpriteCallBack(Ref *pSender)
{
	static int nMark = 0;
	if (0 == nMark)
	{
		CMahjongLayer *pLayer = CMahjongLayer::create();
		pLayer->setTag(110);
		addChild(pLayer);
		nMark++;
		
		return;
	}
	if (1 == nMark)
	{
		CMahjongLayer *pLayer = (CMahjongLayer *)getChildByTag(110);
		if (NULL != pLayer)
		{
			pLayer->removeFromParent();
		}
		nMark = 0;
	}

}


void HelloWorld::update(float dt)
{
	if (m_nVectSize != CMahjongManager::GetInstance().GetVectSize() && m_isBegin)
	{
		Sprite *pSprite = m_vectSprite.at(m_vectSprite.size() - 1);
		m_vectSprite.popBack();
		pSprite->removeFromParent();
		m_nVectSize = CMahjongManager::GetInstance().GetVectSize();

	}
	


}

void HelloWorld::MenuCallBack(Ref *pSender)
{
	CPlayer player;
	int a[] = { 1, 1, 2, 2, 3, 3, 7, 8, 9, 7, 8, 9, 5, 5 };
	for (int i = 0; i < 14; i++)
	{
		player.GetPlayerHand().HandAddMahjong(a[i]);
	}
	if (player.GetPlayerHand().CheckMahjongHu())
	{
		log("YES");
	}
	else
	{ 
		log("NO");
	}
	player.DoMahjongHu();
	player.GetPlayerActions().SetIsSelfHu(true);
	player.GetPlayerActions().CheckMahjongFan();

	CMahjongHuScene *pScene = CMahjongHuScene::create();
	TransitionFlipAngular *flipAngular = TransitionFlipAngular::create(1, pScene);
	pScene->SetMahjongFan(player.GetPlayerActions().GetMahjongFan());
	pScene->SetMahjongName(player.GetPlayerActions().GetVectMahjongName());

	Director::getInstance()->replaceScene(flipAngular);
}

void HelloWorld::AnimateCallBack()
{
	srand((unsigned)time(NULL));
	CPlayerLayer *pPlayerLayer = CPlayerLayer::create();
	addChild(pPlayerLayer);
	for (int i = 0; i < 8; i += 2)
	{
		AddSpriteToLayer(pPlayerLayer, i);
	}

	CEnemyLayer *pEnemyLayer = CEnemyLayer::create();
	addChild(pEnemyLayer);
	for (int i = 1; i < 8; i += 2)
	{
		AddSpriteToLayer(pEnemyLayer, i);
	}

	m_nVectSize = CMahjongManager::GetInstance().GetVectSize();
	m_isBegin = true;

	for (int i = 0; i < 8; i++)
	{
		if (6 > i)
		{ 
			for (int j = 0; j < 4; j++)
			{
				Sprite *pSprite = m_vectSprite.at(m_vectSprite.size() - 1);
				m_vectSprite.popBack();
				Sequence *pSequence = Sequence::create(DelayTime::create(0.3 * (i + 1)), CallFunc::create([=](){
					pSprite->removeFromParent();
				}), NULL);
				pSprite->runAction(pSequence);
			}
		}
		else
		{
			Sprite *pSprite = m_vectSprite.at(m_vectSprite.size() - 1);
			m_vectSprite.popBack();
			Sequence *pSequence = Sequence::create(DelayTime::create(0.3 * (i + 1)), CallFunc::create([=](){
				pSprite->removeFromParent();
			}), NULL);
			pSprite->runAction(pSequence);
		}
	}

}

void HelloWorld::AddSpriteToLayer(CPlayerLayer *pLayer, int nIndex)
{
	if (6 == nIndex)
	{
		int nTemp = CMahjongManager::GetInstance().DispatchMahjong();
		CMahjongMenuImage *pTemp = CMahjongMenuImage::create(nTemp);
		pTemp->setEnabled(true);
		pTemp->retain();
		//DelayTime::create(0.3);
		runAction(Sequence::create(DelayTime::create(0.3 * (nIndex + 1)), CallFunc::create([=](){
			pLayer->AddMenuSprite(pTemp, Vec2(200 + 12 * 50, 15));
		}), NULL));
		return;
	}

	for (int i = nIndex / 2 * 4; i < (nIndex / 2 + 1) * 4; i++)
	{
		int nTemp = CMahjongManager::GetInstance().DispatchMahjong();
		CMahjongMenuImage *pTemp = CMahjongMenuImage::create(nTemp);
		pTemp->setEnabled(true);
		pTemp->retain();
		//DelayTime::create(0.3);
		runAction(Sequence::create(DelayTime::create(0.3 * (nIndex + 1)), CallFunc::create([=](){

			pLayer->AddMenuSprite(pTemp, Vec2(200 + i * 50, 15));
		}), NULL));
		
	}

}

void HelloWorld::AddSpriteToLayer(CEnemyLayer *pLayer, int nIndex)
{
	if (7 == nIndex)
	{
		int nTemp = CMahjongManager::GetInstance().DispatchMahjong();
		CMahjongMenuImage *pTemp = CMahjongMenuImage::create(nTemp);
		pTemp->setEnabled(true);
		//DelayTime::create(0.3);
		pTemp->retain();
		runAction(Sequence::create(DelayTime::create(0.3 * (nIndex + 1)), CallFunc::create([=](){
			pLayer->AddMenuSprite(pTemp, Vec2(200 + 12 * 50, 80));
		}), NULL));

		return;
	}
	for (int i = (nIndex - 1) / 2 * 4; i < ((nIndex - 1) / 2 + 1) * 4; i++)
	{
		int nTemp = CMahjongManager::GetInstance().DispatchMahjong();
		CMahjongMenuImage *pTemp = CMahjongMenuImage::create(nTemp);
		pTemp->setEnabled(true);
		pTemp->retain();
		//DelayTime::create(0.3);
		runAction(Sequence::create(DelayTime::create(0.3 * (nIndex + 1)), CallFunc::create([=](){
			pLayer->AddMenuSprite(pTemp, Vec2(200 + i * 50, 80));
		}), NULL));

	}
}




