/*
 * PacketHandler.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef PACKETHANDLER_HH_
# define PACKETHANDLER_HH_

# include <core/network/Packet.hh>
# include <core/client/Client.hh>

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
	virtual int routing(unsigned int code, Packet& packet
	    , Client*& client) = 0;
	/*
   * Routing internal interface
   * @param code second part of opcode
   * @param packet received
   * @param sock socket that send this packet
   */
	virtual int routing_internal(unsigned int code, Packet& packet);
};

#endif /* PACKETHANDLER_HH_ */
