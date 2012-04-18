/*
 * LiveClient.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "LiveClient.hh"

LiveClient::LiveClient(sf::SocketTCP& control, sf::SocketUDP& data)
 : Client(control, data)
{
  // TODO Auto-generated constructor stub

}

LiveClient::~LiveClient()
{
  // TODO Auto-generated destructor stub
}

Chuck* LiveClient::getElement(int number)
{
  return nullptr;
}


