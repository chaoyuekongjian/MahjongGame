#ifndef _CTREEDATA_H_
#define _CTREEDATA_H_
#include <vector>
using std::vector;

class CMahjongData
{
public:
	CMahjongData();
	virtual ~CMahjongData();

	void AddData(int nData);
	vector<int> GetData();
private:
	vector<int> m_vectData;

};



#endif