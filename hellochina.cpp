/*************************************************************************
  > File Name: hellochina.cpp
  > Author: Cao Zhenghui
  > Mail: 97njczh@gmail.com 
  > Created Time: Tue 22 May 2018 03:20:19 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#include "IPlugin.h"

class CPlugin : public IPlugin
{
public:
	CPlugin(){}
	virtual ~CPlugin(){}

public:

	virtual void Print()
	{
		cout << "Hello China!" << endl;
	}

	virtual void Help(int id)
	{
		cout << "Function ID: " << id 
			<< ". This function will print \'Hello China\'." << endl;
	}

};

// 使用extern “C”使的导出的函数名称和实际名称一致
extern "C" void CreateObj(IPlugin **ppPlugin)
{
	static CPlugin *plugin = new CPlugin();
	*ppPlugin = plugin;
}
