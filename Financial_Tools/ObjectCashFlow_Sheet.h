#pragma once
#include "ObjectCashFlow.h"
class ObjectCashFlow_Sheet
{
	
public:
	ObjectCashFlow_Sheet(void);
	virtual ~ObjectCashFlow_Sheet(void);
	ObjectCashFlow_Sheet& operator=(ObjectCashFlow_Sheet& rhs);
public:
	map<CString,ObjectCashFlow> Project_Sheet;//构建一个项目表
	int Project_Num;
	int Years;
};
