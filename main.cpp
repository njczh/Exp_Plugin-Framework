/*************************************************************************
	> File Name: main.cpp
	> Author: Cao Zhenghui
	> Mail: 97njczh@gmail.com 
	> Created Time: Tue 22 May 2018 03:00:10 PM CST
 ************************************************************************/

#include<iostream>
#include<dlfcn.h>
using namespace std;

int main(){

	void *handle = dlopen("./hello.so",RTLD_LAZY);		// 名称要求
	if( handle == 0 ){
		cout << "dlopen error!" << endl;
		return 0;
	}

	typedef void (*Fun)();
	Fun func = (Fun)dlsym(handle,"Hello");				// 函数声明的要求
	if( func == 0 ){
		cout << "func error: ";
		char *str = dlerror();
		cout << str << endl;
	}

	func();

	dlclose(handle);

	return 0;
}
