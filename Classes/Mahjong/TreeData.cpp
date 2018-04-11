#include "Mahjong\TreeData.h"



CMahjongData::CMahjongData()
{

}

CMahjongData::~CMahjongData()
{

}

void CMahjongData::AddData(int nData)
{
	m_vectData.push_back(nData);

}

vector<int> CMahjongData::GetData()
{
	return m_vectData;
}