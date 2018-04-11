#include "Hand.h"
#include <algorithm>

CHand::CHand()
{
	
	m_nMahjongJiang = 0;

}


CHand::~CHand()
{

}

void CHand::HandAddMahjong(int nValue)
{
	vector<int>::iterator iter;
	for (iter = m_vectMahjongHand.begin(); iter != m_vectMahjongHand.end(); iter++)
	{
		if ((*iter) > nValue)
		{
			m_vectMahjongHand.insert(iter, nValue);
			return;
		}
	}

	m_vectMahjongHand.push_back(nValue);
	//sort(m_vectMahjongHand.begin(), m_vectMahjongHand.end());
}

//获取麻将位置的索引
int CHand::GetMahjongAtIndex(int nValue)
{
	int nCount = 0;
	vector<int>::iterator iter;
	for (iter = m_vectMahjongHand.begin(); iter != m_vectMahjongHand.end(); iter++)
	{
		if ((*iter) == nValue)
		{
			return nCount;
		}
		nCount++;
	}

	return -1;
}

int CHand::ThrowMahjong(int nIndex)
{
	if (nIndex >= m_vectMahjongHand.size())
	{
		return 0;
	}
	int nValue = 0;
	for (int i = 0; i < m_vectMahjongHand.size(); i++)
	{
		if (i == nIndex)
		{
			nValue = m_vectMahjongHand.at(i);
			m_vectMahjongHand.erase(m_vectMahjongHand.begin() + i);
			break;
		}
	}

	return nValue;
}

bool CHand::DeleteMahjong(int nValue)
{
	vector<int>::iterator iter;
	for (iter = m_vectMahjongHand.begin(); iter != m_vectMahjongHand.end(); iter++)
	{
		if ((*iter) == nValue)
		{
			m_vectMahjongHand.erase(iter);
			return true;
		}
	}
	vector<int> vect;

	return false;
}

void CHand::CleanUp()
{
	if (!m_vectMahjongHand.empty())
	{
		m_vectMahjongHand.clear();
	}
}

//void CHand::VectMahjongChi(vector<StrChi> &vectChi)
//{
//	vectChi.insert(vectChi.begin(), m_vectMahjongChi.begin(), m_vectMahjongChi.end());
//}
//
//void CHand::VectMahjongHand(vector<int> &vectChi)
//{
//	vectChi.insert(vectChi.begin(), m_vectMahjongHand.begin(), m_vectMahjongHand.end());
//}

bool CHand::CheckMahjongChi(int nValue)
{
	if (9 < nValue)
	{
		return false;
	}
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectMahjongHand.begin(), m_vectMahjongHand.end());
	vector<int>::iterator iter;
	//int nSize = vectMahjong.size();
	for (int i = 0; i < vectMahjong.size(); i++)
	{
		if (9 < vectMahjong.at(i))
		{
			vectMahjong.erase(vectMahjong.begin() + i);
			i--;
		}
		if (vectMahjong.empty())
		{
			return false;
		}
	}

	for (int i = 0; i < vectMahjong.size() - 1; i++)
	{
		if (vectMahjong.at(i) == vectMahjong.at(i + 1))
		{
			vectMahjong.erase(vectMahjong.begin() + i);
			i--;
		}
		//i--;
	}

	int nSize = vectMahjong.size();
	if (2 <= nSize)
	{
		for (int i = 0; i < nSize - 1; i++)
		{
			if (nValue + 1 == vectMahjong.at(i) && nValue + 2 == vectMahjong.at(i + 1))
			{
				MahjongChi mahjongChi;
				mahjongChi.m_nValueFir = nValue;
				mahjongChi.m_nValueSec = nValue + 1;
				mahjongChi.m_nValueThd = nValue + 2;
				m_vectMahjongChi.push_back(mahjongChi);
			}
			if (nValue - 1 == vectMahjong.at(i) && nValue + 1 == vectMahjong.at(i + 1))
			{
				MahjongChi mahjongChi;
				mahjongChi.m_nValueFir = nValue - 1;
				mahjongChi.m_nValueSec = nValue;
				mahjongChi.m_nValueThd = nValue + 1;
				m_vectMahjongChi.push_back(mahjongChi);
			}
			if (nValue - 2 == vectMahjong.at(i) && nValue - 1 == vectMahjong.at(i + 1))
			{
				MahjongChi mahjongChi;
				mahjongChi.m_nValueFir = nValue - 2;
				mahjongChi.m_nValueSec = nValue - 1;
				mahjongChi.m_nValueThd = nValue;
				m_vectMahjongChi.push_back(mahjongChi);
			}
		}

		for (int i = 0; i < nSize - 2; i++)
		{
			if (nValue - 1 == vectMahjong.at(i) && nValue + 1 == vectMahjong.at(i + 2))
			{
				MahjongChi mahjongChi;
				mahjongChi.m_nValueFir = nValue - 1;
				mahjongChi.m_nValueSec = nValue;
				mahjongChi.m_nValueThd = nValue + 1;
				m_vectMahjongChi.push_back(mahjongChi);
			}
		}
	}
	if (m_vectMahjongChi.empty())
	{
		return false;
	}

	return true;
}

