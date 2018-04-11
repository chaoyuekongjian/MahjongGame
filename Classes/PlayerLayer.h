#ifndef _PALYERLAYER_H_
#define _PALYERLAYER_H_

#include "cocos2d.h"
USING_NS_CC;
#include "Mahjong\MahjongManager.h"
#include "MahjongMenuImage.h"
#include "MahjongHuScene.h"
#include "MahjongFanLayer.h"

enum PlayerMahjongSpriteTag
{
	PLAYER_HU        = 70,
	PLAYER_GANG      = 71,
	PLAYER_PENG      = 72,
	PLAYER_CHI       = 73,
	PLAYER_GUO       = 74,
	PLAYER_SELF_GANG = 75,
	PALYER_PENG_GANG = 76,
	PLAYER_SELF_HU   = 77,
	PLAYER_TING      = 78, 
	PLAYER_ANIMATION = 79,
	PALYER_CANCEL    = 80,
	PLAYER_HUFAN     = 81
};


class CPlayerLayer : public Layer
{
public:
	virtual ~CPlayerLayer();
	CREATE_FUNC(CPlayerLayer);
	virtual bool init();

	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();
	virtual void update(float dt);

	void AddMenuSprite(CMahjongMenuImage *pMenuImage, Point point);
	//MenuItemSprite* CreateSprite(int nIndex, const ccMenuCallback& callBack);

	void MenuCallBack(Ref *pSender);
	void HufanCallBack(Ref *pSender);

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

	void LayerNewCallBack(Ref *pSender);
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



/*
思路：
判定对家打出的牌和从牌组中抓到的牌

*/
