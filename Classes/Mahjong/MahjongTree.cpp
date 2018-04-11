#include "MahjongTree.h"


CMahjongTree::CMahjongTree()
{

}

CMahjongTree::CMahjongTree(const vector<int> vectData)
{
	m_vectAllData.insert(m_vectAllData.begin(), vectData.begin(), vectData.end());
}

CMahjongTree::~CMahjongTree()
{



}

vector<CMahjongData> CMahjongTree::GetDateByLevel(int nLevel)
{
	vector<CMahjongData> mahjongData;
	vector<int> vectResult;
	SetDataWithLevel(m_vectAllData, nLevel, vectResult, mahjongData);

	return mahjongData;
}



void CMahjongTree::SetDataWithLevel(vector<int> vectData, int nLevel, vector<int> &vectResult, vector<CMahjongData> &vectMahjong)
{
	if (nLevel == 0)
	{
		CMahjongData mahjongData;
		for (int i = 0; i < vectResult.size(); i++)
		{
			mahjongData.AddData(vectResult.at(i));
		}
		vectMahjong.push_back(mahjongData);
		return;
	}
	if (vectData.size() == 0)
	{
		return;
	}
	vectResult.push_back(*vectData.begin());
	vector<int> newVect;
	newVect.insert(newVect.begin(), vectData.begin() + 1, vectData.end());
	SetDataWithLevel(newVect, nLevel - 1, vectResult, vectMahjong);
	vectResult.pop_back();
	SetDataWithLevel(newVect, nLevel, vectResult, vectMahjong);
}

