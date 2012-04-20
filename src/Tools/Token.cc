#include "Tools.hh"

std::string
tools::token (std::string private_ip, std::string public_ip)
{
  time_t t;
  int x;
  int r;
  srand (time (0));

  t = time (0);
  x = static_cast<int>(t);
  r = (int)rand ();
  std::string rand = toString (r);
  std::string time = toString (x);
  std::string tmp = private_ip + public_ip + time + rand;
  return tmp;
}