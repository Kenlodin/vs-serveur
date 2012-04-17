/*
 * Diffusion.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef DIFFUSION_HH_
#define DIFFUSION_HH_

# include "../PacketHandler.hh"
# include "../fwd.hh"

class Diffusion : public PacketHandler {
public:
	Diffusion();
	virtual ~Diffusion();
	int routing(unsigned int code, sf::Packet* packet);
	int routing_internal(unsigned int code, sf::Packet* packet);
private:
	typedef int (Diffusion::*handler)(sf::Packet* packet);
	const handler route_[CD::LENGTH];
	const handler route_internal[DD::LENGTH];
private:
	int ddVideoDemand(sf::Packet* packet);
	int ddPingPong(sf::Packet* packet);
};

#endif /* DIFFUSION_HH_ */
