/* 
 * File:   Tools.hh
 * Author: Aymeric
 *
 * Created on 19 avril 2012, 16:49
 */

#ifndef TOOLS_HH
#define	TOOLS_HH

#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

namespace tools
{
  template <typename T>
  std::string toString (T value)
  {
    std::ostringstream oss;
    oss << value;
    return oss.str ();
  }
  
  template <typename T>
  bool fromString (const std::string str, T& dest)
  {
    // créer un flux à partir de la chaîne donnée
    std::istringstream iss (str);
    // tenter la conversion vers Dest
    return (iss >> dest) != 0;
  }


  std::string token (std::string private_ip, std::string public_ip);
}

#endif	/* TOOLS_HH */

