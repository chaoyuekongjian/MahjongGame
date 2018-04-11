#ifndef _MAHJONGSTRUCT_H_
#define _MAHJONGSTRUCT_H_

#include <assert.h>
#include <algorithm>
#include "MahjongTree.h"
struct MahjongChi
{
	int m_nValueFir;
	int m_nValueSec;
	int m_nValueThd;
};

struct MahjongPeng
{
	int m_nValueFir;
	int m_nValueSec;
	int m_nValueThd;
};

struct MahjongGang
{
	int m_nValueFir;
	int m_nValueSec;
	int m_nValueThd;
	int m_nValueFth;
};

struct MahjongGangAn
{
	int m_nValueFir;
	int m_nValueSec;
	int m_nValueThd;
	int m_nValueFth;
};

enum MahjongFan
{
	FAN_DASIXI         = 88,
	FAN_DASANYUAN      = 88,
	FAN_JIULIANBAODENG = 88,
	FAN_SIGANG         = 88,
	FAN_LIANQIDUI      = 88,
	FAN_BAIWANSHI      = 88,
	FAN_XIAOSIXI       = 64,
	FAN_XIAOSNYUAN     = 64,
	FAN_ZIYISE         = 64,
	FAN_SIANKE         = 64,
	FAN_YISESHUANGLONG = 64,
	FAN_YISESITONGSHUN = 48,
	FAN_YISESIJIEGAO   = 48,
	FAN_YISESIBUGAO    = 32,
	FAN_SANGANG        = 32,
	FAN_HUNYAOJIU      = 32,
	FAN_QIDUI          = 24,
	FAN_QINGYISE       = 24,
	FAN_YISESANTONGSHUN= 24,
	FAN_YISESANJIEGAO  = 24,
	FAN_QINGLONG       = 16,
	FAN_YISESANBUGAO   = 16,
	FAN_SANANKE        = 16,
	FAN_DAYUWU         = 12,
	FAN_XIAOYUWU       = 12,
	FAN_SANFENGKE      = 12,
	FAN_PENGPENGHE     = 6,
	FAN_HUNYISE        = 6,
	FAN_SHUANGANGANG   = 6,
	FAN_SHUANGJIANKE   = 6,
	FAN_QUANQIUREN     = 6,
	FAN_SHUANGANKE     = 4,
	FAN_BUQIUREN       = 4,
	FAN_SHUANGMINGGANG = 4,
	FAN_SIGUIYI        = 2,
	FAN_PINGHU         = 2,
	FAN_JIANKE         = 2,
	FAN_DUANYAO        = 2,
	FAN_LIANLIU        = 1,
	FAN_ZIMO           = 1
};

#endif