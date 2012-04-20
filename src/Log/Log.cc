/* 
 * File:   Log.cc
 * Author: Aymeric
 * 
 * Created on 18 avril 2012, 20:24
 */

#include <fstream>

#include "Log.hh"

Log&
Log::getInstance ()
{
  static Log instance;
  
  return instance;
}

void
Log::setFile (std::string file)
{
  if (file_.is_open ())
    file_.close ();
  file_.open (file, std::ios_base::app);
  if (file_.is_open ())
    isActive_ = true;
  else
  {
    std::cerr << "Impossible d'ouvrir le fichier. Le système de log est désactivé." << std::endl;
    isActive_ = false;
  }
}

bool
Log::getIsActive ()
{
  return isActive_;
}

void
Log::write (std::string tag, std::string msg)
{
  std::string m;
  m += "[" + tag + "] " + msg;
  if (isActive_)
    file_ << m << std::endl;
  COUT (m);
}
