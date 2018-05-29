#ifndef _C_PLUGIN_ENUMERATOR_H_
#define _C_PLUGIN_ENUMERATOR_H_

#include <vector>
#include <string>
#include <string.h>
#include <dirent.h>

using namespace std;

#define DIR_PATH "./plugin"

class CPluginEnumerator
{
  public:
    CPluginEnumerator(){};
    ~CPluginEnumerator(){};

  public:
    bool GetPluginNames(vector<string> &v_strPluginNames)
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
			//std::cout<<name<<std::endl;
            v_strPluginNames.push_back(name);
        }

        closedir(dir);

        return true;
    }
};

#endif
