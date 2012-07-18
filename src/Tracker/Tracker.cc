/*
 * Tracker.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include <core/tracker/Tracker.hh>
#include <core/network/ClientList.hh>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
        &Tracker::ctDec,
        &Tracker::ctPing,
        &Tracker::ctUrl, })
{
}

Tracker::~Tracker()
{
}

int Tracker::routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock)
{
  int retVal = RETURN_VALUE_ERROR;
  COUTDEBUG(code);
  if (code < CT::LENGTH)
  {
      if ((retVal = (this->*route_[code])(packet, sock)) == RETURN_VALUE_ERROR)
      {
        COUTDEBUG("Tracker : mauvais processing.");
        ClientList::getInstance().addBadClient(sock, retVal);
        return retVal;
      }
    return RETURN_VALUE_GOOD;
  }
  else
  {
    COUTDEBUG("Tracker : mauvais routing.");
    ClientList::getInstance().addBadClient(sock, retVal);
    Tracker::getInstance().tcMsg(sock, retVal
              , std::string("Tracker : Bad command code."));
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

  COUTDEBUG(1);
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
      "Client --> Tracker : Connection master (" + login + ", "
      + password + ", " + privateIp + ")");
  if (count != 5)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
          , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(2);
  std::string publicIp = ClientList::getInstance().getPrivateIp(sock);
  COUTDEBUG(3);
  std::string token = SqlManager::getInstance().addClient(login, password,
      privateIp, publicIp, bandwidth);
  COUTDEBUG(4);
  if (token == "")
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
              , std::string("Tracker : Empty token."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(5);
  sf::SocketTCP* control = new sf::SocketTCP(sock);
  if (ClientList::getInstance().addClient(control, nullptr, token)
      == RETURN_VALUE_ERROR)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
              , std::string("Tracker : Client with this token"
                  " already connected."));
    delete control;
    COUTDEBUG(6);
    return RETURN_VALUE_ERROR;
  }
  return tcToken(sock, token);
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
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
            , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(6);
  SqlManager::getInstance().saveClientServerConnection(token
      , Config::getInstance().getInstance().getInt("server_id"));
  COUTDEBUG(7);
  sf::SocketTCP* control = new sf::SocketTCP(sock);
  if (ClientList::getInstance().addClient(control, nullptr, token)
      == RETURN_VALUE_ERROR)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
                  , std::string("Tracker : Client with this token"
                      " already connected."));
    delete control;
  COUTDEBUG(8);
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(7.5);
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
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(9);
  sql_result res = SqlManager::getInstance().getAllFlux();
  COUTDEBUG(10);

  return tcList(sock, res);
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
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(11);
  client = ClientList::getInstance().getClient(sock);
  COUTDEBUG(12);
  if (client == nullptr)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
                , std::string("Tracker : Unknown client."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(13);
  SqlManager::getInstance().removeClientServerConnection(client->getToken()
    , Config::getInstance().getInt("server_id")); 
  SqlManager::getInstance().setHandlings(client->getToken(), videoId);
  COUTDEBUG(14);
  client->unlock();
  sql_result res = SqlManager::getInstance().getThreeServers(); //TODO videoId
  COUTDEBUG(15);
  return tcListDiff(sock, res);
}

int Tracker::ctAskCheck(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask check");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
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
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    delete frameNumber;
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(17);
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
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
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
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskDeficient(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask deficient");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
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
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskStop(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask stop");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  
  Client* client = ClientList::getInstance().getClient(sock);
  delete client->getTypeClient();
  client->setTypeClient(nullptr);
  COUTDEBUG(18);
  if (client == nullptr)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
                , std::string("Tracker : Unknown client."));
    return RETURN_VALUE_ERROR;
  }
  
  SqlManager::getInstance().deleteHandlings (client->getToken());
  COUTDEBUG(19);
  return RETURN_VALUE_GOOD;
}

int Tracker::ctDec(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Deconnection");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctPing(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ping");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return tcPing(sock);
}

int Tracker::ctUrl(sf::Packet& packet, sf::SocketTCP& sock)
{
  int count = 0;
  int videoId = 0;
  std::string url = "";
  std::string ip = "";

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> videoId;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Url");
  if (count != 2)
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(19);
  struct stat unused;
  url = "movie/" + tools::toString(videoId) + ".flv";
  if (stat(url.c_str(), &unused) == -1)
    url = url.substr(0, url.length() - 3) + "mp4";
  url = "/" + url;  
  // Get free server
  COUTDEBUG(20);
  ip = "37.59.85.217";
  return tcUrl(sock, ip, url);
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
  sf::Int32 length = 0;

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
    packet << t["description"].c_str();
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
  COUTDEBUG("Tracker --> Client : send msg : " << msg);
  return send(sender, packet);
}

int Tracker::tcPing(sf::SocketTCP& sender)
{
  sf::Packet packet;
  sf::Uint16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::PING);

  // Create packet
  packet << opcode;
  COUTDEBUG("Tracker --> Client : send ping");
  return send(sender, packet);
}

int Tracker::tcUrl(sf::SocketTCP& sender, std::string& ip, std::string& url)
{
  sf::Packet packet;
  sf::Uint16 opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::URL);

  // Create packet
  packet << opcode;
  packet << ip;
  packet << url;
  COUTDEBUG("Tracker --> Client : send url");
  return send(sender, packet);
}

int Tracker::send(sf::SocketTCP& sender, sf::Packet& packet)
{
    COUTDEBUG(30);
  if (sender.IsValid() && sender.Send(packet) == sf::Socket::Done)
  {
    COUTDEBUG(31);
    return RETURN_VALUE_GOOD;
  }
    COUTDEBUG(32);
  return RETURN_VALUE_ERROR;
}


