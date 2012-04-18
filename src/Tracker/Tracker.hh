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
private: // Receiver handling
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
private: // Sender handling
	int tcToken (std::string token);
	int tcList (std::string name[], sf::Int32 id[], sf::Int32 number);
	int tcListDiff (std::string ip[], sf::Int16 port[], sf::Int8 number);
	int tcListDiff (std::string ip1, sf::Int16 port1
	          , std::string ip2, sf::Int16 port2
	          , std::string ip3, sf::Int16 port3);
	int tcListNDiff (std::string ip[], sf::Int16 port[], sf::Int8 number);
	int tcListNDiff (std::string ip, sf::Int16 port);
	int tcListNDiff (std::string ip1, sf::Int16 port1
	              , std::string ip2, sf::Int16 port2);
  int tcListNDiff (std::string ip1, sf::Int16 port1
                , std::string ip2, sf::Int16 port2
                , std::string ip3, sf::Int16 port3);
	int tcMsg (sf::Int32 numMsg, std::string msg);
};

#endif /* TRACKER_HH_ */
