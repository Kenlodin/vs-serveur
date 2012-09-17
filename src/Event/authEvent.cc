#include <core/event/authEvent.hh>

int EventAuth::launch(std::vector<boost::any> params)
{
  sf::SocketTCP   sock       = boost::any_cast<sf::SocketTCP&>(params[0]);
  std::string     login      = boost::any_cast<std::string>(params[1]);
  std::string     password   = boost::any_cast<std::string>(params[2]);
  std::string     ip         = boost::any_cast<std::string>(params[3]) ;
  unsigned short  bandwidth  = boost::any_cast<unsigned short>(params[4]);
  std::string     publicIp, token;

  publicIp = ClientList::getInstance().getPrivateIp(sock);
  token =  SqlManager::getInstance().addClient(login,
                                               password, 
                                               ip, 
                                               publicIp, 
                                               bandwidth);
  
  if (token == "")
  {
    Tracker::getInstance().tcMsg(sock, 
                                 RETURN_VALUE_ERROR, 
                                 std::string("Tracker : Empty token."));
    return RETURN_VALUE_ERROR;
  }

  sf::SocketTCP* control = new sf::SocketTCP(sock);
  if (ClientList::getInstance().addClient(control,
                                          nullptr,
                                          token)
      == RETURN_VALUE_ERROR)
  {
    Tracker::getInstance().tcMsg(sock,
                                 RETURN_VALUE_ERROR, 
                                 std::string("Tracker : Client with this token"
                                             " already connected."));
    delete control;
    return RETURN_VALUE_ERROR;
  }
  return Tracker::getInstance().tcToken(sock, token);
}
