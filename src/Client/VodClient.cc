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
  // TODO Auto-generated constructor stub
  setFileVideo(VodHandler::getInstance().getVod(videoId));
}

VodClient::~VodClient()
{
  // TODO Auto-generated destructor stub

}



