/*************************************************************************
  > File Name: CPluginController.h
  > Author: Cao Zhenghui
  > Mail: 97njczh@gmail.com 
  > Created Time: Wed 30 May 2018 11:49:32 AM CST
 ************************************************************************/

#ifndef _CPLUGINCONTROLLER_H_
#define _CPLUGINCONTROLLER_H_

typedef void (*PROC_PRINT)(void);
typedef void (*PROC_HELP)(void);
typedef int	 (*PROC_GETID)(void);

#include <vector>
using std::vector;

struct Plugin
{
	void * handle;
	PROC_PRINT dllPrint;
	PROC_HELP  dllHelp;
	PROC_GETID dllGetId;
};

class CPluginController
{
public:
	CPluginController(void){};
	virtual ~CPluginController(void){};

public:
	bool Initialize(void);
	bool Uninitialize(void);

	bool ProcessHelp(void);
	bool ProcessRequest(int functionId);

private:
	vector<Plugin> plugins;

};

#endif

