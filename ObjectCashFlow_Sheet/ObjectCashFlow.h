#pragma once

#include "StdAfx.h"
using namespace std;
class ObjectCashFlow
{
public:
	ObjectCashFlow(void);
	virtual ~ObjectCashFlow(void);
	ObjectCashFlow& operator=(ObjectCashFlow& rhs);
public:
	map <CString,long double> Project_OutFlow;
	map <CString,long double> Project_InFlow;
	map <CString,long double> Project;
	CString Project_Name;
};

