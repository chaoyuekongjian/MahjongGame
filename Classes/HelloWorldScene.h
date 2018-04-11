#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PlayerLayer.h"
#include "EnemyLayer.h"
#include "Mahjong\MahjongManager.h"
//#include "MyWebScoket.h"
#include "MyWebSocket.h"

#include "network/HttpClient.h"
using namespace cocos2d::network;

USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
	HelloWorld();
	~HelloWorld();
    static cocos2d::Scene* createScene();

    virtual bool init();

	void MenuCallBack(Ref *pSender);
	void AnimateCallBack();
	void AddSpriteToLayer(CPlayerLayer *pLayer, int nIndex);
	void AddSpriteToLayer(CEnemyLayer *pLayer, int nIndex);

	void SpriteCallBack(Ref *pSender);
	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
	virtual void update(float dt);
    CREATE_FUNC(HelloWorld);

private:
	int m_nVectSize;
	Vector<Sprite *> m_vectSprite;
	
	bool m_isBegin;
	HttpRequest *m_pRequest;
};

#endif // __HELLOWORLD_SCENE_H__
