/*
 * PacketHandler.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef PACKETHANDLER_HH_
# define PACKETHANDLER_HH_

# include <SFML/Network.hpp>

class PacketHandler {
public:
	virtual ~PacketHandler();
public:
	virtual int routing(unsigned int code, sf::Packet& packet
	    , sf::SocketTCP& sock) = 0;
	virtual int routing_internal(unsigned int code, sf::Packet* packet) = 0;
};

#endif /* PACKETHANDLER_HH_ */
