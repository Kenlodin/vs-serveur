#include "Tools.hh"

std::string tools::toString (int x)
{
  std::ostringstream oss;
  oss << x;
  return oss.str ();
}