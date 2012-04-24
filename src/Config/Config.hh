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
#include "../Tools/Tools.hh"

class Config
{
 public:
  static Config& getInstance ();
  void load (std::string file);
  void print ();
  int getPort ();
  bool check ();
 private:
  std::map<std::string, std::string> config_;

 private:
  Config () { };
} ;

#endif	/* CONFIG_HH */

