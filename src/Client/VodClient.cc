/*
 * VodClient.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "VodClient.hh"

VodClient::VodClient(sf::SocketTCP& control, sf::SocketUDP& data)
: Client(control, data)
{
  // TODO Auto-generated constructor stub

}

VodClient::~VodClient()
{
  // TODO Auto-generated destructor stub
}

Chuck* VodClient::getElement(int number)
{
  return nullptr;
}