bool CHand::CheckMahjongPeng(int nValue)
{
	vector<int>::iterator iter;
	int nCount = 0;
	for (iter = m_vectMahjongHand.begin(); iter != m_vectMahjongHand.end(); iter++)
	{
		if ((*iter) == nValue)
		{
			nCount++;
			if (nCount == 2)
			{
				MahjongPeng mahjongPeng;
				mahjongPeng.m_nValueFir = nValue;
				mahjongPeng.m_nValueSec = nValue;
				mahjongPeng.m_nValueThd = nValue;
				m_vectMahjongPeng.push_back(mahjongPeng);
				return true;
			}
		}
	}
	return false;
}

bool CHand::CheckMahjongGang(int nValue)
{
	vector<int>::iterator iter;
	int nCount = 0;
	for (iter = m_vectMahjongHand.begin(); iter != m_vectMahjongHand.end(); iter++)
	{
		if ((*iter) == nValue)
		{
			nCount++;
			if (nCount == 3)
			{
				MahjongGang mahjongGang;
				mahjongGang.m_nValueFir = nValue;
				mahjongGang.m_nValueSec = nValue;
				mahjongGang.m_nValueThd = nValue;
				mahjongGang.m_nValueFth = nValue;
				m_vectMahjongGang.push_back(mahjongGang);
				return true;
			}
		}
	}
	return false;
}


bool CHand::CheckMahjongABC(const vector<int> vectValue)
{
	if (3 != vectValue.size())
	{
		return false;
	}
	if (vectValue.at(0) == vectValue.at(1) - 1 && vectValue.at(1) == vectValue.at(2) - 1)
	{
		return true;
	}

	return false;
}

bool CHand::CheckMahjongAAA(const vector<int> vectValue)
{
	if (3 != vectValue.size())
	{
		return false;
	}
	if (vectValue.at(0) == vectValue.at(1) && vectValue.at(1) == vectValue.at(2))
	{
		return true;
	}

	return false;
}


bool CHand::CheckMahjongThr(const vector<int> vectValue)
{
	int nSize = vectValue.size();
	if (3 != nSize)
	{
		return false;
	}

	if (CheckMahjongAAA(vectValue))
	{
		return true;
	}
	if (CheckMahjongABC(vectValue))
	{
		return true;
	}

	return false;
}

bool CHand::CheckMahjongSix(const vector<int> vectValue)
{
	int nSize = vectValue.size();
	if (6 != nSize)
	{
		return false;
	}
	//如果是三连对
	if (vectValue.at(0) == vectValue.at(1) && vectValue.at(2) == vectValue.at(3) && vectValue.at(4) == vectValue.at(5))
	{
		if (vectValue.at(0) + 1 == vectValue.at(2) && vectValue.at(2) + 1 == vectValue.at(4))
		{
			return true;
		}
	}

	////如果中间四张牌为四重张 旁边的两张牌都是与其连续
	//if (vectValue.at(1) == vectValue.at(2) && vectValue.at(2) == vectValue.at(3) && vectValue.at(3) == vectValue.at(4))
	//{
	//	if (vectValue.at(0) + 1 == vectValue.at(1) && vectValue.at(4) + 1 == vectValue.at(5))
	//	{
	//		return true;
	//	}
	//}

	//344556 情况下
	if (vectValue.at(1) == vectValue.at(2) && vectValue.at(2) + 1 == vectValue.at(3) && vectValue.at(3) == vectValue.at(4))
	{
		if (vectValue.at(0) + 1 == vectValue.at(1) && vectValue.at(4) + 1 == vectValue.at(5))
		{
			return true;
		}
	}
	//122223 情况下 
	if (vectValue.at(1) == vectValue.at(2) && vectValue.at(2) == vectValue.at(3) && vectValue.at(3) == vectValue.at(4))
	{
		if (vectValue.at(0) + 1 == vectValue.at(1) && vectValue.at(4) + 1 == vectValue.at(5))
		{
			return true;
		}
	}

	vector<int> vectTempFir;
	vectTempFir.insert(vectTempFir.begin(), vectValue.begin(), vectValue.begin() + 3);
	vector<int> vectTempSec;
	vectTempSec.insert(vectTempSec.begin(), vectValue.begin() + 3, vectValue.end());
	if (CheckMahjongThr(vectTempFir) && CheckMahjongThr(vectTempSec))
	{
		return true;
	}
	return false;
}

