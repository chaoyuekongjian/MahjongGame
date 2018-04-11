#ifndef _UTFMANAGER_H_
#define _UTFMANAGER_H_

#include "cocos2d.h"
USING_NS_CC;

#include <string>
#include <windows.h>


class CUTFManager
{
public:
	~CUTFManager();
	static CUTFManager& GetInstance();
	static std::string GbkToUtf8(const std::string &str);

private:
	
	

};




#endif