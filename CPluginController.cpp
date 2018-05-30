/*************************************************************************
  > File Name: CPluginController.cpp
  > Author: Cao Zhenghui
  > Mail: 97njczh@gmail.com 
  > Created Time: Wed 30 May 2018 11:50:03 AM CST
 ************************************************************************/

#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include "dlfcn.h"

#include <iostream>

bool CPluginController::Initialize( void )
{
	vector<std::string> v_strPluginNames;

	/* 文件目录枚举器，获取plugin文件夹下所有符合条件的文件名 */
	CPluginEnumerator enumerator;
	if ( !enumerator.GetPluginNames( v_strPluginNames ) )
	{
		/* 获取文件名失败 */
		cout << "Get plugin names error!" << endl;
		return(false);
	}

	for ( int i = 0; i < v_strPluginNames.size(); i++ )
	{
		Plugin plugin;

		/* 加载动态链接库 */
		void *handle = dlopen( v_strPluginNames[i].c_str(), RTLD_LAZY );
		if ( handle == NULL )
			/* 加载失败 */
			std::cout << "dlopen error: " << dlerror() << std::endl;
		else{
			plugin.handle = handle;

			/* 映射动态链接库中的函数 */

			plugin.dllGetId = (PROC_GETID) dlsym( handle, "GetId" );
			if ( plugin.dllGetId == NULL )
			{
				cout << "GetId error!"; continue;
			}

			plugin.dllHelp = (PROC_HELP) dlsym( handle, "Help" );
			if ( plugin.dllHelp == NULL )
			{
				cout << "Help error!"; continue;
			}

			plugin.dllPrint = (PROC_PRINT) dlsym( handle, "Print" );
			if ( plugin.dllPrint == NULL )
			{
				cout << "Print error!"; continue;
			}

			plugins.push_back( plugin );
		}
	}

	return(true);
}


bool CPluginController::Uninitialize( void )
{
	for ( int i = 0; i < plugins.size(); i++ )
	{
		/* 卸载动态链接库 */
		dlclose( plugins[i].handle );
	}

	return(true);
}


bool CPluginController::ProcessHelp( void )
{
	for ( int i = 0; i < plugins.size(); i++ )
	{
		plugins[i].dllHelp();
	}
}


bool CPluginController::ProcessRequest( int functionId )
{
	for ( int i = 0; i < plugins.size(); i++ )
	{
		/* 调用动态链接库中的函数 */
		if ( plugins[i].dllGetId() == functionId )
		{
			plugins[i].dllPrint();
			return true;
		}
	}

	return false;
}

