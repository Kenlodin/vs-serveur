/*
 * Tracker.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "Tracker.hh"

Tracker::Tracker()
    : route_(
    { &Tracker::ctConnMaster, &Tracker::ctConnSlave, &Tracker::ctAskList,
        &Tracker::ctAskFlux, &Tracker::ctAskCheck, &Tracker::ctAskPacket,
        &Tracker::ctAskRpacket, &Tracker::ctAskMove, &Tracker::ctAskDeficient,
        &Tracker::ctAskRem, &Tracker::ctAskStop, &Tracker::ctDec, })
{
  // TODO Auto-generated constructor stub

}

Tracker::~Tracker()
{
  // TODO Auto-generated destructor stub
}

int Tracker::routing(unsigned int code, sf::Packet* packet)
{
  if (code < CT::LENGTH)
    (this->*route_[code])(packet);
  else
    return TRUE;
  return FALSE;
}

int Tracker::ctConnMaster(sf::Packet* packet)
{
  std::string login;
  std::string password;
  std::string privateIp;
  sf::Int16 bandwidth;

  // Extract content of packet
  packet >> login;
  packet >> password;
  packet >> privateIp;
  packet >> bandwidth;
  return FALSE;
}

int Tracker::ctConnSlave(sf::Packet* packet)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  return FALSE;
}

int Tracker::ctAskList(sf::Packet* packet)
{
  std::string token;
  sf::Int8 filter;
  std::string regexFilter;

  // Extract content of packet
  packet >> token;
  packet >> filter;
  packet >> regexFilter;
  return FALSE;
}

int Tracker::ctAskFlux(sf::Packet* packet)
{
  std::string token;
  sf::Int32 videoId;

  // Extract content of packet
  packet >> token;
  packet >> videoId;
  return FALSE;
}

int Tracker::ctAskCheck(sf::Packet* packet)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  return FALSE;
}

int Tracker::ctAskPacket(sf::Packet* packet)
{
  std::string token;
  sf::Int32 nbFrame;
  sf::Int32 frameNumber[];

  // Extract content of packet
  packet >> token;
  packet >> nbFrame;
  frameNumber = new sf::Int32[nbFrame];
  for (int i = 0; i < nbFrame; i++)
  {
    packet >> frameNumber[i];
  }
  return FALSE;
}

int Tracker::ctAskRpacket(sf::Packet* packet)
{
  std::string token;
  sf::Int32 firstFrame;
  sf::Int32 lastFrame;

  // Extract content of packet
  packet >> token;
  packet >> firstFrame;
  packet >> lastFrame;
  return FALSE;
}

int Tracker::ctAskMove(sf::Packet* packet)
{
  std::string token;
  sf::Int32 nPosition;

  // Extract content of packet
  packet >> token;
  packet >> nPosition;
  return FALSE;
}

int Tracker::ctAskDeficient(sf::Packet* packet)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  return FALSE;
}

int Tracker::ctAskRem(sf::Packet* packet)
{
  std::string token;
  sf::Int32 startFrame;
  sf::Int8 endFrame;

  // Extract content of packet
  packet >> token;
  packet >> startFrame;
  packet >> endFrame;
  return FALSE;
}

int Tracker::ctAskStop(sf::Packet* packet)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  return FALSE;
}

int Tracker::ctDec(sf::Packet* packet)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  return FALSE;
}
