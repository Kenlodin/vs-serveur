/*
 * Client.hxx
 *
 *  Created on: 29 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENT_HXX_
# define CLIENT_HXX_

# include <core/client/Client.hh>

inline
sf::SocketTCP* Client::getControlSocket() const
{
  return controlSocket_;
}

inline
void Client::setControlSocket(sf::SocketTCP* controlSocket)
{
  delete controlSocket_;
  controlSocket_ = controlSocket;
}

inline
sf::SocketTCP* Client::getDataSocket() const
{
  return dataSocket_;
}

inline
void Client::setDataSocket(sf::SocketTCP* dataSocket)
{
  delete dataSocket_;
  dataSocket_ = dataSocket;
}

inline
std::string& Client::getToken()
{
  return token_;
}

inline
void Client::setToken(std::string token)
{
  token_ = token;
}

inline
FileVideo* Client::getTypeClient() const
{
  return typeClient_;
}

inline
void Client::setTypeClient(FileVideo* typeClient)
{
  typeClient_ = typeClient;
}

inline
bool Client::tryLock()
{
  return using_.try_lock();
}

inline
void Client::lock()
{
  using_.lock();
}

inline
void Client::unlock()
{
  using_.unlock();
}

#endif /* CLIENT_HXX_ */
