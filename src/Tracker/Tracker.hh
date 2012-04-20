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

class Tracker: public PacketHandler
{
  private:
    Tracker();
    virtual ~Tracker();
  public:
    static Tracker& getInstance();
    int routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock);
  private:
    typedef int (Tracker::*handler)(sf::Packet& packet, sf::SocketTCP& sock);
    const handler route_[CT::LENGTH];
  private:
    // Receiver handling
    int ctConnMaster(sf::Packet& packet, sf::SocketTCP& sock);
    int ctConnSlave(sf::Packet& packet, sf::SocketTCP& sock);
    int ctAskList(sf::Packet& packet, sf::SocketTCP& sock);
    int ctAskFlux(sf::Packet& packet, sf::SocketTCP& sock);
    int ctAskCheck(sf::Packet& packet, sf::SocketTCP& sock);
    int ctAskPacket(sf::Packet& packet, sf::SocketTCP& sock);
    int ctAskRpacket(sf::Packet& packet, sf::SocketTCP& sock);
    int ctAskMove(sf::Packet& packet, sf::SocketTCP& sock);
    int ctAskDeficient(sf::Packet& packet, sf::SocketTCP& sock);
    int ctAskRem(sf::Packet& packet, sf::SocketTCP& sock);
    int ctAskStop(sf::Packet& packet, sf::SocketTCP& sock);
    int ctDec(sf::Packet& packet, sf::SocketTCP& sock);
  private:
    int send(sf::SocketTCP& sender, sf::Packet& packet);
    // Sender handling
    int tcToken(sf::SocketTCP& sender, std::string token);
    int tcList(sf::SocketTCP& sender, std::string name[], sf::Int32 id[],
        sf::Int32 number);
    int tcListDiff(sf::SocketTCP& sender, std::string ip[], sf::Int16 port[],
        sf::Int8 number);
    int tcListDiff(sf::SocketTCP& sender, std::string ip1, sf::Int16 port1,
        std::string ip2, sf::Int16 port2, std::string ip3, sf::Int16 port3);
    int tcListNDiff(sf::SocketTCP& sender, std::string ip[], sf::Int16 port[],
        sf::Int8 number);
    int tcListNDiff(sf::SocketTCP& sender, std::string ip, sf::Int16 port);
    int tcListNDiff(sf::SocketTCP& sender, std::string ip1, sf::Int16 port1,
        std::string ip2, sf::Int16 port2);
    int tcListNDiff(sf::SocketTCP& sender, std::string ip1, sf::Int16 port1,
        std::string ip2, sf::Int16 port2, std::string ip3, sf::Int16 port3);
    int tcMsg(sf::SocketTCP& sender, sf::Int32 numMsg, std::string msg);
};

#endif /* TRACKER_HH_ */