bool CHand::CheckMahjongNin(const vector<int> vectValue)
{
	int nSize = vectValue.size();
	if (9 != nSize)
	{
		return false;
	}
	//122333445
	if (4 == vectValue.at(8) - vectValue.at(0) && 2 == vectValue.at(7) - vectValue.at(1) && 2 == vectValue.at(6) - vectValue.at(2))
	{
		if (vectValue.at(3) == vectValue.at(4) && vectValue.at(4) == vectValue.at(6))
		{
			return true;
		}
	}
	//如果是三暗刻
	int nCount = 0;
	for (int i = 0; i < nSize; i = i + 3)
	{
		if (vectValue.at(i) == vectValue.at(i + 1) && vectValue.at(i + 1) == vectValue.at(i + 2))
		{
			nCount++;
		}
		if (3 == nCount)
		{
			return true;
		}
	}
	//如果前面三个为三重张或三连张
	vector<int> vectTempFir;
	vectTempFir.insert(vectTempFir.begin(), vectValue.begin(), vectValue.begin() + 3);
	vector<int> vectTempSec;
	vectTempSec.insert(vectTempSec.begin(), vectValue.begin() + 3, vectValue.end());
	if (CheckMahjongThr(vectTempFir) && CheckMahjongSix(vectTempSec))
	{
		return true;
	}

	//如果后面三张为三连张或三重张
	vectTempFir.clear();
	vectTempFir.insert(vectTempFir.begin(), vectValue.begin(), vectValue.begin() + 6);
	vectTempSec.clear();
	vectTempSec.insert(vectTempSec.begin(), vectValue.begin() + 6, vectValue.end());
	if (CheckMahjongSix(vectTempFir) && CheckMahjongThr(vectTempSec))
	{
		return true;
	}

	return false;
}

bool CHand::CheckMahjongTwl(const vector<int> vectValue)
{
	int nSize = vectValue.size();
	if (12 != nSize)
	{
		return false;
	}
	//如果前面三张为三重张或三连张
	vector<int> vectTempFir;
	vectTempFir.insert(vectTempFir.begin(), vectValue.begin(), vectValue.begin() + 3);
	vector<int> vectTempSec;
	vectTempSec.insert(vectTempSec.begin(), vectValue.begin() + 3, vectValue.end());
	if (CheckMahjongThr(vectTempFir) && CheckMahjongNin(vectTempSec))
	{
		return true;
	}
	//如果后面三张为三重张或三连张
	vectTempFir.clear();
	vectTempFir.insert(vectTempFir.begin(), vectValue.begin(), vectValue.begin() + 9);
	vectTempSec.clear();
	vectTempSec.insert(vectTempSec.begin(), vectValue.begin() + 9, vectValue.end());
	if (CheckMahjongNin(vectTempFir) && CheckMahjongThr(vectTempSec))
	{
		return true;
	}
	//122333444556
	int temp[11] = { 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1 };
	for (int i = 0; i < vectValue.size() - 1; i++)
	{
		if (vectValue.at(i) + temp[i] == vectValue.at(i + 1))
		{
			if (i == vectValue.size() - 2)
			{
				return true;
			}
			continue;
		}
		else
		{
			break;
		}
	}

	//对分为两半
	vectTempFir.clear();
	vectTempFir.insert(vectTempFir.begin(), vectValue.begin(), vectValue.begin() + 6);
	vectTempSec.clear();
	vectTempSec.insert(vectTempSec.begin(), vectValue.begin() + 6, vectValue.end());
	if (CheckMahjongSix(vectTempFir) && CheckMahjongSix(vectTempSec))
	{
		return true;
	}

	return false;
}

bool CHand::CheckMahjongZii(const vector<int> vectValue)
{
	int nSize = vectValue.size();
	if (nSize < 3 || nSize % 3 != 0)
	{
		return false;
	}

	int nCount = 0;
	for (int i = 0;i < nSize; i = i + 3)
	{
		if (vectValue.at(i) == vectValue.at(i + 1) && vectValue.at(i + 1) == vectValue.at(i + 2))
		{
			nCount++;
		}
		if (nCount == nSize / 3)
		{
			return true;
		}
	}

	return false;
}

