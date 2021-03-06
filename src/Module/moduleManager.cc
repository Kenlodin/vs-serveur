#include <core/module/moduleManager.hh>

ModuleManager *ModuleManager::instance_ = NULL;
ModuleManager *ModuleManager::getInstance()
{
  if (instance_ == NULL)
    instance_ = new ModuleManager();
  return instance_;
}

void ModuleManager::loadModules()
{
  TiXmlDocument c_;
  TiXmlElement  *elt;

  std::cout << "Load modules" << std::endl;
  c_ = TiXmlDocument (Config::getInstance().getString("module-conf"));
  if (!c_.LoadFile ())
  {
    std::cerr << "Warn: can't find `"
              << Config::getInstance().getString("module-conf")
              << "`"
              << std::endl;
    return;
  }

  elt = c_.RootElement ();
  
  if (elt != nullptr)
    elt = elt->FirstChildElement ();
  while (elt != nullptr)
  {
    if (elt->ValueStr () == "module")
      if (elt->GetText () != NULL)
        loadModule(elt->GetText ());
    elt = elt->NextSiblingElement ();
  }
}

void ModuleManager::loadModule(std::string filename)
{
  std::cout << "Load module: " << filename << std::endl;
  modules_[filename] = new Module("modules/" + filename + ".so");
}
