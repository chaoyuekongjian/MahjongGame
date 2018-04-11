#ifndef _MAHJONGTREE_H_
#define _MAHJONGTREE_H_
#include <vector>
#include "MahjongStruct.h"
#include "Mahjong\TreeData.h"
using std::vector;
class CMahjongData;

class CMahjongTree
{
public:
	CMahjongTree();
	CMahjongTree(const vector<int> vectData);
	virtual ~CMahjongTree();

	
	vector<CMahjongData> GetDateByLevel(int nLevel);

private:
	void SetDataWithLevel(vector<int> vectData, int nLevel, vector<int> &vectResult, vector<CMahjongData> &vectMahjong);

	vector<int> m_vectAllData;
	

};


#endif