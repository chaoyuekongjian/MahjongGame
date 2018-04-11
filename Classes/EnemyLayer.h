#ifndef _ENEMYLAYER_H_
#define _ENEMYLAYER_H_

#include "cocos2d.h"
#include "Mahjong\Player.h"
USING_NS_CC;
#include "MahjongMenuImage.h"
#include "Mahjong\MahjongManager.h"
#include "MahjongHuScene.h"

enum EnemyMahjongSpriteTag
{
	ENEMY_HU        = 50,
	ENEMY_GANG      = 51,
	ENEMY_PENG      = 52,
	ENEMY_CHI       = 53,
	ENEMY_GUO       = 54,
	ENEMY_SELF_GANG = 55,
	ENEMY_PENG_GANG = 56,
	ENEMY_SELF_HU   = 57,
	ENEMY_TING      = 58,
	ENEMY_ANIMATION = 59,
	ENEMY_CANCEL    = 60
};

class CEnemyLayer : public Layer
{
public:
	virtual ~CEnemyLayer();
	CREATE_FUNC(CEnemyLayer);
	virtual bool init();

	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();
	virtual void update(float dt);

	void AddMenuSprite(CMahjongMenuImage *pMenuImage, Point point);
	

	void MenuCallBack(Ref *pSender);
	void NotiCallBack(Ref *pSender);
	void TingCallBack(Ref *pSender);
	void SpriteCallBack(Ref *pSender);
	void DoChiCallBack(Ref *pSender);

private:
	void RemoveItemSprite();
	void LayerMahjongPeng(int nNumber);
	void LayerMahjongGang(int nNumber);
	void LayerMahjongChi(int nNumber);
	void LayerMahjongHu();
	void DeleteCallBack(Ref *pSender);
	
	void MenuGangCallBack(Ref *pSender);
	void MenuHuCallBack(Ref *pSender);
	void MenuTingCallBack(Ref *pSender);
	void MenuCancelCallBack(Ref *pSender);

	void TimeCallBack(Ref *pSender);
	void DeleCallBack(Ref *pSender);
	void DeleGuoCallBack(Ref *pSender);

	CMahjongMenuImage *m_pCurImage;

	cocos2d::Vector<CMahjongMenuImage *> m_vectImageNode;
	cocos2d::Vector<CMahjongMenuImage *> m_vectImageDel;
	cocos2d::Vector<CMahjongMenuImage *> m_vectImageOther;
	std::vector<int> m_vectTing;

	bool m_bIsFilled;
	bool m_bIsTing;
	bool m_bChoseTing;
	bool m_bIsAnimateEnd;
	CPlayer m_userPlayer;

	int m_nMahjongNumber;
	int m_nTingStatus;
	int m_nTimeStatus;

	Sequence *m_pSequencePlayer;
	Sequence *m_pSequenceTing;
};

#endif