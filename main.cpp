/*************************************************************************
	> File Name: main.cpp
	> Author: Cao Zhenghui
	> Mail: 97njczh@gmail.com 
	> Created Time: Tue 22 May 2018 03:00:10 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>
#include "CPluginEnumerator.h"

using namespace std;

void HelpCmd();

static const map<string, void (*)()> mapCommands = {
	{"help", HelpCmd}};

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		cout << "无参数！" << endl;
		return 0;
	}

	mapCommands.at(argv[1])();

	return 0;
}

void HelpCmd()
{
	vector<string> v_strPluginNames;

	CPluginEnumerator enumerator;
	if (!enumerator.GetPluginNames(v_strPluginNames))
	{
		cout << "Get plugin names error!" << endl;
		return;
	}

	for (int i = 0; i < v_strPluginNames.size(); i++)
	{
		void *handle = dlopen(v_strPluginNames[i].c_str(), RTLD_LAZY);
		if (handle == 0)
		{
			cout << "dlopen error" << endl;
			return;
		}

		typedef void (*FUNC_HELP)();

		FUNC_HELP dl_help = (FUNC_HELP)dlsym(handle, "Help");
		if (dl_help == 0)
		{
			cout << "dlsym error" << endl;
			return;
		}

		(dl_help)();

		dlclose(handle);
	}
}
