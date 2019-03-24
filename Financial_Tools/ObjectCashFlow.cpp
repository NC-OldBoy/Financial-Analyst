#include "StdAfx.h"
#include "ObjectCashFlow.h"

ObjectCashFlow::ObjectCashFlow(void)
{
}

ObjectCashFlow::~ObjectCashFlow(void)
{
	map<CString,long double>::iterator iter2=Project.begin();
	for (;iter2!=Project.end();)
	{
		Project.erase(iter2++);
	}
}

ObjectCashFlow& ObjectCashFlow::operator=(ObjectCashFlow& rhs)
{
	Project=rhs.Project;
	Project_Name=rhs.Project_Name;
	return *this;
}