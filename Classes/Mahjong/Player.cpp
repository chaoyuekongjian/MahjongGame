#include "Player.h"


CPlayer::CPlayer()
{

	m_nMahjongType = -1;
	m_nMahjongValue = 0;
	
}


CPlayer::~CPlayer()
{
	
	
}

void CPlayer::CheckMahjong(int nValue, int nIndex)
{
	
	if (m_playerHand.CheckMahjongGang(nValue))
	{
		m_nMahjongType = TYPE_GANG;
		m_nMahjongValue = nValue;

		return;
	}
	if (m_playerHand.CheckMahjongPeng(nValue))
	{
		m_nMahjongType = TYPE_PENG;
		m_nMahjongValue = nValue;
		return;
	}
	if (-1 == nIndex)
	{
		return;
	}
	if (m_playerHand.CheckMahjongChi(nValue))
	{
		m_nMahjongType  = TYPE_CHI;
		m_nMahjongValue = nIndex;
		return;
	}
}

void CPlayer::DoMahjong()
{
	if (-1 == m_nMahjongType)
	{
		return;
	}
	switch (m_nMahjongType)
	{
	case TYPE_GANG:
		DoMahjongGang(m_nMahjongValue);
		break;
	case TYPE_PENG:
		DoMahjongPeng(m_nMahjongValue);
		break;
	case TYPE_CHI:
		DoMahjongChi(m_nMahjongValue);
		break;
	default:
		break;
	}
}


void CPlayer::DoMahjongChi(int nIndex) // 选择某一种的吃牌
{
	//assert(0 > nIndex && m_playerHand.GetVectChi().size() <= nIndex);
	MahjongChi mahjongChi = m_playerHand.GetVectChi().at(nIndex);
	m_playerHand.DeleteMahjong(mahjongChi.m_nValueFir);
	m_playerHand.DeleteMahjong(mahjongChi.m_nValueSec);
	m_playerHand.DeleteMahjong(mahjongChi.m_nValueThd);
	m_playerAction.ActionAddMahjong(mahjongChi);
	m_playerHand.CleanMahjongChi();

	return;
}

void CPlayer::DoMahjongPeng(int nValue)
{
	int nSize = m_playerHand.GetVectPeng().size();
	for (int i = 0; i < nSize; i++)
	{
		if (nValue == m_playerHand.GetVectPeng().at(i).m_nValueFir)
		{
			m_playerHand.DeleteMahjong(nValue);
			m_playerHand.DeleteMahjong(nValue);
			MahjongPeng mahjongPeng;
			mahjongPeng.m_nValueFir = nValue;
			mahjongPeng.m_nValueSec = nValue;
			mahjongPeng.m_nValueThd = nValue;
			m_playerAction.ActionAddMahjong(mahjongPeng);
		}
	}

	m_playerHand.CleanMahjongPeng();
}

void CPlayer::DoMahjongGang(int nValue)
{
	int nSize = m_playerHand.GetVectGang().size();
	for (int i = 0; i < nSize; i++)
	{
		if (nValue == m_playerHand.GetVectGang().at(i).m_nValueFir)
		{
			m_playerHand.DeleteMahjong(nValue);
			m_playerHand.DeleteMahjong(nValue);
			m_playerHand.DeleteMahjong(nValue);
			MahjongGang mahjongGang;
			mahjongGang.m_nValueFir = nValue;
			mahjongGang.m_nValueSec = nValue;
			mahjongGang.m_nValueThd = nValue;
			mahjongGang.m_nValueFth = nValue;
			m_playerAction.ActionAddMahjong(mahjongGang);
		}
	}

	m_playerHand.CleanMahjongGang();
}

void CPlayer::DoMahjongGangAn(int nValue)
{
	int nSize = m_playerHand.GetVectGang().size();
	for (int i = 0; i < nSize; i++)
	{
		if (nValue == m_playerHand.GetVectGang().at(i).m_nValueFir)
		{
			m_playerHand.DeleteMahjong(nValue);
			m_playerHand.DeleteMahjong(nValue);
			m_playerHand.DeleteMahjong(nValue);
			MahjongGangAn mahjongGangAn;
			mahjongGangAn.m_nValueFir = nValue;
			mahjongGangAn.m_nValueSec = nValue;
			mahjongGangAn.m_nValueThd = nValue;
			mahjongGangAn.m_nValueFth = nValue;
			m_playerAction.ActionAddMahjong(mahjongGangAn);
		}
	}

	m_playerHand.CleanMahjongGang();
}


bool CPlayer::HaveHuMahjong()
{
	if (m_playerHand.CheckMahjongHu())
	{
		return true;
	}

	return false;
}

void CPlayer::DoMahjongHu()
{
	m_playerAction.ActionAddMahjong(m_playerHand.GetVectHand());
	m_playerAction.SetJiang(m_playerHand.GetJiang());
	m_playerAction.SetHandMahjong(m_playerHand.GetVectHand());
}



void CPlayer::MahjongPrint()
{
	vector<int> vectHand = m_playerHand.GetVectHand();
	cout << "手上的牌:" << endl;
	for (int i = 0; i < vectHand.size(); i++)
	{
		cout << vectHand.at(i) << " ";
	}
}


CHand& CPlayer::GetPlayerHand()
{
	return m_playerHand;
}

CActions& CPlayer::GetPlayerActions()
{
	return m_playerAction;
}

int CPlayer::GetMahjongType()
{
	return m_nMahjongType;
}


CPlayer& CPlayer::operator = (const CPlayer &player)
{
	if (this == &player)
	{
		return *this;
	}
	m_playerHand = player.m_playerHand;
	m_playerAction = player.m_playerAction;

	return *this;
}

