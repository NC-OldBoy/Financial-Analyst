#include "StdAfx.h"
#include "ObjectCashFlow_Sheet.h"


ObjectCashFlow_Sheet::ObjectCashFlow_Sheet(void)
{
	Project_Num=0;
	Years=0;
}

ObjectCashFlow_Sheet::~ObjectCashFlow_Sheet(void)
{
}

ObjectCashFlow_Sheet& ObjectCashFlow_Sheet::operator=(ObjectCashFlow_Sheet& rhs)
{
	Project_Sheet=rhs.Project_Sheet;
	Project_Num=rhs.Project_Num;
	Years=rhs.Years;
	return *this;
}
BOOL ObjectCashFlow_Sheet::isempty()
{
	if(Project_Sheet.empty())
		return TRUE;
	else
		return FALSE;
}