bool CHand::CheckMahjongDui(const vector<int> vectValue)
{
	int nSize = vectValue.size();
	if (14 != nSize)
	{
		return false;
	}
	int nCount = 0;
	for (int i = 0; i < nSize; i = i + 2)
	{
		if (vectValue.at(i) == vectValue.at(i + 1))
		{
			nCount++;
		}
		if (7 == nCount)
		{
			return true;
		}
	}
	return false;
}

bool CHand::CheckMahjongHu()
{
	int nSize = m_vectMahjongHand.size();
	int i = 0;
	vector<int> vectHand;
	if (2 == nSize)
	{
		if (m_vectMahjongHand.at(0) == m_vectMahjongHand.at(1))
		{
			return true;
		}
	}
	while (i < nSize - 1)
	{
		if (!vectHand.empty())
		{
			vectHand.clear();
			
		}
		vectHand.insert(vectHand.begin(), m_vectMahjongHand.begin(), m_vectMahjongHand.end());

		if (vectHand.at(i) == vectHand.at(i + 1))
		{
			int temp = vectHand.at(i);
			vectHand.erase(vectHand.begin() + i);
			vectHand.erase(vectHand.begin() + i);

			//把字和万都分开来
			vector<int> vectWan;
			vector<int> vectZi;
			int nTemp = vectHand.size();
			for (int j = 0; j < nTemp; j++)
			{
				if (vectHand.at(j) <= 9)
				{
					vectWan.push_back(vectHand.at(j));
				}
				else
				{
					vectZi.push_back(vectHand.at(j));
				}
			}

			if (0 == vectWan.size())
			{
				if (!CheckMahjongZii(vectZi))
				{
					i++;
					continue;
				}
				else
				{
					SetJaing(temp);
					return true;
				}
			}

			if (0 != vectZi.size())
			{
				if (!CheckMahjongZii(vectZi))
				{
					i++;
					continue;
				}
			}

			switch (vectWan.size())
			{
			case PAI_THR:
				if (CheckMahjongThr(vectWan))
				{
					SetJaing(temp);
					return true;
				}
				break;
			case PAI_SIX:
				if (CheckMahjongSix(vectWan))
				{
					SetJaing(temp);
					return true;
				}
				break;
			case PAI_NIN:
				if (CheckMahjongNin(vectWan))
				{
					SetJaing(temp);
					return true;
				}
				break;
			case PAI_TWL:
				if (CheckMahjongTwl(vectWan))
				{
					SetJaing(temp);
					return true;
				}
				break;
			default:
				break;
			}
		}
		i++;
	}
	if (CheckMahjongDui(m_vectMahjongHand))
	{
		return true;
	}

	return false;
}

vector<int> CHand::CheckMahjongTing()
{
	vector<int> vectTing;
	for (int i = 1; i <= 16 ; i++)
	{
		HandAddMahjong(i);
		if (CheckMahjongHu())
		{
			vectTing.push_back(i);
		}
		DeleteMahjong(i);
	}
	
	return vectTing;
}



vector<int> CHand::GetVectHand()
{
	return m_vectMahjongHand;
}

vector<MahjongChi> CHand::GetVectChi()
{
	return m_vectMahjongChi;
}

vector<MahjongPeng> CHand::GetVectPeng()
{
	return m_vectMahjongPeng;
}

vector<MahjongGang> CHand::GetVectGang()
{
	return m_vectMahjongGang;
}

void CHand::CleanMahjongChi()
{
	if (!m_vectMahjongChi.empty())
	{
		m_vectMahjongChi.clear();
	}
}

void CHand::CleanMahjongPeng()
{
	if (!m_vectMahjongPeng.empty())
	{
		m_vectMahjongPeng.clear();
	}
}

void CHand::CleanMahjongGang()
{
	if (!m_vectMahjongGang.empty())
	{
		m_vectMahjongGang.clear();
	}
}

CHand &CHand::operator = (const CHand &hand)
{
	if (this == &hand)
	{
		return *this;
	}
	m_vectMahjongHand.insert(m_vectMahjongHand.begin(), hand.m_vectMahjongHand.begin(), hand.m_vectMahjongHand.end());

	return *this;
}


void CHand::SetJaing(int nIndex)
{
	m_nMahjongJiang = nIndex;
}


int CHand::GetJiang()
{
	return  m_nMahjongJiang;
}


