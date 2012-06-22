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
    /*
     * Constructor
     */
	virtual ~PacketHandler();
public:
	/*
	 * Routing interface
	 * @param code second part of opcode
	 * @param packet received
	 * @param sock socket that send this packet
	 */
	virtual int routing(unsigned int code, sf::Packet& packet
	    , sf::SocketTCP& sock) = 0;
	/*
   * Routing internal interface
   * @param code second part of opcode
   * @param packet received
   * @param sock socket that send this packet
   */
	virtual int routing_internal(unsigned int code, sf::Packet* packet);
};

#endif /* PACKETHANDLER_HH_ */
