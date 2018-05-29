/*************************************************************************
	> File Name: hello.cpp
	> Author: Cao Zhenghui
	> Mail: 97njczh@gmail.com 
	> Created Time: Tue 22 May 2018 03:20:19 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

// 使用extern “C”使的导出的函数名称和实际名称一致
extern "C" void Hello(){
	cout << "Hello China!" << endl;
}
