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
  std::string toString (int value);
  bool fromString (const std::string str, int& dest);


  std::string token (std::string private_ip, std::string public_ip);
}

#endif	/* TOOLS_HH */

