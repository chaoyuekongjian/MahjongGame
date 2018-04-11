#include "MahjongFanLayer.h"

CMahjongFanLayer* CMahjongFanLayer::create(CPlayer player)
{
	CMahjongFanLayer *ret = new (std::nothrow) CMahjongFanLayer();
	ret->m_plyaer = player;

	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool CMahjongFanLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	vector<int> vectMahjongHu = m_plyaer.GetPlayerHand().CheckMahjongTing();
	log("vectSize = %d", vectMahjongHu.size());

	setAnchorPoint(Vec2(0, 0));
	setContentSize(Size(218, 77)); 
	setPosition(Vec2(970 - 150 - 50 * vectMahjongHu.size(), 60));

	Sprite *pSprite = Sprite::create("HuBack.png");
	pSprite->setScale(0.3 + vectMahjongHu.size() * 0.1, 0.5);       // 436 153
	pSprite->setAnchorPoint(Vec2(0, 0));
	pSprite->setPosition(Vec2(0, 0));
	addChild(pSprite);
	if (m_plyaer.GetPlayerHand().CheckMahjongHu())
	{
		m_plyaer.DoMahjongHu();
		m_plyaer.GetPlayerActions().CheckMahjongFan();
		int nValue = m_plyaer.GetPlayerActions().GetMahjongFan();

		log("Fan = %d", nValue);
	}
	else
	{
		for (int i = 0; i < vectMahjongHu.size(); i++)
		{
			CPlayer player;
			player = m_plyaer;
			player.GetPlayerHand().HandAddMahjong(vectMahjongHu.at(i));
			player.GetPlayerHand().CheckMahjongHu();
			player.DoMahjongHu();
			player.GetPlayerActions().CheckMahjongFan();
			int nValue = player.GetPlayerActions().GetMahjongFan();

			log("Fan = %d", nValue);
		}
	}
	

	//m_plyaer.GetPlayerActions().CheckMahjongFan();

	return true;
}






