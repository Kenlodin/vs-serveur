

template <typename T>
std::string
tools::toString (T& value)
{
  std::ostringstream oss;
  oss << value;
  return oss.str ();
}

template <typename T>
bool
tools::fromString (const std::string str, T& dest)
{
  // créer un flux à partir de la chaîne donnée
  std::istringstream iss (str);
  // tenter la conversion vers Dest
  return (iss >> dest) != 0;
}
