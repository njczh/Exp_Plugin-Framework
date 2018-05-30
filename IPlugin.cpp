/*************************************************************************
	> File Name: IPlugin.cpp
	> Author: Cao Zhenghui
	> Mail: 97njczh@gmail.com 
	> Created Time: Wed 30 May 2018 08:25:39 PM CST
 ************************************************************************/

#include "IPlugin.h"

IPlugin::IPlugin()
{

};

IPlugin::~IPlugin()
{

};

void IPlugin::SetHandle(void * handle)
{
	this->handle = handle;
}

void * IPlugin::GetHandle(void)
{
	return handle;
}
