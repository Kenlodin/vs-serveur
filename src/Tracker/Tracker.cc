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
  sf::Uint16 bandwidth;

  // Extract content of packet
  packet >> login;
  packet >> password;
  packet >> privateIp;
  packet >> bandwidth;
  sf::SocketTCP newSocket = sock; //TODO Check copy
  std::string publicIp = ClientList::getInstance().getPrivateIp(sock);
  std::string token = SqlManager::getInstance().addClient(login, password,
      privateIp, publicIp, bandwidth);
  tcToken(sock, token);
  ClientList::getInstance().addClient(newSocket, nullptr, token);
  return RETURN_VALUE_GOOD;
}

int Tracker::ctConnSlave(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  sf::SocketTCP newSocket = sock; //TODO Check copy
  //TODO serverId and return value.
  SqlManager::getInstance().saveClientServerConnection(token, 0);
  ClientList::getInstance().addClient(newSocket, nullptr, token);
  return RETURN_VALUE_GOOD; // We keep control socket in selector
}

int Tracker::ctAskList(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  sf::Uint8 filter;
  std::string regexFilter;

  // Extract content of packet
  packet >> token;
  packet >> filter;
  packet >> regexFilter;
  sql_result res = SqlManager::getInstance().getAllFlux();
  tcList(sock, res);
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskFlux(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  sf::Int32 videoId;

  // Extract content of packet
  packet >> token;
  packet >> videoId;
  SqlManager::getInstance().getFlux(videoId);
  //TODO add handling
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
  sf::Int32 endFrame;

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
  sf::Uint16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::TOKEN);

  // Create packet
  packet << opcode;
  packet << token;
  return send(sender, packet);
}

int Tracker::tcList(sf::SocketTCP& sender, sql_result sqlResult)
{
  sf::Packet packet;
  sf::Uint16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST);
  sf::Int32 length;

  // Create packet
  packet << opcode;
  length = sqlResult.size();
  packet << length;
  for (unsigned int i = 0; i < sqlResult.size(); i++)
  {
    pqxx::result::tuple t = sqlResult.at(i);
    packet << t["name"].c_str();
    packet << t["id"].c_str();
  }
  return send(sender, packet);
}

int Tracker::tcListDiff(sf::SocketTCP& sender, sql_result sqlResult)
{
  sf::Packet packet;
  sf::Uint16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_DIFF);
  sf::Uint8 length;
  sf::Uint16 port;

  // Create packet
  packet << opcode;
  length = sqlResult.size();
  packet << length;
  for (unsigned int i = 0; i < sqlResult.size(); i++)
  {
    pqxx::result::tuple t = sqlResult.at(i);
    packet << t["ip"].c_str();
    tools::fromString<sf::Uint16>(t["ip"].c_str(), port);
    packet << port;
  }
  return send(sender, packet);
}

int Tracker::tcListNDiff(sf::SocketTCP& sender, sql_result sqlResult)
{
  sf::Packet packet;
  sf::Uint16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_NDIFF);
  sf::Uint8 length;
  std::string temp;
  sf::Uint16 port;

  // Create packet
  packet << opcode;
  length = sqlResult.size();
  packet << length;
  for (unsigned int i = 0; i < sqlResult.size(); i++)
  {
    pqxx::result::tuple t = sqlResult.at(i);
    tools::fromString<sf::Uint16>(t["ip"].c_str(), port);
    port = sf::Uint16(t["port"].c_str());
    packet << port;
  }
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
  sf::Uint16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::MSG);

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
