/*
 * Diffusion.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

// Internal include
#include "Diffusion.hh"
#include "../Network/ClientList.hh"
#include "../FileManager/LiveHandler.hh"

Diffusion::Diffusion()
    : route_(
    { &Diffusion::cdToken })

    , route_internal(
    { &Diffusion::ddVideoDemand, &Diffusion::ddPingPong, &Diffusion::ddLiveLink
      , &Diffusion::ddLiveData, &Diffusion::ddVodData})
{
  // TODO Auto-generated constructor stub
}

Diffusion::~Diffusion()
{
  // TODO Auto-generated destructor stub
}

int Diffusion::routing(unsigned int code, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  int retVal = RETURN_VALUE_ERROR;
  COUTDEBUG(code);
  if (code < CD::LENGTH)
  {
      if ((retVal = (this->*route_[code])(packet, sock)) == RETURN_VALUE_ERROR)
      {
        COUTDEBUG("Diffusion : mauvais processing.");
        ClientList::getInstance().addBadClient(sock, retVal);
        return retVal;
      }
    return RETURN_VALUE_GOOD;
  }
  else
  {
    COUTDEBUG("Diffusion : mauvais routing.");
    ClientList::getInstance().addBadClient(sock, retVal);
    dcMsg(sock, retVal
              , std::string("Diffusion : Bad command code."));
    return RETURN_VALUE_ERROR;
  }
}

int Diffusion::routing_internal(unsigned int code, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  int retVal = RETURN_VALUE_ERROR;
  COUTDEBUG(code);
  if (code < DD::LENGTH)
  {
      if ((retVal = (this->*route_[code])(packet, sock)) == RETURN_VALUE_ERROR)
      {
        COUTDEBUG("Diffusion : mauvais processing interne.");
        ClientList::getInstance().addBadClient(sock, retVal);
        return retVal;
      }
    return RETURN_VALUE_GOOD;
  }
  else
  {
    COUTDEBUG("Diffusion : mauvais routing interne.");
    ClientList::getInstance().addBadClient(sock, retVal);
    dcMsg(sock, retVal
          , std::string("Diffusion : Bad command code."));
    return RETURN_VALUE_ERROR;
  }
}

int Diffusion::ddVideoDemand(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 videoId;
  sf::Int32 serverId;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> videoId;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> serverId;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Diffusion --> Diffusion : Video Demand");
  if (count != 3)
  {
    dcMsg(sock, RETURN_VALUE_ERROR
              , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_SUPPRESS;
}

int Diffusion::ddPingPong(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string message;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> message;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Diffusion --> Diffusion : Ping Pong");
  if (count != 2)
  {
    dcMsg(sock, RETURN_VALUE_ERROR
      , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_SUPPRESS;
}

int Diffusion::cdToken(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> token;
  INCTEST(packet.EndOfPacket(), count)
  sf::SocketTCP* newSocket = new sf::SocketTCP(sock);
  COUTDEBUG("Diffusion --> Diffusion : Token : " << token);
  if (ClientList::getInstance().link(newSocket, token) == RETURN_VALUE_ERROR)
  {
    delete newSocket;
    dcMsg(sock, RETURN_VALUE_ERROR
        , std::string("Diffusion : Unknown client for connection to diffusion"));
  }
  if (count != 2)
  {
    delete newSocket;
    dcMsg(sock, RETURN_VALUE_ERROR
          , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_SUPPRESS;
}

int Diffusion::ddLiveLink(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 videoId;
  sf::Int32 serverId;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> videoId;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> serverId;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Diffusion --> Diffusion : Live Link");
  if (count != 3)
  {
    dcMsg(sock, RETURN_VALUE_ERROR
          , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  LiveHandler::getInstance().getLive(videoId)->addServer(sock);
  return RETURN_VALUE_SUPPRESS;
}

Diffusion& Diffusion::getInstance()
{
  static Diffusion instance_;

  return instance_;
}

int Diffusion::dcData(sf::SocketTCP& sender, int number, Chunk* chuck)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::DIFFUSION_CLIENT, DC::DATA);
  sf::Uint32 type = avifile::e_opcode::AVI_CHUNK;

  packet << opcode;
  packet << type;
  packet << number;
  packet.Append(chuck->subChunk_, 8);
  packet.Append(chuck->subChunk_->data, chuck->subChunk_->size);
  COUTDEBUG("Diffusion --> Client : Data");
  return send(sender, packet);
}

int Diffusion::dcMsg(sf::SocketTCP& sender, sf::Int32 numMsg, std::string msg)
{
  sf::Packet packet;
  sf::Uint16 opcode = MERGE_OPCODE(ConnexionType::DIFFUSION_CLIENT, DC::MSG);

  // Create packet
  packet << opcode;
  packet << numMsg;
  packet << msg;
  COUTDEBUG("Diffusion --> Client : send msg : " << msg);
  return send(sender, packet);
}

int Diffusion::ddLiveData(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 videoId;
  sf::Int32 number;
  Chunk* data = new Chunk();
  int count = 0;

  INCTEST(!packet.EndOfPacket(), count)
  packet >> videoId;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> number;
  INCTEST(!packet.EndOfPacket(), count)
  data->subChunk_ = reinterpret_cast<avifile::s_sub_chunk*>(malloc(8));
  INCTEST(packet.GetDataSize() > 8, count)
  memcpy(data->subChunk_, packet.GetData(), 8);
  data->subChunk_->data = malloc(data->subChunk_->size);
  INCTEST(packet.GetDataSize() == data->subChunk_->size + 8, count)
  memcpy(data->subChunk_->data, packet.GetData() + 8, data->subChunk_->size);
  if (count != 5)
  {
    dcMsg(sock, RETURN_VALUE_ERROR
          , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  LiveHandler::getInstance().getLive(videoId)->addPacket(number, data);
  return RETURN_VALUE_GOOD;
}

int Diffusion::ddVodData(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 videoId;
    sf::Int32 number;
    Chunk* data = new Chunk();
    int count = 0;

    INCTEST(!packet.EndOfPacket(), count)
    packet >> videoId;
    INCTEST(!packet.EndOfPacket(), count)
    packet >> number;
    INCTEST(!packet.EndOfPacket(), count)
    data->subChunk_ = reinterpret_cast<avifile::s_sub_chunk*>(malloc(8));
    INCTEST(packet.GetDataSize() > 8, count)
    memcpy(data->subChunk_, packet.GetData(), 8);
    data->subChunk_->data = malloc(data->subChunk_->size);
    INCTEST(packet.GetDataSize() == data->subChunk_->size + 8, count)
    memcpy(data->subChunk_->data, packet.GetData() + 8, data->subChunk_->size);
    if (count != 5)
    {
      dcMsg(sock, RETURN_VALUE_ERROR
            , std::string("Diffusion : Bad number of attributes."));
      return RETURN_VALUE_ERROR;
    }
    //VodHandler::getInstance().getVod(videoId)->addPacket(number, data);
    // TODO
    return RETURN_VALUE_GOOD;
}

int Diffusion::dcData(sf::SocketTCP& sender, int code,
    avifile::s_chunk* headers)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::DIFFUSION_CLIENT, DC::DATA);
  sf::Uint8 type = code;

  packet << opcode;
  packet << type;
  packet.Append(headers, 12);
  if (headers->data)
    packet.Append(headers->data, headers->size - sizeof(avifile::u32));
  COUTDEBUG("Diffusion --> Client : Data");
  return send(sender, packet);
}

int Diffusion::send(sf::SocketTCP& sender, sf::Packet& packet)
{
  if (sender.Send(packet) == sf::Socket::Done)
    return RETURN_VALUE_GOOD;
  return RETURN_VALUE_ERROR;
}
