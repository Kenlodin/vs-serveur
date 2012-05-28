/*
 * File:   Config.cc
 * Author: Aymeric
 *
 * Created on 19 avril 2012, 16:41
 */

#include "Config.hh"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>


Config&
Config::getInstance ()
{
  static Config instance;

  return instance;
}

void
Config::load (std::string file)
{
  c_ = TiXmlDocument (file);
  if (!c_.LoadFile ())
  {
    std::cerr << "Impossible de charger le fichier de configuration ! " << std::endl;
    std::exit (1);
  }
}

void
Config::loadConfig ()
{
  TiXmlElement *elt = c_.RootElement ();
  if (elt != nullptr)
    elt = elt->FirstChildElement ();
  while (elt != nullptr)
  {
    if (elt->ValueStr () != "files")
    {
      std::string text;
      if (elt->GetText () == NULL)
        text = std::string ("");
      else
        text = std::string (elt->GetText ());
      config_.insert (std::pair<std::string, std::string > (elt->ValueStr (), text));
    }
    elt = elt->NextSiblingElement ();
  }
}

void
Config::loadFiles ()
{
  namespace fs = boost::filesystem;
  fs::path p ("movie/");
  if (!fs::exists (p))
  {
    COUTDEBUG ("The folder \"movie\" n'exite pas !!!");
    std::exit(2);
  }
  if (fs::is_directory (p))
  {
    fs::directory_iterator end_itr;
    for (fs::directory_iterator itr (p); itr != end_itr; ++itr)
    {
      if (fs::is_directory (*itr))
        continue;
      //  On récupère le nom du fichier sans l'extension (qui est l'id du fichier)
      std::string file = itr->path().filename().string();
      std::size_t pos = file.rfind(".");
      file.resize (pos);
      SqlManager::getInstance ().setFileServer (file);

    }
  }
}

void
Config::print ()
{
  std::map<std::string, std::string>::iterator i;
  for (i = config_.begin (); i != config_.end (); ++i)
    std::cout << i->first << "-" << i->second << std::endl;
}

bool
Config::check ()
{
  //  config_.find ()
  return true;
}

void
Config::add (std::string key, int value)
{
  mutex_.lock ();
  config_.insert (std::pair<std::string, std::string > (key, tools::toString<int> (value)));
  mutex_.unlock ();
}

void
Config::add (std::string key, std::string value)
{
  mutex_.lock ();
  config_.insert (std::pair<std::string, std::string > (key, value));
  mutex_.unlock ();
}

int
Config::getInt (std::string key)
{
  int value_int;
  mutex_.lock ();
  std::string value_str = config_.at (key);
  mutex_.unlock ();
  tools::fromString (value_str, value_int);
  return value_int;
}

std::string
Config::getString (std::string key)
{
  std::string value;
  mutex_.lock ();
  value = config_.at (key);
  mutex_.unlock ();
  return value;
}

void
Config::setIsOnline (bool isOnline_)
{
  mutex_.lock ();
  this->isOnline_ = isOnline_;
  mutex_.unlock ();
}

bool
Config::isOnline () const
{
  return isOnline_;
}
