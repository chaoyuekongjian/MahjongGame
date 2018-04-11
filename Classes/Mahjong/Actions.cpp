
#include "Actions.h"


CActions::CActions()
{
	m_nMahjongJiang = 0;
	m_nMahjongFan = 0;
	m_bIsSelfHu = false;
}


CActions::~CActions()
{

}


void CActions::ActionAddMahjong(MahjongChi mahjongChi)
{
	m_vectAllMahjong.push_back(mahjongChi.m_nValueFir);
	m_vectAllMahjong.push_back(mahjongChi.m_nValueSec);
	m_vectAllMahjong.push_back(mahjongChi.m_nValueThd);
	m_vectMahjongChi.push_back(mahjongChi);
}

void CActions::ActionAddMahjong(MahjongPeng mahjongPeng)
{
	for (int i = 0; i < 3; i++)
	{
		m_vectAllMahjong.push_back(mahjongPeng.m_nValueFir);
	}
	m_vectMahjongPeng.push_back(mahjongPeng);
}

void CActions::ActionAddMahjong(MahjongGang mahjongGang)
{
	for (int i = 0; i < 4; i++)
	{
		m_vectAllMahjong.push_back(mahjongGang.m_nValueFir);
	}
	m_vectMahjongGang.push_back(mahjongGang);
}

void CActions::ActionAddMahjong(MahjongGangAn mahjongGangAn)
{
	for (int i = 0; i < 4; i++)
	{
		m_vectAllMahjong.push_back(mahjongGangAn.m_nValueFir);
	}
	m_vectMahjongGangAn.push_back(mahjongGangAn);
}


void CActions::ActionAddMahjong(vector<int> vectHand)
{
	m_vectAllMahjong.insert(m_vectAllMahjong.begin(), vectHand.begin(), vectHand.end());

}

void CActions::SetJiang(int nIndex)
{
	m_nMahjongJiang = nIndex;
}

void CActions::ChangePengToGang(int nIndex)
{
	for (int i = 0; i < m_vectMahjongPeng.size(); i++)
	{
		m_vectMahjongPeng.at(i).m_nValueFir = nIndex;
		m_vectMahjongPeng.erase(m_vectMahjongPeng.begin() + i);
		break;
	}

	MahjongGang mahjongGang;
	mahjongGang.m_nValueFir = nIndex;
	mahjongGang.m_nValueSec = nIndex;
	mahjongGang.m_nValueThd = nIndex;
	mahjongGang.m_nValueFth = nIndex;
	m_vectMahjongGang.push_back(mahjongGang);
	
	for (int i = 0; i < m_vectAllMahjong.size(); i++)
	{
		if (m_vectAllMahjong.at(i) == nIndex)
		{
			m_vectAllMahjong.insert(m_vectAllMahjong.begin() + i, nIndex);
			break;
		}
	}
}

void CActions::SetHandMahjong(vector<int> vectHand)
{
	if (!m_vectHanMahjong.empty())
	{
		m_vectHanMahjong.clear();
	}
	
	m_vectHanMahjong.insert(m_vectHanMahjong.begin(), vectHand.begin(), vectHand.end());
}

void CActions::SeparationJiang(vector<int> &vectHand)
{
	int nCount = 0;
	vector<int>::iterator iter;
	for (iter = vectHand.begin(); iter != vectHand.end();)
	{
		if (*iter == m_nMahjongJiang)
		{
			iter = vectHand.erase(iter);
			nCount++;
			if (2 == nCount)
			{
				break;
			}
		}
		else
		{
			iter++;
		}
	}
}

void CActions::SetIsSelfHu(bool bValue)
{
	m_bIsSelfHu = bValue;
}



CActions &CActions::operator = (const CActions &others)
{
	if (this == &others)
	{
		return *this;
	}
	m_vectHanMahjong.insert(m_vectHanMahjong.begin(), others.m_vectHanMahjong.begin(), others.m_vectHanMahjong.end());
	m_vectAllMahjong.insert(m_vectAllMahjong.begin(), others.m_vectAllMahjong.begin(), others.m_vectAllMahjong.end());
	m_vectMahjongChi.insert(m_vectMahjongChi.begin(), others.m_vectMahjongChi.begin(), others.m_vectMahjongChi.end());
	m_vectMahjongPeng.insert(m_vectMahjongPeng.begin(), others.m_vectMahjongPeng.begin(), others.m_vectMahjongPeng.end());
	m_vectMahjongGang.insert(m_vectMahjongGang.begin(), others.m_vectMahjongGang.begin(), others.m_vectMahjongGang.end());
	m_vectMahjongGangAn.insert(m_vectMahjongGangAn.begin(), others.m_vectMahjongGangAn.begin(), others.m_vectMahjongGangAn.end());

	return *this;
}


