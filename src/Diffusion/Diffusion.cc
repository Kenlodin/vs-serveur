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

int Diffusion::routing(unsigned int code, sf::Packet* packet)
{
	if (FALSE)//code < CD::LENGTH)
		(this->*route_[code]) (packet);
	else
		return TRUE;
	return FALSE;
}

int Diffusion::routing_internal(unsigned int code, sf::Packet* packet)
{
	if (code < DD::LENGTH)
		(this->*route_[code]) (packet);
	else
		return TRUE;
	return FALSE;
}

int Diffusion::ddVideoDemand(sf::Packet* packet) {
	sf::Int32 videoId;
	sf::Int32 serverId;

	// Extract content of packet
	packet >> videoId;
	packet >> serverId;
	return FALSE;
}


int Diffusion::ddPingPong(sf::Packet* packet) {
	std::string message;

	// Extract content of packet
	packet >> message;
	return FALSE;
}



