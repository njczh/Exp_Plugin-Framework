/*************************************************************************
  > File Name: main.cpp
  > Author: Cao Zhenghui
  > Mail: 97njczh@gmail.com 
  > Created Time: Tue 22 May 2018 03:00:10 PM CST
 ************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#include "CPluginEnumerator.h"
#include "CPluginController.h"

int main( int argc, char *argv[] )
{
	if ( argc != 2 )
	{
		cout << "Parameters error！" << endl;
		return(0);
	}

	CPluginController pluginController;

	pluginController.Initialize();

	int id = atoi( argv[1] );
	if( id != 0 ){
		if( !pluginController.ProcessRequest( id ) )
			cout << "No such function belonging to this func ID." << endl;
	}
	else{	
		if ( strcmp( argv[1], "help" ) == 0 )
			pluginController.ProcessHelp();
		else
			cout << "Parameters error！" << endl;
	}

	pluginController.Uninitialize();

	return(0);
}