void CActions::CheckMahjongFan()
{
	if (!m_vectMahjongName.empty())
	{
		m_vectMahjongName.clear();
	}

	if (CheckHu88Dasixi())
	{
		m_nMahjongFan += FAN_DASIXI;
		m_sMahjongName = "大四喜";
		m_vectMahjongName.push_back("大四喜");
		if (CheckHu88Sigang())
		{
			m_nMahjongFan += FAN_SIGANG;
			m_vectMahjongName.push_back("四杠");
		}
		else
		{
			if (CheckHu32Sangang())
			{
				m_nMahjongFan += FAN_SANGANG;
				m_vectMahjongName.push_back("三杠");
			}
			else
			{
				if (CheckHu4Shuangminggang())
				{
					m_nMahjongFan += FAN_SHUANGMINGGANG;
					m_vectMahjongName.push_back("双明杠");
				}
			}

		}
		if (CheckHu64Ziyise())
		{
			m_nMahjongFan += FAN_ZIYISE;
			m_vectMahjongName.push_back("字一色");
		}
		if (CheckHu64Sianke())
		{
			m_nMahjongFan += FAN_SIANKE;
			m_vectMahjongName.push_back("四暗刻");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}
		
		return;
	}

	if (CheckHu88Dasanyuan())
	{
		m_nMahjongFan = FAN_DASANYUAN;
		m_sMahjongName = "大三元";
		m_vectMahjongName.push_back("大三元");
		if (CheckHu88Sigang())
		{
			m_nMahjongFan += FAN_SIGANG;
			m_vectMahjongName.push_back("四杠");
		}
		else
		{
			if (CheckHu32Sangang())
			{
				m_nMahjongFan += FAN_SANGANG;
				m_vectMahjongName.push_back("三杠");
			}
			else
			{
				if (CheckHu4Shuangminggang())
				{
					m_nMahjongFan += FAN_SHUANGMINGGANG;
					m_vectMahjongName.push_back("双明杠");
				}
			}
		}
		if (4 == m_vectMahjongGangAn.size())
		{
			m_nMahjongFan += FAN_SIANKE;
			m_vectMahjongName.push_back("四暗刻");
		}
		if (CheckHu64Ziyise())
		{
			m_nMahjongFan += FAN_ZIYISE;
			m_vectMahjongName.push_back("字一色");
		}
		if (CheckHu32Hunyaojiu())
		{
			m_nMahjongFan += FAN_HUNYAOJIU;
			m_vectMahjongName.push_back("混幺九");
		}
		else
		{
			if (CheckHu6Pengpenghu())
			{
				m_nMahjongFan += FAN_PENGPENGHE;
				m_vectMahjongName.push_back("碰碰和");
			}
		}
		if (CheckHu24Qidui())
		{
			m_nMahjongFan += FAN_QIDUI;
			m_vectMahjongName.push_back("七对");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu88Jiulianbaodeng())
	{
		m_nMahjongFan = FAN_JIULIANBAODENG;
		m_sMahjongName = "九莲宝灯";
		m_vectMahjongName.push_back("九莲宝灯");
		if (CheckHu16Qinglong())
		{
			m_nMahjongFan = FAN_QINGLONG;
			m_sMahjongName = "清龙";
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}
		
		return;
	}

	if (CheckHu88Sigang())
	{
		m_nMahjongFan = FAN_SIGANG;
		m_sMahjongName = "四杠";
		m_vectMahjongName.push_back("四杠");
		if (CheckHu88Baiwanshi())
		{
			m_nMahjongFan += FAN_BAIWANSHI;
			m_vectMahjongName.push_back("百万石");
		}
		if (CheckHu64Xiaosixi())
		{
			m_nMahjongFan += FAN_XIAOSIXI;
			m_vectMahjongName.push_back("小四喜");
		}
		if (CheckHu64Xiaosanyuan())
		{
			m_nMahjongFan += FAN_XIAOSNYUAN;
			m_vectMahjongName.push_back("小三元");
		}
		if (4 == m_vectMahjongGangAn.size())
		{
			m_nMahjongFan += FAN_SIANKE;
			m_vectMahjongName.push_back("四暗刻");
		}
		if (3 == m_vectMahjongGangAn.size())
		{
			m_nMahjongFan += FAN_SANANKE;
			m_vectMahjongName.push_back("三暗刻");
		}
		if (CheckHu24Qingyise())
		{
			m_nMahjongFan += FAN_QINGYISE;
			m_vectMahjongName.push_back("清一色");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu32Hunyaojiu())
		{
			m_nMahjongFan += FAN_HUNYAOJIU;
			m_vectMahjongName.push_back("混幺九");
		}
		else
		{
			if (CheckHu6Pengpenghu())
			{
				m_nMahjongFan += FAN_PENGPENGHE;
				m_vectMahjongName.push_back("碰碰和");
			}
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu88Lianqidui())
	{
		m_nMahjongFan = FAN_LIANQIDUI;
		m_sMahjongName = "连七对"; 
		m_vectMahjongName.push_back("连七对");
		return;
	}

	if (CheckHu88Baiwanshi())
	{
		m_nMahjongFan = FAN_BAIWANSHI;
		m_sMahjongName = "百万石";
		m_vectMahjongName.push_back("百万石");
		if (CheckHu64Sianke())
		{
			m_nMahjongFan += FAN_SIANKE;
			m_vectMahjongName.push_back("四暗刻");
		}
		if (CheckHu32Hunyaojiu())
		{
			m_nMahjongFan += FAN_HUNYAOJIU;
			m_vectMahjongName.push_back("混幺九");
		}
		else
		{
			if (CheckHu6Pengpenghu())
			{
				m_nMahjongFan += FAN_PENGPENGHE;
				m_vectMahjongName.push_back("碰碰和");
			}
		}
		if (CheckHu12Dayuwu())
		{
			m_nMahjongFan += FAN_DAYUWU;
			m_vectMahjongName.push_back("大于五");
		}
		if (CheckHu12Xiaoyuwu())
		{
			m_nMahjongFan += FAN_XIAOYUWU;
			m_vectMahjongName.push_back("小于五");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu64Xiaosixi())
	{
		m_nMahjongFan = FAN_XIAOSIXI;
		m_sMahjongName = "小四喜";
		m_vectMahjongName.push_back("小四喜");
		if (CheckHu64Sianke())
		{
			m_nMahjongFan += FAN_SIANKE;
			m_vectMahjongName.push_back("四暗刻");
		}
		if (CheckHu64Ziyise())
		{
			m_nMahjongFan += FAN_ZIYISE;
			m_vectMahjongName.push_back("字一色");
		}
		if (CheckHu32Sangang())
		{
			m_nMahjongFan += FAN_SANGANG;
			m_vectMahjongName.push_back("三杠");
		}
		else
		{
			if (CheckHu4Shuangminggang())
			{
				m_nMahjongFan += FAN_SHUANGMINGGANG;
				m_vectMahjongName.push_back("双明杠");
			}
		}
		if (CheckHu24Qidui())
		{
			m_nMahjongFan += FAN_QIDUI;
			m_vectMahjongName.push_back("七对");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu32Hunyaojiu())
		{
			m_nMahjongFan += FAN_HUNYAOJIU;
			m_vectMahjongName.push_back("混幺九");
		}
		else
		{
			if (CheckHu6Pengpenghu())
			{
				m_nMahjongFan += FAN_PENGPENGHE;
				m_vectMahjongName.push_back("碰碰和");
			}
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu64Xiaosanyuan())
	{
		m_nMahjongFan = FAN_XIAOSNYUAN;
		m_sMahjongName = "小三元";
		m_vectMahjongName.push_back("小三元");
		if (CheckHu64Sianke())
		{
			m_nMahjongFan += FAN_SIANKE;
			m_vectMahjongName.push_back("四暗刻");
		}
		if (CheckHu64Ziyise())
		{
			m_nMahjongFan += FAN_ZIYISE;
			m_vectMahjongName.push_back("字一色");
		}
		if (CheckHu32Sangang())
		{
			m_nMahjongFan += FAN_SANGANG;
			m_vectMahjongName.push_back("三杠");
		}
		else
		{
			if (CheckHu4Shuangminggang())
			{
				m_nMahjongFan += FAN_SHUANGMINGGANG;
				m_vectMahjongName.push_back("双明杠");
			}
		}
		if (CheckHu24Qidui())
		{
			m_nMahjongFan += FAN_QIDUI;
			m_vectMahjongName.push_back("七对");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu32Hunyaojiu())
		{
			m_nMahjongFan += FAN_HUNYAOJIU;
			m_vectMahjongName.push_back("混幺九");
		}
		else
		{
			if (CheckHu6Pengpenghu())
			{
				m_nMahjongFan += FAN_PENGPENGHE;
				m_vectMahjongName.push_back("碰碰和");
			}
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu64Ziyise())
	{
		m_nMahjongFan = FAN_ZIYISE;
		m_sMahjongName = "字一色";
		m_vectMahjongName.push_back("字一色");
		if (CheckHu64Sianke())
		{
			m_nMahjongFan += FAN_SIANKE;
			m_vectMahjongName.push_back("四暗刻");
		}
		if (CheckHu32Sangang())
		{
			m_nMahjongFan += FAN_SANGANG;
			m_vectMahjongName.push_back("三杠");
		}
		else
		{
			if (CheckHu4Shuangminggang())
			{
				m_nMahjongFan += FAN_SHUANGMINGGANG;
				m_vectMahjongName.push_back("双明杠");
			}
		}
		if (CheckHu24Qidui())
		{
			m_nMahjongFan += FAN_QIDUI;
			m_vectMahjongName.push_back("七对");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu64Sianke())
	{
		m_nMahjongFan = FAN_SIANKE;
		m_sMahjongName = "四暗刻";
		m_vectMahjongName.push_back("四暗刻");
		if (CheckHu48Yisesitongshun())
		{
			m_nMahjongFan += FAN_YISESITONGSHUN;
			m_vectMahjongName.push_back("一色四同顺");
		}
		if (CheckHu48Yisesijiegao())
		{
			m_nMahjongFan += FAN_YISESIJIEGAO;
			m_vectMahjongName.push_back("一色四节高");
		}
		if (CheckHu24Qingyise())
		{
			m_nMahjongFan += FAN_QINGYISE;
			m_vectMahjongName.push_back("清一色");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu64Yiseshuanglong())
	{
		m_nMahjongFan = FAN_YISESHUANGLONG;
		m_sMahjongName = "一色双龙会";
		m_vectMahjongName.push_back("一色双龙会");
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu48Yisesitongshun())
	{
		m_nMahjongFan = FAN_YISESITONGSHUN;
		m_sMahjongName = "一色四同顺";
		m_vectMahjongName.push_back("一色四同顺");
		if (CheckHu24Qingyise())
		{
			m_nMahjongFan += FAN_QINGYISE;
			m_vectMahjongName.push_back("清一色");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu12Xiaoyuwu())
		{
			m_nMahjongFan += FAN_XIAOYUWU;
			m_vectMahjongName.push_back("小于五");
		}
		if (CheckHu12Dayuwu())
		{
			m_nMahjongFan += FAN_DAYUWU;
			m_vectMahjongName.push_back("大于五");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Pinghu())
		{
			m_nMahjongFan += FAN_PINGHU;
			m_vectMahjongName.push_back("平和");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu48Yisesijiegao())
	{
		m_nMahjongFan = FAN_YISESIJIEGAO;
		m_sMahjongName = "一色四节高";
		m_vectMahjongName.push_back("一色四节高");
		if (CheckHu24Qingyise())
		{
			m_nMahjongFan += FAN_QINGYISE;
			m_vectMahjongName.push_back("清一色");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu12Xiaoyuwu())
		{
			m_nMahjongFan += FAN_XIAOYUWU;
			m_vectMahjongName.push_back("小于五");
		}
		if (CheckHu12Dayuwu())
		{
			m_nMahjongFan += FAN_DAYUWU;
			m_vectMahjongName.push_back("大于五");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu32Yisesibugao())
	{
		m_nMahjongFan = FAN_YISESIBUGAO;
		m_sMahjongName = "一色四步高";
		m_vectMahjongName.push_back("一色四步高");
		if (CheckHu24Qingyise())
		{
			m_nMahjongFan += FAN_QINGYISE;
			m_vectMahjongName.push_back("清一色");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Pinghu())
		{
			m_nMahjongFan += FAN_PINGHU;
			m_vectMahjongName.push_back("平和");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}
		

		return;
	}

	if (CheckHu32Sangang())
	{
		m_nMahjongFan = FAN_SANGANG;
		m_sMahjongName = "三杠";
		m_vectMahjongName.push_back("三杠");
		if (CheckHu24Qingyise())
		{
			m_nMahjongFan += FAN_QINGYISE;
			m_vectMahjongName.push_back("清一色");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu6Shuangjianke())
		{
			m_nMahjongFan += FAN_SHUANGJIANKE;
			m_vectMahjongName.push_back("双箭刻");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu32Hunyaojiu())
	{
		m_nMahjongFan = FAN_HUNYAOJIU;
		m_sMahjongName = "混幺九";
		m_vectMahjongName.push_back("混幺九");
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu6Shuangjianke())
		{
			m_nMahjongFan += FAN_SHUANGJIANKE;
			m_vectMahjongName.push_back("双箭刻");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}


		return;
	}

	if (CheckHu24Qidui())
	{
		m_nMahjongFan = FAN_QIDUI;
		m_sMahjongName = "七对";
		m_vectMahjongName.push_back("七对");
		if (CheckHu24Qingyise())
		{
			m_nMahjongFan += FAN_QINGYISE;
			m_vectMahjongName.push_back("清一色");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Pinghu())
		{
			m_nMahjongFan += FAN_PINGHU;
			m_vectMahjongName.push_back("平和");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu24Qingyise())
	{
		m_nMahjongFan = FAN_QINGYISE;
		m_sMahjongName = "清一色";
		m_vectMahjongName.push_back("清一色");
		if (CheckHu16Qinglong())
		{
			m_nMahjongFan += FAN_QINGLONG;
			m_vectMahjongName.push_back("清龙");
		}
		if (CheckHu24Yisesantongshun())
		{
			m_nMahjongFan += FAN_YISESANTONGSHUN;
			m_vectMahjongName.push_back("一色三同顺");
		}
		if (CheckHu16Yisesanbugao())
		{
			m_nMahjongFan += FAN_YISESANBUGAO;
			m_vectMahjongName.push_back("一色三步高");
		}
		if (CheckHu12Xiaoyuwu())
		{
			m_nMahjongFan += FAN_XIAOYUWU;
			m_vectMahjongName.push_back("小于五");
		}
		if (CheckHu12Dayuwu())
		{
			m_nMahjongFan += FAN_DAYUWU;
			m_vectMahjongName.push_back("大于五");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Pinghu())
		{
			m_nMahjongFan += FAN_PINGHU;
			m_vectMahjongName.push_back("平和");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu2Duanyao())
		{
			m_nMahjongFan += FAN_DUANYAO;
			m_vectMahjongName.push_back("断幺");
		}
		if (!CheckHu16Qinglong())
		{
			if (CheckHu1Lianliu())
			{
				m_nMahjongFan += FAN_LIANLIU;
				m_vectMahjongName.push_back("连六");
			}
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}


		return;
	}

	if (CheckHu24Yisesantongshun())
	{
		m_nMahjongFan = FAN_YISESANTONGSHUN;
		m_sMahjongName = "一色三同顺";
		m_vectMahjongName.push_back("一色三同顺");
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu2Pinghu())
		{
			m_nMahjongFan += FAN_PINGHU;
			m_vectMahjongName.push_back("平和");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}


		return;
	}

	if (CheckHu48Yisesijiegao())
	{
		m_nMahjongFan = FAN_YISESANJIEGAO;
		m_sMahjongName = "一色三节高";
		m_vectMahjongName.push_back("一色三节高");
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}


		return;
	}

	if (CheckHu16Qinglong())
	{
		m_nMahjongFan = FAN_QINGLONG;
		m_sMahjongName = "清龙";
		m_vectMahjongName.push_back("清龙");
		if (CheckHu16Yisesanbugao())
		{
			m_nMahjongFan += FAN_YISESANBUGAO;
			m_vectMahjongName.push_back("一色三步高");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu2Pinghu())
		{
			m_nMahjongFan += FAN_PINGHU;
			m_vectMahjongName.push_back("平和");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu16Yisesanbugao())
	{
		m_nMahjongFan = FAN_YISESANBUGAO;
		m_sMahjongName = "一色三步高";
		m_vectMahjongName.push_back("一色三步高");
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu2Pinghu())
		{
			m_nMahjongFan += FAN_PINGHU;
			m_vectMahjongName.push_back("平和");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		

		return;
	}

	if (CheckHu16Sananke())
	{
		m_nMahjongFan = FAN_SANANKE;
		m_sMahjongName = "三暗刻";
		m_vectMahjongName.push_back("三暗刻");
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu6Shuangjianke())
		{
			m_nMahjongFan += FAN_SHUANGJIANKE;
			m_vectMahjongName.push_back("双箭刻");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}


		return;
	}

	/*if (CheckHu12Dayuwu())
	{
		m_nMahjongFan = FAN_DAYUWU;
		m_sMahjongName = "大于五";
		return;
	}
	if (CheckHu12Xiaoyuwu())
	{
		m_nMahjongFan = FAN_XIAOYUWU;
		m_sMahjongName = "小于五";
		return;
	}*/

	if (CheckHu12Sanfengke())
	{
		m_nMahjongFan = FAN_SANFENGKE;
		m_sMahjongName = "三风刻";
		m_vectMahjongName.push_back("三风刻");
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu6Pengpenghu())
	{
		m_nMahjongFan = FAN_PENGPENGHE;
		m_sMahjongName = "碰碰和";
		m_vectMahjongName.push_back("碰碰和");
		if (CheckHu6Shuangjianke())
		{
			m_nMahjongFan += FAN_SHUANGJIANKE;
			m_vectMahjongName.push_back("双箭刻");
		}
		if (CheckHu6Hunyise())
		{
			m_nMahjongFan += FAN_HUNYISE;
			m_vectMahjongName.push_back("混一色");
		}
		if (CheckHu6Shuangangang())
		{
			m_nMahjongFan += FAN_SHUANGANGANG;
			m_vectMahjongName.push_back("双暗杠");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}

		return;
	}

	if (CheckHu6Hunyise())
	{
		m_nMahjongFan = FAN_HUNYISE;
		m_sMahjongName = "混一色";
		m_vectMahjongName.push_back("混一色");
		if (CheckHu6Shuangjianke())
		{
			m_nMahjongFan += FAN_SHUANGJIANKE;
			m_vectMahjongName.push_back("双箭刻");
		}
		if (CheckHu6Shuangangang())
		{
			m_nMahjongFan += FAN_SHUANGANGANG;
			m_vectMahjongName.push_back("双暗杠");
		}
		if (CheckHu6Quanqiuren())
		{
			m_nMahjongFan += FAN_QUANQIUREN;
			m_vectMahjongName.push_back("全求人");
		}
		if (CheckHu4Shuanganke())
		{
			m_nMahjongFan += FAN_SHUANGANKE;
			m_vectMahjongName.push_back("双暗刻");
		}
		if (CheckHu4Buqiuren())
		{
			m_nMahjongFan += FAN_BUQIUREN;
			m_vectMahjongName.push_back("不求人");
		}
		if (CheckHu2Jianke())
		{
			m_nMahjongFan += FAN_JIANKE;
			m_vectMahjongName.push_back("箭刻");
		}
		if (CheckHu2Siguiyi())
		{
			m_nMahjongFan += FAN_SIGUIYI;
			m_vectMahjongName.push_back("四归一");
		}
		if (CheckHu1Lianliu())
		{
			m_nMahjongFan += FAN_LIANLIU;
			m_vectMahjongName.push_back("连六");
		}
		if (CheckHu1Zimo())
		{
			m_nMahjongFan += FAN_ZIMO;
			m_vectMahjongName.push_back("自摸");
		}


		return;
	}

}

int CActions::GetMahjongFan()
{
	return m_nMahjongFan;
}


std::vector<string> CActions::GetVectMahjongName()
{
	return m_vectMahjongName;
}



bool CActions::CheckHu88Dasixi()
{
	int nSize = m_vectAllMahjong.size();
	int nCount = 0;
	for (int i = 10; i < 14; i++)
	{
		int nMark = 0;
		for (int j = 0; j < nSize; j++)
		{
			if (m_vectAllMahjong.at(j) == i)
			{
				nMark++;
			}
			if (3 <= nMark)
			{
				nCount++;
				break;
			}
		}

		if (4 == nCount)
		{
			//大四喜
			return true;
		}
	}
	
	return false;
}

bool CActions::CheckHu88Dasanyuan()
{
	int nSize = m_vectAllMahjong.size();
	int nCount = 0;
	for (int i = 14; i < 17; i++)
	{
		int nMark = 0;
		for (int j = 0; j < nSize; j++)
		{
			if (m_vectAllMahjong.at(j) == i)
			{
				nMark++;
			}
			if (3 <= nMark)
			{
				nCount++;
				break;
			}
		}
		if (3 == nCount)
		{
			//大三元
			return true;
		}
	}
	
	return false;
}

bool CActions::CheckHu88Jiulianbaodeng()
{
	if (14 != m_vectAllMahjong.size())
	{
		return false;
	}

	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	sort(vectMahjong.begin(), vectMahjong.end());
	for (int i = 0; i < vectMahjong.size(); i++)
	{
		int temp = vectMahjong.at(i);
		vectMahjong.erase(vectMahjong.begin() + i);
		if (vectMahjong.at(0) == vectMahjong.at(1) && vectMahjong.at(1) == vectMahjong.at(2) && 1 == vectMahjong.at(0))
		{
			if (2 == vectMahjong.at(3) && 3 == vectMahjong.at(4) && 4 == vectMahjong.at(5) && 5 == vectMahjong.at(6) && 6 == vectMahjong.at(7) && 7 == vectMahjong.at(8) && 8 == vectMahjong.at(9))
			{
				if (vectMahjong.at(10) == vectMahjong.at(11) && vectMahjong.at(11) == vectMahjong.at(12) && 9 == vectMahjong.at(11))
				{
					if (9 >= temp)
					{
						return true;
					}
				}
			}
		} 
		vectMahjong.push_back(temp);
		sort(vectMahjong.begin(), vectMahjong.end());
	}

	return false;
}

bool CActions::CheckHu88Sigang()
{
	if (4 == m_vectMahjongGang.size() + m_vectMahjongGangAn.size())
	{
		return true;
	}

	return false;
}

bool CActions::CheckHu88Lianqidui()
{
	//检查是否是七连对	
	vector<int>::iterator iter;
	for (iter = m_vectAllMahjong.begin(); iter != m_vectAllMahjong.end(); iter++)
	{
		if (9 < *iter)
		{
			return false;
		}
	}
	int nSize = m_vectAllMahjong.size();
	if (14 != nSize)
	{
		return false;
	}
	int temp[] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
	for (int i = 0; i < nSize - 1; i++)
	{
		if (m_vectAllMahjong.at(i) + temp[i] == m_vectAllMahjong.at(i + 1))
		{
			if (i == nSize - 2)
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool CActions::CheckHu88Baiwanshi()
{
	int nSum = 0;
	for (int i = 0; i < m_vectAllMahjong.size(); i++)
	{
		if (9 < m_vectAllMahjong.at(i))
		{
			return false;
		}
		else
		{
			nSum += m_vectAllMahjong.at(i);
		}
	}

	if (100 <= nSum)
	{
		return true;
	}
	
	return false;
}


//64番牌种
bool CActions::CheckHu64Xiaosixi()
{
	if (10 > m_nMahjongJiang || 13 < m_nMahjongJiang)
	{
		return false;
	}
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	SeparationJiang(vectMahjong);
	int nCount = 0;
	for (int i = 10; i < 14; i++)
	{
		int nMark = 0;
		for (int j = 0; j < vectMahjong.size(); j++)
		{
			if (vectMahjong.at(j) == i)
			{
				nMark++;
			}
			if (3 <= nMark)
			{
				nCount++;
				break;
			}
		}
		if (3 == nCount)
		{
			//小四喜
			return true;
		}
	}

	return false;
}

bool CActions::CheckHu64Xiaosanyuan()
{
	if (14 > m_nMahjongJiang || 16 < m_nMahjongJiang)
	{
		return false;
	}
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	SeparationJiang(vectMahjong);
	int nCount = 0;
	for (int i = 14; i < 17; i++)
	{
		int nMark = 0;
		for (int j = 0; j < vectMahjong.size(); j++)
		{
			if (vectMahjong.at(j) == i)
			{
				nMark++;
			}
			if (3 <= nMark)
			{
				nCount++;
				break;
			}
		}
		if (2 == nCount)
		{
			//小三元
			return true;
		}
	}

	return false;
}

bool CActions::CheckHu64Ziyise()
{
	vector<int>::iterator iter;
	for (iter = m_vectAllMahjong.begin(); iter != m_vectAllMahjong.end(); iter++)
	{
		if (9 >= *iter)
		{
			return false;
		}
	}

	return true;
}

bool CActions::CheckHu64Sianke()
{
	int nCount = 0;
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectHanMahjong.begin(), m_vectHanMahjong.end());
	SeparationJiang(vectMahjong);
	if (12 != vectMahjong.size() + m_vectMahjongGangAn.size() * 3)
	{
		return false;
	}
	for (int i = 0; i < vectMahjong.size(); i = i + 3)
	{
		if (!(vectMahjong.at(i) == vectMahjong.at(i + 1) && vectMahjong.at(i + 1) == vectMahjong.at(i + 2)))
		{
			return false;
		}
	}

	return true;
}

bool CActions::CheckHu64Yiseshuanglong()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	sort(vectMahjong.begin(), vectMahjong.end()); 
	if (14 != vectMahjong.size() && CheckHu24Qidui())
	{
		return false;
	}
	if (1 == vectMahjong.at(0) && 2 == vectMahjong.at(2) && 3 == vectMahjong.at(4))
	{
		if (5 == vectMahjong.at(6))
		{
			if (7 == vectMahjong.at(8) && 8 == vectMahjong.at(10) && vectMahjong.at(12))
			{
				return true;
			}
		}
	}

	return false;
}

bool CActions::CheckHu48Yisesitongshun()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	sort(vectMahjong.begin(), vectMahjong.end());
	SeparationJiang(vectMahjong);
	if (12 != vectMahjong.size() || m_vectMahjongPeng.empty())
	{
		return false;
	}
	int nCount = 0;
	int temp[] = { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0};
	for (int i = 0; i < vectMahjong.size() - 1; i++)
	{
		if (vectMahjong.at(i) + temp[i] == vectMahjong.at(i + 1))
		{
			if (i == vectMahjong.size() - 2)
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool CActions::CheckHu48Yisesijiegao()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	sort(vectMahjong.begin(), vectMahjong.end());
	SeparationJiang(vectMahjong);
	if (12 != vectMahjong.size() || !m_vectMahjongPeng.empty())
	{
		return false;
	}

	int nCount = 0;
	for (int i = 0; i < vectMahjong.size(); i = i + 3)
	{
		if (!(vectMahjong.at(0) + 1 == vectMahjong.at(3) && vectMahjong.at(3) + 1 == vectMahjong.at(6) && vectMahjong.at(6) + 1 == vectMahjong.at(9)))
		{
			return false;
		}
		if (vectMahjong.at(i) == vectMahjong.at(i + 1) && vectMahjong.at(i + 1) == vectMahjong.at(i + 2))
		{
			if (0 < vectMahjong.at(i) && 10 > vectMahjong.at(i))
			{
				nCount++;
			}
			if (4 == nCount)
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool CActions::CheckHu32Yisesibugao()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	sort(vectMahjong.begin(), vectMahjong.end());
	SeparationJiang(vectMahjong); 
	if (12 != vectMahjong.size())
	{
		return false;
	}

	for (int i = 0; i < vectMahjong.size(); i++)
	{
		if (9 < vectMahjong.at(i))
		{
			return false;
		}
	}

	int temp[11] = { 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1 };

	MahjongChi mahjongChiFir;
	mahjongChiFir.m_nValueFir = vectMahjong.at(0);
	mahjongChiFir.m_nValueSec = 0;
	mahjongChiFir.m_nValueThd = 0;
	vectMahjong.erase(vectMahjong.begin());
	for (int i = 0; i < vectMahjong.size(); i++)
	{
		if (mahjongChiFir.m_nValueFir + 1 == vectMahjong.at(i) && 0 == mahjongChiFir.m_nValueSec)
		{
			mahjongChiFir.m_nValueSec = vectMahjong.at(i);
			vectMahjong.erase(vectMahjong.begin() + i);
			i--;
			continue;
		}
		if (0 != mahjongChiFir.m_nValueSec && mahjongChiFir.m_nValueSec + 1 == vectMahjong.at(i))
		{
			mahjongChiFir.m_nValueThd = vectMahjong.at(i);
			vectMahjong.erase(vectMahjong.begin() + i);
			break;
		}
	}

	MahjongChi mahjongChiSec;
	mahjongChiSec.m_nValueFir = vectMahjong.at(0);
	mahjongChiSec.m_nValueSec = 0;
	mahjongChiSec.m_nValueThd = 0;
	vectMahjong.erase(vectMahjong.begin());
	for (int i = 0; i < vectMahjong.size(); i++)
	{
		if (mahjongChiSec.m_nValueFir + 1 == vectMahjong.at(i) && 0 == mahjongChiSec.m_nValueSec)
		{
			mahjongChiSec.m_nValueSec = vectMahjong.at(i);
			vectMahjong.erase(vectMahjong.begin() + i);
			i--;
			continue;
		}
		if (0 != mahjongChiSec.m_nValueSec && mahjongChiSec.m_nValueSec + 1 == vectMahjong.at(i))
		{
			mahjongChiSec.m_nValueThd = vectMahjong.at(i);
			vectMahjong.erase(vectMahjong.begin() + i);

			break;
		}
	}

	MahjongChi mahjongChiThd;
	mahjongChiThd.m_nValueFir = vectMahjong.at(0);
	mahjongChiThd.m_nValueSec = 0;
	mahjongChiThd.m_nValueThd = 0;
	vectMahjong.erase(vectMahjong.begin());
	for (int i = 0; i < vectMahjong.size(); i++)
	{
		if (mahjongChiThd.m_nValueFir + 1 == vectMahjong.at(i) && 0 == mahjongChiThd.m_nValueSec)
		{
			mahjongChiThd.m_nValueSec = vectMahjong.at(i);
			vectMahjong.erase(vectMahjong.begin() + i);
			i--;
			continue;
		}
		if (0 != mahjongChiThd.m_nValueSec && mahjongChiThd.m_nValueSec + 1 == vectMahjong.at(i))
		{
			mahjongChiThd.m_nValueThd = vectMahjong.at(i);
			//vect.erase(vect.begin() + i);
			break;
		}
	}

	MahjongChi mahjongChiTir;
	mahjongChiTir.m_nValueFir = vectMahjong.at(0);
	mahjongChiTir.m_nValueSec = 0;
	mahjongChiTir.m_nValueThd = 0;
	vectMahjong.erase(vectMahjong.begin());
	for (int i = 0; i < vectMahjong.size(); i++)
	{
		if (mahjongChiTir.m_nValueFir + 1 == vectMahjong.at(i) && 0 == mahjongChiTir.m_nValueSec)
		{
			mahjongChiTir.m_nValueSec = vectMahjong.at(i);
			vectMahjong.erase(vectMahjong.begin() + i);
			i--;
			continue;
		}
		if (0 != mahjongChiTir.m_nValueSec && mahjongChiTir.m_nValueSec + 1 == vectMahjong.at(i))
		{
			mahjongChiTir.m_nValueThd = vectMahjong.at(i);
			//vect.erase(vect.begin() + i);
			break;
		}
	}

	if (CheckChiIsLing(mahjongChiFir) && CheckChiIsLing(mahjongChiSec) && CheckChiIsLing(mahjongChiThd) && CheckChiIsLing(mahjongChiTir))
	{
		if (2 >= mahjongChiSec.m_nValueFir - mahjongChiFir.m_nValueFir && 2 >= mahjongChiThd.m_nValueFir - mahjongChiSec.m_nValueFir && 2 >= mahjongChiTir.m_nValueFir - mahjongChiThd.m_nValueFir)
		{
			return true;
		}
	}

	

	return false;
}

bool CActions::CheckHu32Sangang()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	sort(vectMahjong.begin(), vectMahjong.end());
	SeparationJiang(vectMahjong);

	int nMark = 0;
	int nCount = 0;
	for (int i = 0; i < vectMahjong.size() - 1; i++)
	{
		if (vectMahjong.at(i) == vectMahjong.at(i + 1))
		{
			nMark++;
		}
		else
		{
			nMark = 0;
		}
		if (3 == nMark)
		{
			nCount++;
			nMark = 0;
		}
		if (3 == nCount)
		{
			return true;
		}
	}

	return false;
}

bool CActions::CheckHu32Hunyaojiu()
{
	for (int i = 0; i < m_vectAllMahjong.size(); i++)
	{
		if (2 <= m_vectAllMahjong.at(i) && 9 > m_vectAllMahjong.at(i))
		{
			return false;
		}
	}
	vector<int> vectWan;
	vector<int> vectZi;
	for (int i = 0; i < m_vectAllMahjong.size(); i++)
	{
		if (9 < m_vectAllMahjong.at(i))
		{
			vectZi.push_back(m_vectAllMahjong.at(i));
		}
		else
		{
			vectWan.push_back(m_vectAllMahjong.at(i));
		}
	}

	if (0 < vectWan.size() && 0 < vectZi.size())
	{
		return true;
	}

	return false;
}



bool CActions::CheckHu24Qidui()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	sort(vectMahjong.begin(), vectMahjong.end());
	if (14 != vectMahjong.size())
	{
		return false;
	}
	for (int i = 0; i < vectMahjong.size() - 1; i = i + 2)
	{
		if (vectMahjong.at(i) != vectMahjong.at(i + 1))
		{
			return false;
		}
	}

	return true;
}


bool CActions::CheckHu24Qingyise()
{
	if (9 < m_nMahjongJiang)
	{
		return false;
	}
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	sort(vectMahjong.begin(), vectMahjong.end());
	SeparationJiang(vectMahjong);
	for (int i = 0; i < vectMahjong.size(); i++)
	{
		if (9 < vectMahjong.at(i))
		{
			return false;
		}
	}

	return true;
}


bool CActions::CheckHu24Yisesantongshun()
{
	//一色三同顺的条件：吃牌区域必须存在一组
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectHanMahjong.begin(), m_vectHanMahjong.end());
	//vectMahjong.insert(vectMahjong.end(), m_vectMahjongChi.begin(), m_vectMahjongChi.end());
	SeparationJiang(vectMahjong);
	if (9 > vectMahjong.size())
	{
		return false;
	}
	CMahjongTree mahjongTree(vectMahjong);
	vector<CMahjongData> vectData;
	vectData = mahjongTree.GetDateByLevel(9);
	int temp[] = { 1, 1, -2, 1, 1, -2, 1, 1 };
	for (int i = 0; i < vectData.size(); i++)
	{
		vector<int> vectTemp;
		vectTemp = vectData.at(i).GetData();
		for (int j = 0; j < vectTemp.size() - 1; j++)
		{
			if (vectTemp.at(j) + temp[j] == vectTemp.at(j + 1))
			{
				if (j == vectTemp.size() - 2)
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool CActions::CheckHu24Yisesanjiegao()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectHanMahjong.begin(), m_vectHanMahjong.end());
	for (int i = 0; i < m_vectMahjongPeng.size(); i++)
	{
		vectMahjong.push_back(m_vectMahjongPeng.at(i).m_nValueFir);
		vectMahjong.push_back(m_vectMahjongPeng.at(i).m_nValueSec);
		vectMahjong.push_back(m_vectMahjongPeng.at(i).m_nValueThd);
	}
	SeparationJiang(vectMahjong);
	sort(vectMahjong.begin(), vectMahjong.end());
	if (9 > vectMahjong.size())
	{
		return false;
	}
	CMahjongTree mahjongTree(vectMahjong);
	vector<CMahjongData> vectData;
	vectData = mahjongTree.GetDateByLevel(9);
	int temp[] = { 0, 0, 1, 0, 0, 1, 0, 0 };
	for (int i = 0; i < vectData.size(); i++)
	{
		vector<int> vectTemp;
		vectTemp = vectData.at(i).GetData();
		for (int j = 0; j < vectTemp.size() - 1; j++)
		{
			if (vectTemp.at(j) + temp[j] == vectTemp.at(j + 1))
			{
				if (j == vectTemp.size() - 2)
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}
	}
	


	return true;
}

bool CActions::CheckHu16Qinglong()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	sort(vectMahjong.begin(), vectMahjong.end());
	for (int i = 0; i < vectMahjong.size() - 1; i++)
	{
		if (vectMahjong.at(i) == vectMahjong.at(i + 1))
		{
			vectMahjong.erase(vectMahjong.begin() + i);
			i--;
		}
	}
	if (9 > vectMahjong.size())
	{
		return false;
	}
	for (int i = 0; i < 9; i++)
	{
		if (i + 1 != vectMahjong.at(i))
		{
			return false;
		}
	}

	return true;
}

bool CActions::CheckHu16Yisesanbugao()
{
	vector<int> vectAll;
	vectAll.insert(vectAll.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	for (int i = 0; i < vectAll.size(); i++)
	{
		if (9 < vectAll.at(i))
		{
			vectAll.erase(vectAll.begin() + i);
			i--;
		}
	}
	if (9 > vectAll.size())
	{
		return false;
	}

	SeparationJiang(vectAll);
	CMahjongTree mahjongTree(vectAll);
	vector<CMahjongData> vectData;
	int temp[8] = { 1, 1, 0, 1, 1, 0, 1, 1 };
	vectData = mahjongTree.GetDateByLevel(9);
	for (int i = 0; i < vectData.size(); i++)
	{
		vector<int> vect;
		vect = vectData.at(i).GetData(); 
		MahjongChi mahjongChiFir;
		mahjongChiFir.m_nValueFir = vect.at(0);
		mahjongChiFir.m_nValueSec = 0;
		mahjongChiFir.m_nValueThd = 0;
		vect.erase(vect.begin());
		for (int i = 0; i < vect.size(); i++)
		{
			if (mahjongChiFir.m_nValueFir + 1 == vect.at(i) && 0 == mahjongChiFir.m_nValueSec)
			{
				mahjongChiFir.m_nValueSec = vect.at(i);
				vect.erase(vect.begin() + i);
				i--;
				continue;
			}
			if (0 != mahjongChiFir.m_nValueSec && mahjongChiFir.m_nValueSec + 1 == vect.at(i))
			{
				mahjongChiFir.m_nValueThd = vect.at(i);
				vect.erase(vect.begin() + i);
				break;
			}
		}

		MahjongChi mahjongChiSec;
		mahjongChiSec.m_nValueFir = vect.at(0);
		mahjongChiSec.m_nValueSec = 0;
		mahjongChiSec.m_nValueThd = 0;
		vect.erase(vect.begin());
		for (int i = 0; i < vect.size(); i++)
		{
			if (mahjongChiSec.m_nValueFir + 1 == vect.at(i) && 0 == mahjongChiSec.m_nValueSec)
			{
				mahjongChiSec.m_nValueSec = vect.at(i);
				vect.erase(vect.begin() + i);
				i--;
				continue;
			}
			if (0 != mahjongChiSec.m_nValueSec && mahjongChiSec.m_nValueSec + 1 == vect.at(i))
			{
				mahjongChiSec.m_nValueThd = vect.at(i);
				vect.erase(vect.begin() + i);

				break;
			}
		}

		MahjongChi mahjongChiThd;
		mahjongChiThd.m_nValueFir = vect.at(0);
		mahjongChiThd.m_nValueSec = 0;
		mahjongChiThd.m_nValueThd = 0;
		vect.erase(vect.begin());
		for (int i = 0; i < vect.size(); i++)
		{
			if (mahjongChiThd.m_nValueFir + 1 == vect.at(i) && 0 == mahjongChiThd.m_nValueSec)
			{
				mahjongChiThd.m_nValueSec = vect.at(i);
				vect.erase(vect.begin() + i);
				i--;
				continue;
			}
			if (0 != mahjongChiThd.m_nValueSec && mahjongChiThd.m_nValueSec + 1 == vect.at(i))
			{
				mahjongChiThd.m_nValueThd = vect.at(i);
				//vect.erase(vect.begin() + i);
				break;
			}
		}

		if (CheckChiIsLing(mahjongChiFir) && CheckChiIsLing(mahjongChiSec) && CheckChiIsLing(mahjongChiThd))
		{
			if (2 >= mahjongChiSec.m_nValueFir - mahjongChiFir.m_nValueFir && 2 >= mahjongChiThd.m_nValueFir - mahjongChiSec.m_nValueFir)
			{
				return true;
			}
		}

	}

	return false;
}

bool CActions::CheckChiIsLing(MahjongChi mahjongChi)
{
	if (0 == mahjongChi.m_nValueFir || 0 == mahjongChi.m_nValueSec || 0 == mahjongChi.m_nValueThd)
	{
		return false;
	}

	return true;
}


bool CActions::CheckHu16Sananke()
{
	int nMark = 0;
	int nCount = 0;

	int nSize = m_vectMahjongGangAn.size();
	for (int i = 0; i < m_vectHanMahjong.size() - 1; i++)
	{
		if (m_vectHanMahjong.at(i) == m_vectHanMahjong.at(i + 1))
		{
			nMark++;
		}
		else
		{
			nMark = 0;
		}
		if (2 == nMark)
		{
			nCount++;
			nMark = 0;
		}
	}
	if (3 == nCount + nSize)
	{
		return true;
	}

	return false;
}


bool CActions::CheckHu12Dayuwu()
{
	for (int i = 0; i < m_vectAllMahjong.size(); i++)
	{
		if (5 >= m_vectAllMahjong.at(i) || 9 < m_vectAllMahjong.at(i))
		{
			return false;
		}
	}

	return true;
}

bool CActions::CheckHu12Xiaoyuwu()
{
	for (int i = 0; i < m_vectAllMahjong.size(); i++)
	{
		if (5 < m_vectAllMahjong.at(i))
		{
			return false;
		}
	}

	return true;
}

bool CActions::CheckHu12Sanfengke()
{
	int nSize = m_vectAllMahjong.size();
	int nCount = 0;
	for (int i = 10; i < 14; i++)
	{
		int nMark = 0;
		for (int j = 0; j < nSize; j++)
		{
			if (m_vectAllMahjong.at(j) == i)
			{
				nMark++;
			}
			if (3 == nMark)
			{
				nCount++;
				break;
			}
		}

		if (3 == nCount)
		{
			//三风刻
			return true;
		}
	}

	return false;
}


bool CActions::CheckHu6Pengpenghu()
{
	if (3 != m_vectMahjongPeng.size())
	{
		return false;
	}
	vector<int> vectHand;
	vectHand.insert(vectHand.begin(), m_vectHanMahjong.begin(), m_vectHanMahjong.end());
	SeparationJiang(vectHand);
	if (3 != vectHand.size())
	{
		return false;
	}
	if (vectHand.at(0) == vectHand.at(1) && vectHand.at(1) == vectHand.at(2))
	{
		return true;
	}

	return false;
}

bool CActions::CheckHu6Hunyise()
{
	int nMarkWan = 0;
	int nMarkZi = 0;
	for (int i = 0; i < m_vectAllMahjong.size(); i++)
	{
		if (1 <= m_vectAllMahjong.at(i) && 9 >= m_vectAllMahjong.at(i))
		{
			nMarkWan++;
		}
		else
		{
			nMarkZi++;
		}
	}
	if (0 < nMarkWan && 0 < nMarkZi)
	{
		return true;
	}

	return false;
}

bool CActions::CheckHu6Shuangangang()
{
	int nCount = 0;
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	SeparationJiang(vectMahjong);
	int nSize = vectMahjong.size();
	if (16 != nSize)
	{
		return false;
	}
	nCount = 0;
	for (int i = 0; i < nSize; i = i + 4)
	{
		if (vectMahjong.at(i) == vectMahjong.at(i + 1) && vectMahjong.at(i + 1) == vectMahjong.at(i + 2) && vectMahjong.at(i + 2) == vectMahjong.at(i + 3))
		{
			nCount++;
		}
	}
	//双杠
	if (2 == nCount)
	{
		return true;
	}

	return false;
}

bool CActions::CheckHu6Shuangjianke()
{
	int nSize = m_vectAllMahjong.size();
	int nCount = 0;
	for (int i = 14; i < 17; i++)
	{
		int nMark = 0;
		for (int j = 0; j < nSize; j++)
		{
			if (m_vectAllMahjong.at(j) == i)
			{
				nMark++;
			}
			if (3 <= nMark)
			{
				nCount++;
				break;
			}
		}
		if (2 == nCount)
		{
			//双箭刻
			return true;
		}
	}

	return false;
}

bool CActions::CheckHu6Quanqiuren()
{
	if (2 == m_vectHanMahjong.size() && 0 == m_vectMahjongGangAn.size() && !m_bIsSelfHu)
	{
		return true;
	}

	return false;
}

bool CActions::CheckHu4Buqiuren()
{
	if (!m_bIsSelfHu)
	{
		return false;
	}

	if (!m_vectMahjongChi.empty())
	{
		return false;
	}

	if (!m_vectMahjongGang.empty())
	{
		return false;
	}

	if (!m_vectMahjongPeng.empty())
	{
		return false;
	}

	return true;
}

bool CActions::CheckHu4Shuangminggang()
{
	if (2 == m_vectMahjongGang.size())
	{
		return true;
	}

	return false;
}

bool CActions::CheckHu4Shuanganke()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectHanMahjong.begin(), m_vectHanMahjong.end());
	SeparationJiang(vectMahjong);

	int nSize = 0;
	int nMark = 0;
	for (int i = 0; i < vectMahjong.size() - 1; i++)
	{
		if (vectMahjong.at(i) == vectMahjong.at(i + 1))
		{
			nMark++;
		}
		else
		{
			nMark = 0;
		}
		if (2 == nMark)
		{
			nMark = 0;
			nSize++;
		}
	}

	if (2 == nSize)
	{
		return true;
	}

	return false;
}


bool CActions::CheckHu2Pinghu()
{
	if (9 < m_nMahjongJiang)
	{
		return false;
	}

	if (!m_vectMahjongGang.empty() || !m_vectMahjongPeng.empty() || !m_vectMahjongGangAn.empty())
	{
		return false;
	}

	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectHanMahjong.begin(), m_vectHanMahjong.end());
	SeparationJiang(vectMahjong);

	while (!vectMahjong.empty())
	{
		MahjongChi mahjongChi;
		mahjongChi.m_nValueFir = vectMahjong.at(0);
		mahjongChi.m_nValueSec = 0;
		mahjongChi.m_nValueThd = 0;
		vectMahjong.erase(vectMahjong.begin());
		for (int i = 0; i < vectMahjong.size(); i++)
		{
			if (mahjongChi.m_nValueFir + 1 == vectMahjong.at(i) && 0 == mahjongChi.m_nValueSec)
			{
				mahjongChi.m_nValueSec = vectMahjong.at(i);
				vectMahjong.erase(vectMahjong.begin() + i);
				i--;
				continue;
			}
			if (mahjongChi.m_nValueFir + 2 == vectMahjong.at(i) && 0 == mahjongChi.m_nValueThd)
			{
				mahjongChi.m_nValueThd = vectMahjong.at(i);
				vectMahjong.erase(vectMahjong.begin() + i);
				i--;
			}
		}
		if (0 == mahjongChi.m_nValueFir || 0 == mahjongChi.m_nValueSec || 0 == mahjongChi.m_nValueThd)
		{
			return false;
		}
	}

	return true;
}

bool CActions::CheckHu2Siguiyi()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectHanMahjong.begin(), m_vectHanMahjong.end());

	int nIndex = 0;
	for (int i = 0; i < vectMahjong.size() - 1; i++)
	{
		if (vectMahjong.at(i) == vectMahjong.at(i + 1))
		{
			nIndex++;
		}
		else
		{
			nIndex = 0;
		}
		if (3 == nIndex)
		{
			return true;
		}
	}

	return false;
}

bool CActions::CheckHu2Jianke()
{
	int nSize = m_vectAllMahjong.size();
	int nCount = 0;
	for (int i = 14; i < 17; i++)
	{
		int nMark = 0;
		for (int j = 0; j < nSize; j++)
		{
			if (m_vectAllMahjong.at(j) == i)
			{
				nMark++;
			}
			if (3 <= nMark)
			{
				nCount++;
				break;
			}
		}
	}
	if (1 == nCount)
	{
		return true;
	}

	return false;
}

bool CActions::CheckHu2Duanyao()
{
	for (int i = 0; i < m_vectAllMahjong.size(); i++)
	{
		if (1 < m_vectAllMahjong.at(i) && 9 > m_vectAllMahjong.at(i))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool CActions::CheckHu1Lianliu()
{
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	for (int i = 0; i < vectMahjong.size() - 1; i++)
	{
		if (vectMahjong.at(i) == vectMahjong.at(i + 1))
		{
			vectMahjong.erase(vectMahjong.begin() + i);
			i--;
		}
	}
	
	if (9 < vectMahjong.at(vectMahjong.size() - 1))
	{
		vectMahjong.pop_back();
	}
	
	int nMark = 0;
	for (int i = 0; i < vectMahjong.size() - 1; i++)
	{
		if (vectMahjong.at(i) + 1 == vectMahjong.at(i + 1))
		{
			nMark++;
		}
		else
		{
			nMark = 0;
		}
		if (5 == nMark)
		{
			return true;
		}
	}

	return false;
}

bool CActions::CheckHu1Zimo()
{
	return m_bIsSelfHu;
}

bool CActions::CheckHu1Laoshaofu()
{	
	vector<int> vectMahjong;
	vectMahjong.insert(vectMahjong.begin(), m_vectAllMahjong.begin(), m_vectAllMahjong.end());
	SeparationJiang(vectMahjong);

	for (int i = 0; i < vectMahjong.size() - 1; i++)
	{
		if (vectMahjong.at(i) == vectMahjong.at(i + 1))
		{
			vectMahjong.erase(vectMahjong.begin() + i);
			i--;
		}
	}
	
	if (6 == vectMahjong.at(0) + vectMahjong.at(1) + vectMahjong.at(2) && 24 == vectMahjong.at(vectMahjong.size() - 1) + vectMahjong.at(vectMahjong.size() - 2) + vectMahjong.at(vectMahjong.size() - 3))
	{
		return true;
	}

	return true;
}

bool CActions::CheckHu1Erwubajiang()
{
	if (2 == m_nMahjongJiang || 5 == m_nMahjongJiang || 8 == m_nMahjongJiang)
	{
		return true;
	}

	return false;
}

bool CActions::CheckHu1Yaojiutou()
{
	if (1 == m_nMahjongJiang || 9 == m_nMahjongJiang)
	{
		return true;
	}

	return false;
}

bool CActions::CheckHu1Yibangao()
{


	return true;
}
