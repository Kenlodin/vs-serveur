/*
 * Tracker.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef TRACKER_HH_
#define TRACKER_HH_

# include "../fwd.hh"
# include "../PacketHandler.hh"

class Tracker : public PacketHandler {
public:
	Tracker();
	virtual ~Tracker();
	int routing(unsigned int code, sf::Packet* packet);
private:
	typedef int (Tracker::*handler)(sf::Packet* packet);
	const handler route_[CT::LENGTH];
private:
	int ctConnMaster (sf::Packet* packet);
	int ctConnSlave (sf::Packet* packet);
	int ctAskList (sf::Packet* packet);
	int ctAskFlux (sf::Packet* packet);
	int ctAskCheck (sf::Packet* packet);
	int ctAskPacket (sf::Packet* packet);
	int ctAskRpacket (sf::Packet* packet);
	int ctAskMove (sf::Packet* packet);
	int ctAskDeficient (sf::Packet* packet);
	int ctAskRem (sf::Packet* packet);
	int ctAskStop (sf::Packet* packet);
	int ctDec (sf::Packet* packet);
};

#endif /* TRACKER_HH_ */
