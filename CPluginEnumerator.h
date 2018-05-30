#ifndef _C_PLUGIN_ENUMERATOR_H_
#define _C_PLUGIN_ENUMERATOR_H_

#include <vector>
#include <string>

using namespace std;

#define DIR_PATH "./plugin"

class CPluginEnumerator
{
public:
	CPluginEnumerator()
	{
	};
	~CPluginEnumerator()
	{
	};

public:
	bool GetPluginNames( vector<string> &v_strPluginNames );
};

#endif