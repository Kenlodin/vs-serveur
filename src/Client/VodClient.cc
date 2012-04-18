/*
 * VodClient.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "VodClient.hh"

VodClient::VodClient(sf::SocketTCP& control, sf::SocketUDP& data, int videoId)
: Client(control, data, videoId)
{
  // TODO Auto-generated constructor stub
  setFileVideo(new VodFile(videoId));
}

VodClient::~VodClient()
{
  // TODO Auto-generated destructor stub

}

Chuck* VodClient::getElement(int number)
{
  return getFileVideo()->getPacket(number);
}


