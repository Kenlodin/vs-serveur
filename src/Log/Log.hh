/* 
 * File:   Log.hh
 * Author: Aymeric
 *
 * Created on 18 avril 2012, 20:24
 */

#ifndef LOG_HH
#define	LOG_HH

#include <iostream>
#include <fstream>

#ifndef DEBUG
#define COUT(MSG) (std::cout << MSG << std::endl)
#endif

/**
 * La classe log permet de mettre en place un systeme de log. C'est un singleton
 * qui ne nécessite pas d'être thread-safe.
 * 
 * @param file
 */
class Log
{
 public:
  void setFile (std::string file);
  void write (std::string tag, std::string msg);
  bool getIsActive ();

 private:
  std::ofstream file_;
  bool isActive_;

 public:
  static Log* getInstance ();
  
 private:
  Log () { }
  ~Log () { }
} ;

#endif	/* LOG_HH */

