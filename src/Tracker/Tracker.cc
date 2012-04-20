/*
 * Tracker.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "Tracker.hh"
#include "../Network/ClientList.hh"

Tracker::Tracker()
    : route_(
    {
        &Tracker::ctConnMaster,
        &Tracker::ctConnSlave,
        &Tracker::ctAskList,
        &Tracker::ctAskFlux,
        &Tracker::ctAskCheck,
        &Tracker::ctAskPacket,
        &Tracker::ctAskRpacket,
        &Tracker::ctAskMove,
        &Tracker::ctAskDeficient,
        &Tracker::ctAskRem,
        &Tracker::ctAskStop,
        &Tracker::ctDec, })
{
  // TODO Auto-generated constructor stub

}

Tracker::~Tracker()
{
  // TODO Auto-generated destructor stub
}

int Tracker::routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock)
{
  if (code < CT::LENGTH)
    (this->*route_[code])(packet, sock);
  else
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctConnMaster(sf::Packet& packet, sf::SocketTCP& sock)
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
  sf::SocketTCP newSocket = sock; //TODO Check copy
  ClientList::getInstance().addClient(newSocket, nullptr, "");
  return RETURN_VALUE_GOOD;
}

int Tracker::ctConnSlave(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  sf::SocketTCP newSocket = sock; //TODO Check copy
  ClientList::getInstance().addClient(newSocket, nullptr, token);
  return RETURN_VALUE_GOOD; // We keep control socket in selector
}

int Tracker::ctAskList(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  sf::Int8 filter;
  std::string regexFilter;

  // Extract content of packet
  packet >> token;
  packet >> filter;
  packet >> regexFilter;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskFlux(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  sf::Int32 videoId;

  // Extract content of packet
  packet >> token;
  packet >> videoId;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskCheck(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskPacket(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  sf::Int32 nbFrame;
  sf::Int32* frameNumber;

  // Extract content of packet
  packet >> token;
  packet >> nbFrame;
  frameNumber = new sf::Int32[nbFrame];
  for (int i = 0; i < nbFrame; i++)
  {
    packet >> frameNumber[i];
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskRpacket(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  sf::Int32 firstFrame;
  sf::Int32 lastFrame;

  // Extract content of packet
  packet >> token;
  packet >> firstFrame;
  packet >> lastFrame;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskMove(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  sf::Int32 nPosition;

  // Extract content of packet
  packet >> token;
  packet >> nPosition;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskDeficient(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskRem(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  sf::Int32 startFrame;
  sf::Int8 endFrame;

  // Extract content of packet
  packet >> token;
  packet >> startFrame;
  packet >> endFrame;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskStop(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctDec(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  return RETURN_VALUE_GOOD;
}

int Tracker::tcToken(sf::SocketTCP& sender, std::string token)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::TOKEN);

  // Create packet
  packet << opcode;
  packet << token;
  return send(sender, packet);
}

int Tracker::tcList(sf::SocketTCP& sender, std::string name[], sf::Int32 id[],
    sf::Int32 number)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST);

  // Create packet
  packet << opcode;
  packet << number;
  for (int i = 0; i < number; i++)
  {
    packet << name[i];
    packet << id[i];
  }
  return send(sender, packet);
}

int Tracker::tcListDiff(sf::SocketTCP& sender, std::string ip[],
    sf::Int16 port[], sf::Int8 number)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_DIFF);

  // Create packet
  packet << opcode;
  packet << number;
  for (int i = 0; i < number; i++)
  {
    packet << ip[i];
    packet << port[i];
  }
  return send(sender, packet);
}

int Tracker::tcListDiff(sf::SocketTCP& sender, std::string ip1, sf::Int16 port1,
    std::string ip2, sf::Int16 port2, std::string ip3, sf::Int16 port3)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_DIFF);
  sf::Int8 number = 3;

  // Create packet
  packet << opcode;
  packet << number;
  packet << ip1;
  packet << port1;
  packet << ip2;
  packet << port2;
  packet << ip3;
  packet << port3;
  return send(sender, packet);
}

int Tracker::tcListNDiff(sf::SocketTCP& sender, std::string ip[],
    sf::Int16 port[], sf::Int8 number)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_NDIFF);

  // Create packet
  packet << opcode;
  packet << number;
  for (int i = 0; i < number; i++)
  {
    packet << ip[i];
    packet << port[i];
  }
  return send(sender, packet);
}

int Tracker::tcListNDiff(sf::SocketTCP& sender, std::string ip, sf::Int16 port)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_NDIFF);
  sf::Int8 number = 1;

  // Create packet
  packet << opcode;
  packet << number;
  packet << ip;
  packet << port;
  return send(sender, packet);
}

int Tracker::tcListNDiff(sf::SocketTCP& sender, std::string ip1,
    sf::Int16 port1, std::string ip2, sf::Int16 port2)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_NDIFF);
  sf::Int8 number = 2;

  // Create packet
  packet << opcode;
  packet << number;
  packet << ip1;
  packet << port1;
  packet << ip2;
  packet << port2;
  return send(sender, packet);
}

int Tracker::tcListNDiff(sf::SocketTCP& sender, std::string ip1,
    sf::Int16 port1, std::string ip2, sf::Int16 port2, std::string ip3,
    sf::Int16 port3)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_NDIFF);
  sf::Int8 number = 3;

  // Create packet
  packet << opcode;
  packet << number;
  packet << ip1;
  packet << port1;
  packet << ip2;
  packet << port2;
  packet << ip3;
  packet << port3;
  return send(sender, packet);
}

Tracker& Tracker::getInstance()
{
  static Tracker instance_;

  return instance_;
}

int Tracker::tcMsg(sf::SocketTCP& sender, sf::Int32 numMsg, std::string msg)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::MSG);

  // Create packet
  packet << opcode;
  packet << numMsg;
  packet << msg;
  return send(sender, packet);
}

int Tracker::send(sf::SocketTCP& sender, sf::Packet& packet)
{
  if (sender.Send(packet) == sf::Socket::Done)
    return RETURN_VALUE_GOOD;
  return RETURN_VALUE_ERROR;
}
