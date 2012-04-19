/*
 * LiveClient.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "LiveClient.hh"
#include "../FileManager/LiveHandler.hh"

LiveClient::LiveClient(sf::SocketTCP& control, sf::SocketTCP& data, int videoId)
 : Client(control, data, videoId)
{
  // TODO Auto-generated constructor stub
  setFileVideo(LiveHandler::getInstance().getLive(videoId));
}

LiveClient::~LiveClient()
{
  // TODO Auto-generated destructor stub
  LiveHandler::getInstance().leaveLive(getVideoId());
}

Chuck* LiveClient::getElement(int number)
{
  return getFileVideo()->getPacket(number);
}

