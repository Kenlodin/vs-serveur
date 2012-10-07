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

int Tracker::routing(unsigned int code, Packet& packet, Client*& client)
{
  int retVal = RETURN_VALUE_ERROR;
  COUTDEBUG(code);
  if (code < CT::LENGTH)
  {
      if ((retVal = (this->*route_[code])(packet, client)) == RETURN_VALUE_ERROR)
      {
        COUTDEBUG("Tracker : mauvais processing.");
        ClientList::getInstance().addBadClient(client, retVal);
        return retVal;
      }
    return RETURN_VALUE_GOOD;
  }
  else
  {
    COUTDEBUG("Tracker : mauvais routing.");
    ClientList::getInstance().addBadClient(client, retVal);
    Tracker::getInstance().tcMsg(client, retVal
              , std::string("Tracker : Bad command code."));
    return RETURN_VALUE_ERROR;
  }
}

int Tracker::ctConnMaster(Packet& packet, Client*& client)
{
  std::string login;
  std::string password;
  std::string privateIp;
  uint16_t bandwidth;
  int count = 0;

  COUTDEBUG(1);
  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> login;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> password;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> privateIp;
  client->setPrivateIp(privateIp);
  INCTEST(!packet.EndOfPacket(), count)
  packet >> bandwidth;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG(
      "Client --> Tracker : Connection master (" + login + ", "
      + password + ", " + privateIp + ")");
  if (count != 5)
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
          , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(2);
  std::string publicIp = client->getPublicIp();
  COUTDEBUG(3);
  std::string token = SqlManager::getInstance().addClient(login, password,
      privateIp, publicIp, bandwidth);
  COUTDEBUG(4);
  if (token == "")
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
              , std::string("Tracker : Empty token."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(5);
  client->setToken(token, 10); // TODO Level of privilege
  ClientList::getInstance().link(client, token);
  return tcToken(client, token);
}

int Tracker::ctConnSlave(Packet& packet, Client*& client)
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
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
            , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(6);
  SqlManager::getInstance().saveClientServerConnection(token
      , Config::getInstance().getInstance().getInt("server_id"));
  COUTDEBUG(7);
  client->setToken(token, 10); //TODO set privilege level
  ClientList::getInstance().link(client, token);
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskList(Packet& packet, Client*& client)
{
  uint8_t filter;
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
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(9);
  sql_result res = SqlManager::getInstance().getAllFlux();
  COUTDEBUG(10);

  return tcList(client, res);
}

int Tracker::ctAskFlux(Packet& packet, Client*& client)
{
  int videoId;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> videoId;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask flux");
  if (count != 2)
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  /*if (client == nullptr) TODO Check privilege level
  {
    Tracker::getInstance().tcMsg(sock, RETURN_VALUE_ERROR
                , std::string("Tracker : Unknown client."));
    return RETURN_VALUE_ERROR;
  }*/
  SqlManager::getInstance().removeClientServerConnection(client->getToken()
    , Config::getInstance().getInt("server_id")); 
  SqlManager::getInstance().setHandlings(client->getToken(), videoId);
  COUTDEBUG(14);
  client->unlock();
  sql_result res = SqlManager::getInstance().getThreeServers(); //TODO videoId
  COUTDEBUG(15);
  return tcListDiff(client, res);
}

int Tracker::ctAskCheck(Packet& packet, Client*& client)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask check");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskPacket(Packet& packet, Client*& client)
{
  int nbFrame;
  int* frameNumber;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> nbFrame;
  INCTEST(!packet.EndOfPacket(), count)
  frameNumber = new int[nbFrame];
  for (int i = 0; i < nbFrame; i++)
  {
    INCTEST(!packet.EndOfPacket(), count)
    packet >> frameNumber[i];
  }
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask packet");
  if (count != 3 + nbFrame)
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    delete frameNumber;
    return RETURN_VALUE_ERROR;
  }
  COUTDEBUG(17);
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskRpacket(Packet& packet, Client*& client)
{
  int firstFrame;
  int lastFrame;
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
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
                , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskMove(Packet& packet, Client*& client)
{
  int nPosition;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count);
  packet >> nPosition;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask move");
  if (count != 2)
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskDeficient(Packet& packet, Client*& client)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask deficient");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskRem(Packet& packet, Client*& client)
{
  int startFrame;
  int endFrame;
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
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctAskStop(Packet& packet, Client*& client)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ask stop");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  delete client->getTypeClient();//TODO Unsafe
  client->setTypeClient(nullptr);
  
  SqlManager::getInstance().deleteHandlings (client->getToken());
  return RETURN_VALUE_GOOD;
}

int Tracker::ctDec(Packet& packet, Client*& client)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Deconnection");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_GOOD;
}

int Tracker::ctPing(Packet& packet, Client*& client)
{
  int count = 0;

  // Extract content of packet
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Client --> Tracker : Ping");
  if (count != 1)
  {
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return tcPing(client);
}

int Tracker::ctUrl(Packet& packet, Client*& client)
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
    Tracker::getInstance().tcMsg(client, RETURN_VALUE_ERROR
        , std::string("Tracker : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  struct stat unused;
  url = "movie/" + tools::toString(videoId) + ".flv";
  if (stat(url.c_str(), &unused) == -1)
    url = url.substr(0, url.length() - 3) + "mp4";
  url = "/" + url;  //TODO Change method
  //TODO Get free server
  COUTDEBUG(20);
  ip = "37.59.85.217";
  return tcUrl(client, ip, url);
}

int Tracker::tcToken(Client*& sender, std::string token)
{
  Packet packet;
  uint16_t opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::TOKEN);

  // Create packet
  packet << opcode;
  packet << token;
  COUTDEBUG("Tracker --> Client : Token = " + token);
  return send(sender, packet);
}

int Tracker::tcList(Client*& sender, sql_result sqlResult)
{
  Packet packet;
  u_int16_t opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST);
  int length = 0;

  // Create packet
  packet << opcode;
  length = sqlResult.size();
  packet << length;
  for (unsigned int i = 0; i < sqlResult.size(); i++)
  {
    pqxx::result::tuple t = sqlResult.at(i);
    int id;
    packet << t["name"].c_str();
    id = atoi(t["id"].c_str());
    packet << id;
    packet << t["description"].c_str();
  }
  COUTDEBUG("Tracker --> Client : list");
  return send(sender, packet);
}

int Tracker::tcListDiff(Client*& sender, sql_result sqlResult)
{
  Packet packet;
  uint16_t opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_DIFF);
  uint8_t length;
  uint16_t port;

  // Create packet
  packet << opcode;
  length = sqlResult.size();
  packet << length;
  for (unsigned int i = 0; i < sqlResult.size(); i++)
  {
    pqxx::result::tuple t = sqlResult.at(i);
    packet << t["ip"].c_str();
    tools::fromString<uint16_t>(t["port"].c_str(), port);
    packet << port;
  }
  COUTDEBUG("Tracker --> Client : list diffusion");
  return send(sender, packet);
}

