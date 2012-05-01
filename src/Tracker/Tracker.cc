/*
 * Tracker.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "Tracker.hh"
#include "../Network/ClientList.hh"
#include "../Client/LiveClient.hh"
#include "../Client/VodClient.hh"

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
  int retVal = RETURN_VALUE_ERROR;
  COUTDEBUG(code);
  if (code < CT::LENGTH
      && (retVal = (this->*route_[code])(packet, sock)) == RETURN_VALUE_GOOD)
    return RETURN_VALUE_GOOD;
  else
  {
    COUTDEBUG("Tracker : mauvais routing.");
    ClientList::getInstance().addBadClient(sock, retVal);
    return RETURN_VALUE_ERROR;
  }
}

int Tracker::ctConnMaster(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string login;
  std::string password;
  std::string privateIp;
  sf::Uint16 bandwidth;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> login;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> password;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> privateIp;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> bandwidth;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG(
      "Client --> Tracker : Connection master (" + login + ", " + password + ", " + privateIp + ")");
  if (count != 5)
    return RETURN_VALUE_ERROR;
  std::string publicIp = ClientList::getInstance().getPrivateIp(sock);
  std::string token = SqlManager::getInstance().addClient(login, password,
      privateIp, publicIp, bandwidth);
  if (token == "")
    return RETURN_VALUE_ERROR;
  tcToken(sock, token);
  ClientList::getInstance().addClient(sock, nullptr, token);
  return RETURN_VALUE_GOOD;
}

int Tracker::ctConnSlave(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> token;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Connection slave (" + token + ")");
  if (count != 2)
    return RETURN_VALUE_ERROR;
  //TODO serverId and return value.
  SqlManager::getInstance().saveClientServerConnection(token, 0);
  ClientList::getInstance().addClient(sock, nullptr, token);
  return RETURN_VALUE_GOOD; // We keep control socket in selector
}

int Tracker::ctAskList(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Uint8 filter;
  std::string regexFilter;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> filter;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> regexFilter;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask list");
  if (count != 3)
    return RETURN_VALUE_ERROR;
  sql_result res = SqlManager::getInstance().getAllFlux();
  tcList(sock, res);
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskFlux(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 videoId;
  int count = 0;
  Client* client;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> videoId;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask flux");
  if (count != 2)
    return RETURN_VALUE_ERROR;
  client = ClientList::getInstance().getClient(sock);
  if (client == nullptr)
    return RETURN_VALUE_ERROR;
  SqlManager::getInstance().setHandlings(client->getToken(), videoId);
  client->unlock();
  sql_result res = SqlManager::getInstance().getThreeServers(); //TODO videoId
  client->setTypeClient(new VodClient(videoId));
  return tcListDiff(sock, res);
}

int Tracker::ctAskCheck(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask check");
  if (count != 1)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskPacket(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 nbFrame;
  sf::Int32* frameNumber;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> nbFrame;
  INCTEST(!packet.EndOfPacket(), count)
  frameNumber = new sf::Int32[nbFrame];
  for (int i = 0; i < nbFrame; i++)
  {
    INCTEST(!packet.EndOfPacket(), count)
    packet >> frameNumber[i];
  }
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask packet");
  if (count != 3 + nbFrame)
  {
    delete frameNumber;
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskRpacket(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 firstFrame;
  sf::Int32 lastFrame;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> firstFrame;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> lastFrame;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask range packet");
  if (count != 3)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskMove(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 nPosition;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count);
  packet >> nPosition;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask move");
  if (count != 2)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskDeficient(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask deficient");
  if (count != 1)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskRem(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 startFrame;
  sf::Int32 endFrame;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> startFrame;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> endFrame;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask remove");
  if (count != 3)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskStop(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask stop");
  if (count != 1)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Tracker::ctDec(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Deconnection");
  if (count != 1)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Tracker::tcToken(sf::SocketTCP& sender, std::string token)
{
  sf::Packet packet;
  sf::Uint16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::TOKEN);

  // Create packet
  packet << opcode;
  packet << token;
  COUTDEBUG("Tracker --> Client : Token = " + token);
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
    sf::Int32 id;
    packet << t["name"].c_str();
    id = atoi(t["id"].c_str());
    packet << id;
  }
  COUTDEBUG("Tracker --> Client : list");
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
    tools::fromString<sf::Uint16>(t["port"].c_str(), port);
    packet << port;
  }
  COUTDEBUG("Tracker --> Client : list diffusion");
  return send(sender, packet);
}

int Tracker::tcListNDiff(sf::SocketTCP& sender, sql_result sqlResult)
{
  sf::Packet packet;
  sf::Uint16 opcode =
      MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_NDIFF);
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
    packet << t["ip"].c_str();
    tools::fromString<sf::Uint16>(t["port"].c_str(), port);
    packet << port;
  }
  COUTDEBUG("Tracker --> Client : list new diffusion");
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
  COUTDEBUG("Tracker --> Client : send msg");
  return send(sender, packet);
}

int Tracker::send(sf::SocketTCP& sender, sf::Packet& packet)
{
  if (sender.Send(packet) == sf::Socket::Done)
    return RETURN_VALUE_GOOD;

  return RETURN_VALUE_ERROR;
}
