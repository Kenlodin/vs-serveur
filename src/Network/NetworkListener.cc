/*
 * NetworkListener.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "NetworkListener.hh"

NetworkListener::NetworkListener(sf::SocketTCP& server
    , void(*add)(sf::SocketTCP&, sf::IPAddress&))
 : server_ (server)
, add_ (add)
{
  // TODO Auto-generated constructor stub

}

NetworkListener::~NetworkListener()
{
  // TODO Auto-generated destructor stub
}

void NetworkListener::run ()
{
  sf::SocketTCP client;
  sf::IPAddress ip;
  while (server_.IsValid())
  {
    server_.Accept(client, &ip);
    add_(client, ip);
  }
}

