/*************************************************************************
	> File Name: IPlugin.h
	> Author: Cao Zhenghui
	> Mail: 97njczh@gmail.com 
	> Created Time: Wed 30 May 2018 08:25:39 PM CST
 ************************************************************************/

#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

class IPlugin
{
public:
	IPlugin();
	virtual ~IPlugin();

public:
	virtual int GetId() = 0;
	virtual void Print() = 0;
	virtual void Help() = 0;

public:
	void   SetHandle(void *);
	void * GetHandle(void);

private:
	void * handle;

};

#endif
