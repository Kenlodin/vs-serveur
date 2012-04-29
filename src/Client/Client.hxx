/*
 * Client.hxx
 *
 *  Created on: 29 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENT_HXX_
# define CLIENT_HXX_

# include "Client.hh"

inline
sf::SocketTCP Client::getControlSocket() const
{
  return controlSocket_;
}

inline
sf::SocketTCP* Client::getDataSocket() const
{
  return dataSocket_;
}

inline
void Client::setDataSocket(sf::SocketTCP* dataSocket)
{
  dataSocket_ = dataSocket;
}

inline
std::string Client::getToken() const
{
  return token_;
}

inline
void Client::setToken(std::string token)
{
  token_ = token;
}

inline
TypeClient* Client::getTypeClient() const
{
  return typeClient_;
}

inline
void Client::setTypeClient(TypeClient* typeClient)
{
  typeClient_ = typeClient;
}

#endif /* CLIENT_HXX_ */
