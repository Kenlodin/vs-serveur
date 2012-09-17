#ifndef MODULEMANAGER_HH_
# define MODULEMANAGER_HH_

# include <string>
# include <tinyxml.h>
# include <map>
# include <core/module/module.hh>

class ModuleManager
{
  public:
    static ModuleManager *getInstance();

    void loadModule(std::string filename);
    void loadModules();

  private:
    static ModuleManager *instance_;
    std::map<std::string, Module*> modules_;
};

#endif /* !MODULEMANAGER_HH_ */
