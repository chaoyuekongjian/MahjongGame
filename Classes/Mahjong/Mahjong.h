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
	vector<int> m_vectMahjongHand;  // ����ʣ�µ���
	vector<int> m_vectMahjongAll;   // ���Ϻͷ��������������




};




#endif