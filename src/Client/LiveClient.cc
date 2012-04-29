/*
 * LiveClient.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

// Internal include
#include "LiveClient.hh"
#include "../FileManager/LiveHandler.hh"

LiveClient::LiveClient(int videoId)
 : TypeClient(videoId)
{
  // TODO Auto-generated constructor stub
  setFileVideo(LiveHandler::getInstance().getLive(videoId));
}

LiveClient::~LiveClient()
{
  // TODO Auto-generated destructor stub
  LiveHandler::getInstance().leaveLive(getVideoId());
}

Chunk* LiveClient::getElement(int number)
{
  return getFileVideo()->getPacket(number);
}


