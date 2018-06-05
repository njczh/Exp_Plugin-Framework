/*************************************************************************
  > File Name: CPluginEnumerator.cpp
  > Author: Cao Zhenghui
  > Mail: 97njczh@gmail.com 
  > Created Time: Wed 30 May 2018 10:55:49 AM CST
 ************************************************************************/

#include "CPluginEnumerator.h"

#include <string.h>
#include <dirent.h>
#include <iostream>
using namespace std;

bool CPluginEnumerator::GetPluginNames(vector<string> &v_strPluginNames)
{
	DIR *dir = opendir(DIR_PATH);
	if (dir == 0)
		return false;

	while (true)
	{
		struct dirent *pentry = readdir(dir);
		if (pentry == 0)
			break;

		if (strcmp(pentry->d_name, ".") == 0)
			continue;

		if (strcmp(pentry->d_name, "..") == 0)
			continue;

		string name = DIR_PATH;
		name += "/";
		name += pentry->d_name;
		v_strPluginNames.push_back(name);
	}

	closedir(dir);

	return true;
}



