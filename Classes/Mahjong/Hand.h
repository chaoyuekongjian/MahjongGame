#ifndef _HAND_H_
#define _HAND_H_
#include <vector>
#include "MahjongStruct.h"

using std::vector;


class CHand
{
public:
	CHand();
	virtual ~CHand();
	enum PaiNumber
	{
		PAI_THR = 3,
		PAI_SIX = 6, 
		PAI_NIN = 9, 
		PAI_TWL = 12
	};


	void HandAddMahjong(int nValue);							        //添加麻将
	int  GetMahjongAtIndex(int nValue);								    //获取麻将的索引
	int ThrowMahjong(int nIndex);									    //打牌并删除对应位置的麻将
	bool DeleteMahjong(int nValue);									    //删除对应值的麻将 
	int GetJiang();                                                     //获取将牌
	void CleanUp();													    //清除麻将 
	//void VectMahjongChi(vector<StrChi> &vectChi);					    // 获取吃牌的组合
	//void VectMahjongHand(vector<int> &vectChi);

	bool CheckMahjongChi(int nValue);								    //检测吃牌
	bool CheckMahjongPeng(int nValue);								    //检测碰牌
	bool CheckMahjongGang(int nValue);                                  //检测杠牌

	bool CheckMahjongHu();                                              //检测是否胡牌
	vector<int> CheckMahjongTing();                                     //检测是否听牌 

	

	vector<int> GetVectHand();                                          //获取手上的牌
	vector<MahjongChi> GetVectChi();                                    //获取可以吃牌的组合
	vector<MahjongPeng> GetVectPeng();                                  //获取可以碰的牌
	vector<MahjongGang> GetVectGang();                                  //获取可以杠的牌
	 
	void CleanMahjongChi();                                             //清除吃牌vector
	void CleanMahjongPeng();
	void CleanMahjongGang();

	CHand &operator = (const CHand &hand);
protected:
	bool CheckMahjongABC(const vector<int> vectValue);					//检测三连张
	bool CheckMahjongAAA(const vector<int> vectValue);					//检测三重张
	bool CheckMahjongThr(const vector<int> vectValue);					//检测三张牌
	bool CheckMahjongSix(const vector<int> vectValue);                  //检测六张牌
	bool CheckMahjongNin(const vector<int> vectValue);                  //检测九张牌
	bool CheckMahjongTwl(const vector<int> vectValue);                  //检测十二张牌
	bool CheckMahjongZii(const vector<int> vectValue);                  //检测字牌
	bool CheckMahjongDui(const vector<int> vectValue);                  //检测七对

private:
	void SetJaing(int nIndex);                                          //设置将牌

private:
	vector<int> m_vectMahjongHand;
	vector<MahjongChi> m_vectMahjongChi;
	vector<MahjongPeng> m_vectMahjongPeng;
	vector<MahjongGang> m_vectMahjongGang;

	int m_nMahjongJiang;                                          //将
};

#endif