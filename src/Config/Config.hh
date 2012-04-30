/* 
 * File:   Config.hh
 * Author: Aymeric
 *
 * Created on 19 avril 2012, 16:41
 */

#ifndef CONFIG_HH
#define	CONFIG_HH

#include <map>
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <tinyxml.h>
#include "../Tools/Tools.hh"
#include "../SqlManager/SqlManager.hh"

class Config
{
 public:
  static Config& getInstance ();
  void load (std::string file);
  void loadConfig ();
  void loadFiles ();

  void print ();
  bool check ();
  void add (std::string key, int value);
  void add (std::string key, std::string value);
  int getInt (std::string key);
  std::string getString (std::string key);

 private:
  std::map<std::string, std::string> config_;
  TiXmlDocument c_;
  boost::mutex mutex_;

  Config () { };
} ;

#endif	/* CONFIG_HH */

