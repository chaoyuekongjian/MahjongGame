#ifndef _MAHJONG_H_
#define _MAHJONG_H_
#include <vector>


using std::vector; 
class CMahjong
{
public:
	CMahjong();
	virtual ~CMahjong();


protected:
	void PushNewMahjong(int nIndex);



private:
	vector<int> m_vectMahjongHand;  // 手上剩下的牌
	vector<int> m_vectMahjongAll;   // 手上和放牌区域的所有牌




};




#endif