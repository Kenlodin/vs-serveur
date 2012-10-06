/*
 * Diffusion.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

// Internal include
#include <core/diffusion/Diffusion.hh>
#include <core/network/ClientList.hh>
#include <core/fileManager/LiveHandler.hh>

Diffusion::Diffusion()
    : route_(
    { &Diffusion::cdToken })

    , route_internal(
    { &Diffusion::ddVideoDemand, &Diffusion::ddPingPong, &Diffusion::ddLiveLink
      , &Diffusion::ddLiveData, &Diffusion::ddVodData})
{
}

Diffusion::~Diffusion()
{
}

int Diffusion::routing(unsigned int code, Packet& packet,
    Client*& client)
{
  int retVal = RETURN_VALUE_ERROR;
  COUTDEBUG(code);
  if (code < CD::LENGTH)
  {
      if ((retVal = (this->*route_[code])(packet, client)) != RETURN_VALUE_ERROR)
      {
        if (retVal == RETURN_VALUE_ERROR)
          COUTDEBUG("Diffusion : mauvais processing.");
        ClientList::getInstance().addBadClient(client, retVal);
        return retVal;
      }
    return RETURN_VALUE_GOOD;
  }
  else
  {
    COUTDEBUG("Diffusion : mauvais routing.");
    ClientList::getInstance().addBadClient(client, retVal);
    dcMsg(client, retVal
              , std::string("Diffusion : Bad command code."));
    return RETURN_VALUE_ERROR;
  }
}

int Diffusion::routing_internal(unsigned int code, Packet& packet,
    Client*& client)
{
  int retVal = RETURN_VALUE_ERROR;
  COUTDEBUG(code);
  if (code < DD::LENGTH)
  {
      if ((retVal = (this->*route_[code])(packet, client)) == RETURN_VALUE_ERROR)
      {
        COUTDEBUG("Diffusion : mauvais processing interne.");
        ClientList::getInstance().addBadClient(client, retVal);
        return retVal;
      }
    return RETURN_VALUE_GOOD;
  }
  else
  {
    COUTDEBUG("Diffusion : mauvais routing interne.");
    ClientList::getInstance().addBadClient(client, retVal);
    dcMsg(client, retVal
          , std::string("Diffusion : Bad command code."));
    return RETURN_VALUE_ERROR;
  }
}

int Diffusion::ddVideoDemand(Packet& packet, Client*& client)
{
  int videoId;
  int serverId;
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
    dcMsg(client, RETURN_VALUE_ERROR
              , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_SUPPRESS;
}

int Diffusion::ddPingPong(Packet& packet, Client*& client)
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
    dcMsg(client, RETURN_VALUE_ERROR
      , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_SUPPRESS;
}

int Diffusion::cdToken(Packet& packet, Client*& client)
{
  std::string token;
  int count = 0;

  // Extract content of packet
  INCTEST(!packet.EndOfPacket(), count)
  packet >> token;
  INCTEST(packet.EndOfPacket(), count)
  COUTDEBUG("Diffusion --> Diffusion : Token : " << token);
  if (count != 2)
  {
    dcMsg(client, RETURN_VALUE_ERROR
          , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  return RETURN_VALUE_SUPPRESS;
}

int Diffusion::ddLiveLink(Packet& packet, Client*& client)
{
  int videoId;
  int serverId;
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
    dcMsg(client, RETURN_VALUE_ERROR
          , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  //LiveHandler::getInstance().getLive(videoId)->addServer(client->getSockets().front()); TODO
  return RETURN_VALUE_SUPPRESS;
}

Diffusion& Diffusion::getInstance()
{
  static Diffusion instance_;

  return instance_;
}

int Diffusion::dcData(Client*& sender, int number, Chunk* chuck)
{
  Packet packet;
  int16_t opcode = MERGE_OPCODE(ConnexionType::DIFFUSION_CLIENT, DC::DATA);
  int type = avifile::e_opcode::AVI_CHUNK;

  packet << opcode;
  packet << type;
  packet << number;
  //packet.Append(chuck->subChunk_, sizeof(avifile::s_sub_chunk) - sizeof(void*));
  //if (chuck->subChunk_->data)
  //  packet.Append(chuck->subChunk_->data, MOD2(chuck->subChunk_->size));
  //COUTDEBUG("Diffusion --> Client : Data");
  return send(sender, packet);
}

int Diffusion::dcMsg(Client*& sender, int numMsg, std::string msg)
{
  Packet packet;
  uint16_t opcode = MERGE_OPCODE(ConnexionType::DIFFUSION_CLIENT, DC::MSG);

  // Create packet
  packet << opcode;
  packet << numMsg;
  packet << msg;
  COUTDEBUG("Diffusion --> Client : send msg : " << msg);
  return send(sender, packet);
}

int Diffusion::ddLiveData(Packet& packet, Client*& client)
{
  int videoId;
  int number;
  Chunk* data = new Chunk();
  int count = 0;

  INCTEST(!packet.EndOfPacket(), count)
  packet >> videoId;
  INCTEST(!packet.EndOfPacket(), count)
  packet >> number;
  INCTEST(!packet.EndOfPacket(), count)
  data->subChunk_ = reinterpret_cast<avifile::s_sub_chunk*>(malloc(8));
  INCTEST(packet.GetDataSize() > 8, count)
  //memcpy(data->subChunk_, packet.GetData(), 8);
  data->subChunk_->data = malloc(data->subChunk_->size);
  INCTEST(packet.GetDataSize() == data->subChunk_->size + 8, count)
  //memcpy(data->subChunk_->data, packet.GetData() + 8, data->subChunk_->size);
  if (count != 5)
  {
    dcMsg(client, RETURN_VALUE_ERROR
          , std::string("Diffusion : Bad number of attributes."));
    return RETURN_VALUE_ERROR;
  }
  //LiveHandler::getInstance().getLive(videoId)->setElement(number, data);
  return RETURN_VALUE_GOOD;
}

int Diffusion::ddVodData(Packet& packet, Client*& client)
{
  int videoId;
    int number;
    Chunk* data = new Chunk();
    int count = 0;

    INCTEST(!packet.EndOfPacket(), count)
    packet >> videoId;
    INCTEST(!packet.EndOfPacket(), count)
    packet >> number;
    INCTEST(!packet.EndOfPacket(), count)
    data->subChunk_ = reinterpret_cast<avifile::s_sub_chunk*>(malloc(8));
    INCTEST(packet.GetDataSize() > 8, count)
    //memcpy(data->subChunk_, packet.GetData(), 8);
    data->subChunk_->data = malloc(data->subChunk_->size);
    INCTEST(packet.GetDataSize() == data->subChunk_->size + 8, count)
    //memcpy(data->subChunk_->data, packet.GetData() + 8, data->subChunk_->size);
    if (count != 5)
    {
      dcMsg(client, RETURN_VALUE_ERROR
            , std::string("Diffusion : Bad number of attributes."));
      return RETURN_VALUE_ERROR;
    }
    //VodHandler::getInstance().getVod(videoId)->setElement(number, data);
    // TODO Reception of data
    return RETURN_VALUE_GOOD;
}

int Diffusion::dcData(Client*& sender,int number, int code,
    avifile::s_chunk* headers)
{
  Packet packet;
  int16_t opcode = MERGE_OPCODE(ConnexionType::DIFFUSION_CLIENT, DC::DATA);
  int type = code;

  packet << opcode;
  packet << type;
  packet << number;
  //packet.Append(headers, SIZE_CHUNK_HEADER);
  //if (headers->data)
  //  packet.Append(headers->data, headers->size - sizeof(avifile::u32));
  COUTDEBUG("Diffusion --> Client : Data");
  return send(sender, packet);
}

int Diffusion::send(Client*& sender, Packet& packet)
{
  //TODO FIXME
  return RETURN_VALUE_ERROR;
}
