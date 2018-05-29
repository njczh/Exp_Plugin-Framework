/*************************************************************************
	> File Name: main.cpp
	> Author: Cao Zhenghui
	> Mail: 97njczh@gmail.com 
	> Created Time: Tue 22 May 2018 03:00:10 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>
using namespace std;

#define DIR_PATH "./plugin/"
typedef void (*Fun)();

int main()
{

	vector<void *> handles;

	DIR *dir;
	struct dirent *ptr;
	dir = opendir(DIR_PATH);

	while ((ptr = readdir(dir)) != NULL)
	{
		int len = strlen(ptr->d_name);

		if (len < 4 || strcmp(&ptr->d_name[len-3],".so"))
			continue;

		char file_path[NAME_MAX + strlen(DIR_PATH) + 1] = DIR_PATH;

		strcat(file_path, ptr->d_name);

		void *handle = dlopen(file_path, RTLD_LAZY); // 名称要求

		if (handle == 0)
		{
			cout << "dlopen error!" << endl;
			continue;
		}
		else
			handles.push_back(handle);
	}

	for (vector<void *>::iterator handle = handles.begin(); handle != handles.end(); handle++)
	{
		Fun func = (Fun)dlsym(*handle, "Hello"); // 函数声明的要求
		if (func == 0)
		{
			cout << "func error: ";
			char *str = dlerror();
			cout << str << endl;
		}

		func();

		dlclose(*handle);
	}

	return 0;
}
