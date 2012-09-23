/*
 * PacketHandler.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include <core/PacketHandler.hh>
#include <core/fwd.hh>

PacketHandler::~PacketHandler()
{
}

int PacketHandler::routing_internal(unsigned int code __attribute__((unused))
  , Packet& packet __attribute__((unused)))
{
  return RETURN_VALUE_ERROR;
}


