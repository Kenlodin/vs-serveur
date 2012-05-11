/*
 * VodClient.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "VodClient.hh"

VodClient::VodClient(int videoId)
: TypeClient(videoId)
{
  setFileVideo(VodHandler::getInstance().getVod(videoId));
}

VodClient::~VodClient()
{
  VodHandler::getInstance().leaveVod(getVideoId());

}



