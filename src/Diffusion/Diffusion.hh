/*
 * Diffusion.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef DIFFUSION_HH_
#define DIFFUSION_HH_

# include "../PacketHandler.hh"

class Diffusion : public PacketHandler {
public:
	Diffusion();
	virtual ~Diffusion();
	int routing(unsigned int code, sf::Packet* packet);
};

#endif /* DIFFUSION_HH_ */
