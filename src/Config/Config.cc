/* 
 * File:   Config.cc
 * Author: Aymeric
 * 
 * Created on 19 avril 2012, 16:41
 */

#include "Config.hh"
#include <tinyxml.h>

Config&
Config::getInstance ()
{
  static Config instance;

  return instance;
}

void
Config::load (std::string file)
{
  TiXmlDocument c (file);
  if (!c.LoadFile ())
  {
    std::cerr << "Impossible de charger le fichier de configuration ! " << std::endl;
    std::exit (1);
  }
  TiXmlElement *elt = c.RootElement ();
  if (elt != nullptr)
    elt = elt->FirstChildElement ();
  while (elt != nullptr)
  {
    std::string text = std::string (elt->GetText ());
    config_.insert (std::pair<std::string, std::string > (elt->ValueStr (), text));
    elt = elt->NextSiblingElement ();
  }
}

void
Config::print ()
{
  std::map<std::string, std::string>::iterator i;
  for (i = config_.begin (); i != config_.end (); ++i)
    std::cout << i->first << "-" << i->second << std::endl;
}

int
Config::getPort ()
{
    std::string port = config_.at ("port");
    int p;
    tools::fromString (port, p);
    return p;
}

bool
Config::check ()
{
//  config_.find ()
}