#include "Tools.hh"

std::string
tools::toString (int value)
{
  std::ostringstream oss;
  oss << value;
  return oss.str ();
}

bool
tools::fromString (const std::string str, int& dest)
{
  // créer un flux à partir de la chaîne donnée
  std::istringstream iss (str);
  // tenter la conversion vers Dest
  return iss >> dest != 0;
}