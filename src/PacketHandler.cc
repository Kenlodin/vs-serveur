/*
 * PacketHandler.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "PacketHandler.hh"
#include "fwd.hh"

PacketHandler::~PacketHandler()
{
}

int PacketHandler::routing_internal(unsigned int code __attribute__((unused))
  , sf::Packet* packet __attribute__((unused)))
{
  return RETURN_VALUE_ERROR;
}


