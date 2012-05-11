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
  setFileVideo(LiveHandler::getInstance().getLive(videoId));
}

LiveClient::~LiveClient()
{
  LiveHandler::getInstance().leaveLive(getVideoId());
}



