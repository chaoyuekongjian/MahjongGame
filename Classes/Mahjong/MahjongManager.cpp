#include "MahjongManager.h"

CMahjongManager::CMahjongManager()
{
	m_nStatus = GAME_BEGIN;
	m_bControl = true;
	m_vectMahjong.reserve(20);
	srand((unsigned)time(NULL));

	FillMahjong();
}


CMahjongManager& CMahjongManager::GetInstance()
{
	static CMahjongManager mahjongManager;
	return mahjongManager;
}

CMahjongManager::~CMahjongManager()
{


}

void CMahjongManager::FillMahjong()
{
	if (!m_vectMahjong.empty())
	{
		m_vectMahjong.clear();
	}
	for (int i = 1; i < 17; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_vectMahjong.push_back(i);
		}
	}
	/*for (int i = 17; i < 25; i++)
	{
	m_vectMahjong.push_back(i);
	}*/
	if (!m_vectMahjongQiang.empty())
	{
		m_vectMahjongQiang.clear();
	}
	int nCount = m_vectMahjong.size();
	for (int i = 0; i < nCount; i++)
	{
		int nIndex = rand() % m_vectMahjong.size();
		int nValue = m_vectMahjong.at(nIndex);
		m_vectMahjong.erase(m_vectMahjong.begin() + nIndex);
		m_vectMahjongQiang.push_back(nValue);
	}
}

int CMahjongManager::DispatchMahjong()
{
	int nIndex = m_vectMahjongQiang.at(m_vectMahjongQiang.size() - 1);
	m_vectMahjongQiang.pop_back();

	return nIndex;
}

vector<int> CMahjongManager::GetMahjongVect()
{
	return m_vectMahjongQiang;
}


bool CMahjongManager::CheckVectEmpty()
{
	if (m_vectMahjongQiang.empty())
	{
		return true;
	}

	return false;
}

void CMahjongManager::SwapVect(int nIndexFir, int nIndexSec)
{
	swap(m_vectMahjongQiang.at(nIndexFir), m_vectMahjongQiang.at(nIndexSec));
}

int CMahjongManager::GetVectSize()
{
	return m_vectMahjongQiang.size();
}


void CMahjongManager::ChangeStatus()
{
	//cocos2d::log("change = %d", m_nStatus);
	if (ENEMY_MID == m_nStatus)
	{
		m_nStatus = PLAYER_ENABLE;
		return;
	}
	m_nStatus++;
}

void CMahjongManager::BackStatus()
{
	if (PLAYER_ENABLE == m_nStatus)
	{
		m_nStatus = ENEMY_END;
		//cocos2d::log("%d", m_nStatus);
		return;
	}
	m_nStatus--;
	//cocos2d::log("back = %d", m_nStatus);
}

void CMahjongManager::ResetStatus()
{
	m_nStatus = GAME_BEGIN;
	m_bControl = true;
}

int CMahjongManager::GetStatus()
{
	return m_nStatus;
}

