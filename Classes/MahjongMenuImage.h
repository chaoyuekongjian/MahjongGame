#ifndef _MAHJONGMENUSPRITE_H_
#define _MAHJONGMENUSPRITE_H_
#include "cocos2d.h"


class CMahjongMenuImage : public cocos2d::MenuItemImage
{
public:
	virtual ~CMahjongMenuImage();
	virtual bool init();

	static CMahjongMenuImage* create(int nIndex);
	

	int GetIndex();

private:
	int m_nIndex;
	


};





#endif 
