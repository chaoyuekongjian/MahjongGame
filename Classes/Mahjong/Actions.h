#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include <vector>
#include <string>
#include "MahjongStruct.h"
using std::vector;
using std::string;

class CActions
{
public:
	CActions();
	virtual ~CActions();

	void ActionAddMahjong(MahjongChi mahjongChi);
	void ActionAddMahjong(MahjongPeng mahjongPeng);
	void ActionAddMahjong(MahjongGang mahjongGang);
	void ActionAddMahjong(MahjongGangAn mahjongGangAn);
	void ActionAddMahjong(vector<int> vectHand);

	void ChangePengToGang(int nIndex);
	void SetHandMahjong(vector<int> vectHand);
	void SetJiang(int nIndex);
	void CheckMahjongFan();
	void SetIsSelfHu(bool bValue);

	int GetMahjongFan();
	std::vector<string> GetVectMahjongName();
	
	CActions &operator = (const CActions &others);
private:
	void SeparationJiang(vector<int> &vectHand);              //分离将牌

	//检测胡牌番数 88番牌种
	bool CheckHu88Dasixi();
	bool CheckHu88Dasanyuan();
	bool CheckHu88Jiulianbaodeng();
	bool CheckHu88Sigang();
	bool CheckHu88Lianqidui();
	bool CheckHu88Baiwanshi();
	
	//64番牌种
	bool CheckHu64Xiaosixi();
	bool CheckHu64Xiaosanyuan();
	bool CheckHu64Ziyise();
	bool CheckHu64Sianke();
	bool CheckHu64Yiseshuanglong();
	
	//48番牌种
	bool CheckHu48Yisesitongshun();
	bool CheckHu48Yisesijiegao();                                                            
	
	//32番牌种
	bool CheckHu32Yisesibugao();
	bool CheckHu32Sangang(); 
	bool CheckHu32Hunyaojiu();
	
	//24番牌种
	bool CheckHu24Qidui();
	bool CheckHu24Qingyise();
	bool CheckHu24Yisesantongshun(); 
	bool CheckHu24Yisesanjiegao();  
	
	//16番牌种
	bool CheckHu16Qinglong();
	bool CheckHu16Yisesanbugao();
	bool CheckHu16Sananke();
	
	//12番牌种
	bool CheckHu12Dayuwu();
	bool CheckHu12Xiaoyuwu();
	bool CheckHu12Sanfengke();
	
	//8番牌种

	//6番牌种
	bool CheckHu6Pengpenghu();
	bool CheckHu6Hunyise();
	bool CheckHu6Shuangangang();
	bool CheckHu6Shuangjianke();
	bool CheckHu6Quanqiuren();
	
	//4番牌种
	bool CheckHu4Buqiuren();
	bool CheckHu4Shuangminggang();
	bool CheckHu4Shuanganke();
	
	//2番牌种
	bool CheckHu2Pinghu();
	bool CheckHu2Siguiyi();
	bool CheckHu2Jianke();
	bool CheckHu2Duanyao();

	//1番牌种
	bool CheckHu1Lianliu();
	bool CheckHu1Zimo();
	bool CheckHu1Laoshaofu();
	bool CheckHu1Erwubajiang();
	bool CheckHu1Yaojiutou();
	bool CheckHu1Yibangao();

	bool CheckChiIsLing(MahjongChi mahjongChi);

private:
	int m_nMahjongJiang;                                        //将

	vector<int> m_vectHanMahjong;                               //手牌  计算暗刻所用
	vector<int> m_vectAllMahjong;                               // 计算番数区域

	vector<MahjongChi> m_vectMahjongChi;
	vector<MahjongPeng> m_vectMahjongPeng;
	vector<MahjongGang> m_vectMahjongGang;
	vector<MahjongGangAn> m_vectMahjongGangAn;

	int m_nMahjongFan;
	string m_sMahjongName;
	std::vector<string> m_vectMahjongName;

	bool m_bIsSelfHu;
};

#endif