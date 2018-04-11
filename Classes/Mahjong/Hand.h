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


	void HandAddMahjong(int nValue);							        //����齫
	int  GetMahjongAtIndex(int nValue);								    //��ȡ�齫������
	int ThrowMahjong(int nIndex);									    //���Ʋ�ɾ����Ӧλ�õ��齫
	bool DeleteMahjong(int nValue);									    //ɾ����Ӧֵ���齫 
	int GetJiang();                                                     //��ȡ����
	void CleanUp();													    //����齫 
	//void VectMahjongChi(vector<StrChi> &vectChi);					    // ��ȡ���Ƶ����
	//void VectMahjongHand(vector<int> &vectChi);

	bool CheckMahjongChi(int nValue);								    //������
	bool CheckMahjongPeng(int nValue);								    //�������
	bool CheckMahjongGang(int nValue);                                  //������

	bool CheckMahjongHu();                                              //����Ƿ����
	vector<int> CheckMahjongTing();                                     //����Ƿ����� 

	

	vector<int> GetVectHand();                                          //��ȡ���ϵ���
	vector<MahjongChi> GetVectChi();                                    //��ȡ���Գ��Ƶ����
	vector<MahjongPeng> GetVectPeng();                                  //��ȡ����������
	vector<MahjongGang> GetVectGang();                                  //��ȡ���Ըܵ���
	 
	void CleanMahjongChi();                                             //�������vector
	void CleanMahjongPeng();
	void CleanMahjongGang();

	CHand &operator = (const CHand &hand);
protected:
	bool CheckMahjongABC(const vector<int> vectValue);					//���������
	bool CheckMahjongAAA(const vector<int> vectValue);					//���������
	bool CheckMahjongThr(const vector<int> vectValue);					//���������
	bool CheckMahjongSix(const vector<int> vectValue);                  //���������
	bool CheckMahjongNin(const vector<int> vectValue);                  //��������
	bool CheckMahjongTwl(const vector<int> vectValue);                  //���ʮ������
	bool CheckMahjongZii(const vector<int> vectValue);                  //�������
	bool CheckMahjongDui(const vector<int> vectValue);                  //����߶�

private:
	void SetJaing(int nIndex);                                          //���ý���

private:
	vector<int> m_vectMahjongHand;
	vector<MahjongChi> m_vectMahjongChi;
	vector<MahjongPeng> m_vectMahjongPeng;
	vector<MahjongGang> m_vectMahjongGang;

	int m_nMahjongJiang;                                          //��
};

#endif