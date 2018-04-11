
#include "UTFManager.h"


CUTFManager& CUTFManager::GetInstance()
{
	static CUTFManager manager;
	return manager;
}

CUTFManager::~CUTFManager()
{

}



std::string CUTFManager::GbkToUtf8(const std::string &str)
{
	int nLength = MultiByteToWideChar(0, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pWideStr = new wchar_t[nLength + 1];
	memset(pWideStr, 0, nLength + 1);

	MultiByteToWideChar(0, 0, str.c_str(), -1, pWideStr, nLength);
	nLength = WideCharToMultiByte(65001, 0, pWideStr, -1, NULL, 0, NULL, NULL);

	char* pStr = new char[nLength + 1];
	memset(pStr, 0, nLength + 1);
	WideCharToMultiByte(65001, 0, pWideStr, -1, pStr, nLength, NULL, NULL);

	if (pWideStr) delete[] pWideStr;
	std::string resultStr(pStr);
	delete pStr;

	return resultStr;
}
