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

int PacketHandler::routing_internal(unsigned int code, sf::Packet* packet)
{
  return RETURN_VALUE_ERROR;
}


