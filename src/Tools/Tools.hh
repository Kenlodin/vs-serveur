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
  std::string toString (int value);
  
  template <typename T>
  bool fromString (const std::string str, T& dest);


  std::string token (std::string private_ip, std::string public_ip);
}

#include "string.hxx"

#endif	/* TOOLS_HH */

