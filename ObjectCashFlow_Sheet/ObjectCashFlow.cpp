#include "StdAfx.h"
#include "ObjectCashFlow.h"

ObjectCashFlow::ObjectCashFlow(void)
{
}

ObjectCashFlow::~ObjectCashFlow(void)
{
}

ObjectCashFlow& ObjectCashFlow::operator=(ObjectCashFlow& rhs)
{
	Project=rhs.Project;
	Project_Name=rhs.Project_Name;
	return *this;
}