int Tracker::tcListNDiff(Client*& sender, sql_result sqlResult)
{
  Packet packet;
  uint16_t opcode =
      MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::LIST_NDIFF);
  uint8_t length;
  std::string temp;
  uint16_t port;

  // Create packet
  packet << opcode;
  length = sqlResult.size();
  packet << length;
  for (unsigned int i = 0; i < sqlResult.size(); i++)
  {
    pqxx::result::tuple t = sqlResult.at(i);
    packet << t["ip"].c_str();
    tools::fromString<uint16_t>(t["port"].c_str(), port);
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

int Tracker::tcMsg(Client*& sender, int numMsg, std::string msg)
{
  Packet packet;
  uint16_t opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::MSG);

  // Create packet
  packet << opcode;
  packet << numMsg;
  packet << msg;
  COUTDEBUG("Tracker --> Client : send msg : " << msg);
  return send(sender, packet);
}

int Tracker::tcPing(Client*& sender)
{
  Packet packet;
  uint16_t opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::PING);

  // Create packet
  packet << opcode;
  COUTDEBUG("Tracker --> Client : send ping");
  return send(sender, packet);
}

int Tracker::tcUrl(Client*& sender, std::string& ip, std::string& url)
{
  Packet packet;
  uint16_t opcode = MERGE_OPCODE(ConnexionType::TRACKER_CLIENT, TC::URL);

  // Create packet
  packet << opcode;
  packet << ip;
  packet << url;
  COUTDEBUG("Tracker --> Client : send url");
  return send(sender, packet);
}

int Tracker::send(Client*& sender, Packet& packet)
{
  return sender->send(packet);
}


