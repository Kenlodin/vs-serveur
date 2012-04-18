/*
 * Client.cpp
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "Client.hh"

Client::Client(sf::SocketTCP& control, sf::SocketUDP& data)
: controlSocket_ (control)
, dataSocket_ (data)
{
  // TODO Auto-generated constructor stub

}

Client::~Client()
{
  // TODO Auto-generated destructor stub
}

sf::SocketTCP& Client::getControlSocket() const
{
  return controlSocket_;
}

sf::SocketUDP& Client::getDataSocket() const
{
  return dataSocket_;
}


