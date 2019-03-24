#pragma once

#include "StdAfx.h"
using namespace std;
class ObjectCashFlow
{
public:
	ObjectCashFlow(void);
	virtual ~ObjectCashFlow(void);
public:
	map <CString,long double> Project;
	CString Project_Name;
};
