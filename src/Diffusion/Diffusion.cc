/*
 * Diffusion.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "Diffusion.hh"
#include "../Network/ClientList.hh"

Diffusion::Diffusion()
    : route_(
    { &Diffusion::cdToken })

    , route_internal(
    { &Diffusion::ddVideoDemand, &Diffusion::ddPingPong })
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
  coutDebug(code);
  if (RETURN_VALUE_GOOD) //code < CD::LENGTH)
    (this->*route_[code])(packet, sock);
  else
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Diffusion::routing_internal(unsigned int code, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  coutDebug(code);
  if (code < DD::LENGTH)
    (this->*route_[code])(packet, sock);
  else
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Diffusion::ddVideoDemand(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 videoId;
  sf::Int32 serverId;

  // Extract content of packet
  packet >> videoId;
  packet >> serverId;
  coutDebug("Diffusion --> Diffusion : Video Demand");
  return RETURN_VALUE_GOOD;
}

int Diffusion::ddPingPong(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string message;

  // Extract content of packet
  packet >> message;
  coutDebug("Diffusion --> Diffusion : Ping Pong");
  return RETURN_VALUE_GOOD;
}

int Diffusion::cdToken(sf::Packet& packet, sf::SocketTCP& sock)
{
  std::string token;

  // Extract content of packet
  packet >> token;
  sf::SocketTCP* newSocket = new sf::SocketTCP(sock);
  if (ClientList::getInstance().link(newSocket, token) == RETURN_VALUE_ERROR)
  {
    delete newSocket;
    return RETURN_VALUE_ERROR;
  }
  coutDebug("Diffusion --> Diffusion : Token");
  return RETURN_VALUE_SUPPRESS;
}

int Diffusion::ddLiveLink(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int32 videoId;
  sf::Int32 serverId;

  // Extract content of packet
  packet >> videoId;
  packet >> serverId;
  coutDebug("Diffusion --> Diffusion : Live Link");
  return RETURN_VALUE_GOOD;
}

Diffusion& Diffusion::getInstance()
{
  static Diffusion instance_;

  return instance_;
}

int Diffusion::dcData(sf::SocketTCP& sender, sf::Int8 data[], int length)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::DIFFUSION_CLIENT, DC::DATA);

  packet << opcode;
  for (int i = 0; i < length; i++)
  {
    packet << data[i];
  }
  coutDebug("Diffusion --> Client : Data");
  return RETURN_VALUE_GOOD;
}

int Diffusion::send(sf::SocketTCP& sender, sf::Packet& packet)
{
  if (sender.Send(packet) == sf::Socket::Done)
    return RETURN_VALUE_GOOD;
  return RETURN_VALUE_ERROR;
}
