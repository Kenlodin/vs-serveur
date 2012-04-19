/*
 * Diffusion.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "Diffusion.hh"

Diffusion::Diffusion()
 : route_ ()
 , route_internal ({
	&Diffusion::ddVideoDemand,
	&Diffusion::ddPingPong
})
{
	// TODO Auto-generated constructor stub
}

Diffusion::~Diffusion() {
	// TODO Auto-generated destructor stub
}

int Diffusion::routing(unsigned int code, sf::Packet& packet
    , sf::SocketTCP& sock)
{
	if (RETURN_VALUE_GOOD)//code < CD::LENGTH)
		(this->*route_[code]) (packet, sock);
	else
		return RETURN_VALUE_ERROR;
	return RETURN_VALUE_GOOD;
}

int Diffusion::routing_internal(unsigned int code, sf::Packet& packet
    , sf::SocketTCP& sock)
{
	if (code < DD::LENGTH)
		(this->*route_[code]) (packet, sock);
	else
		return RETURN_VALUE_ERROR;
	return RETURN_VALUE_GOOD;
}

int Diffusion::ddVideoDemand(sf::Packet& packet, sf::SocketTCP& sock) {
	sf::Int32 videoId;
	sf::Int32 serverId;

	// Extract content of packet
	packet >> videoId;
	packet >> serverId;
	return RETURN_VALUE_GOOD;
}


int Diffusion::ddPingPong(sf::Packet& packet, sf::SocketTCP& sock) {
	std::string message;

	// Extract content of packet
	packet >> message;
	return RETURN_VALUE_GOOD;
}

int Diffusion::dcData(sf::Int8 data[], int length)
{
  sf::Packet packet;
  sf::Int16 opcode = MERGE_OPCODE(ConnexionType::DIFFUSION_CLIENT, DC::DATA);

  packet << opcode;
  for (int i = 0; i < length; i++)
  {
    packet << data[i];
  }
  return RETURN_VALUE_GOOD;
}




