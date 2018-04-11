#ifndef _MAHJONGHUSCENE_H_
#define _MAHJONGHUSCENE_H_

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using std::string;
using std::vector;

class CMahjongHuScene : public cocos2d::Scene
{
public:
	CMahjongHuScene();
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(CMahjongHuScene);

	void MenuCallBack(Ref *pSender);

	void SetMahjongFan(int nNumber);
	void SetMahjongName(vector<string> vectMahjongName);
	
	virtual void onEnterTransitionDidFinish();
private:
	int m_nMahjongFan;
	string m_sMahjongName;
	vector<string> m_vectMahjongName;
};


#endif