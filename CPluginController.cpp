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
		return false;
	}

	for ( int i = 0; i < v_strPluginNames.size(); i++ )
	{
		typedef void (*PLUGIN_CREATE)(IPlugin**);
		PLUGIN_CREATE CreateProc;

		IPlugin *pPlugin =  NULL;

		/* 加载动态链接库 */
		void *handle = dlopen( v_strPluginNames[i].c_str(), RTLD_LAZY );
		if ( handle == NULL )
		{
			/* 加载失败 */
			std::cout << "dlopen error: " << dlerror() << std::endl;
		}
		else
		{
			/* 映射动态链接库中的函数 */

			CreateProc = (PLUGIN_CREATE)dlsym( handle, "CreateObj" );
			if ( CreateProc == NULL ){
				cout << "Create object error!\n"; continue;
			}

			(CreateProc)(&pPlugin);
			if(pPlugin == NULL){
				cout << "Get object error!\n"; continue;
			}

			pPlugin->SetHandle( handle );
			plugins.push_back( pPlugin );
		}
	}

	return true ;
}


bool CPluginController::Uninitialize( void )
{
	for ( int i = 0; i < plugins.size(); i++ )
	{
		/* 卸载动态链接库 */
		dlclose( plugins[i]->GetHandle() );
	}

	return(true);
}


bool CPluginController::ProcessHelp( void )
{
	for ( int i = 0; i < plugins.size(); i++ )
	{
		plugins[i]->Help(i+1);
	}
}


bool CPluginController::ProcessRequest( int functionId )
{
	if(functionId > plugins.size() || functionId < 1)
	{
		return false;
	}
	else
	{
		plugins[functionId-1]->Print();
		return true;
	}
}

