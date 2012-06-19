/*
 * Tracker.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef TRACKER_HH_
#define TRACKER_HH_

//Internal include
# include "../fwd.hh"
# include "../PacketHandler.hh"
# include "../SqlManager/SqlManager.hh"
# include "../Log/Log.hh"

/*
 * Class which represent the process of tracker
 */
class Tracker: public PacketHandler
{
  private: // Private because of singleton
    // Constructor
    Tracker();

    // Destructor
    virtual ~Tracker();
  public:
    // Get instance of tracker
    static Tracker& getInstance();

    // Routing handler for packet of tracker
    int routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock);
  private:
    // typedef of funtion handler
    typedef int (Tracker::*handler)(sf::Packet& packet, sf::SocketTCP& sock);

    // Array of function of routing
    const handler route_[CT::LENGTH];
  private:
    // Receiver handling //
    // Manage packet client->tracker : Connection master
    int ctConnMaster(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Connection slave
    int ctConnSlave(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Ask list
    int ctAskList(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Ask flux
    int ctAskFlux(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Ask Check
    int ctAskCheck(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Ask Packet
    int ctAskPacket(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Ask Range Packer
    int ctAskRpacket(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Ask Move
    int ctAskMove(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Ask deficient
    int ctAskDeficient(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Ask remove frame of video
    int ctAskRem(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Ask stop video
    int ctAskStop(sf::Packet& packet, sf::SocketTCP& sock);

    // Manage packet client->tracker : Deconnection
    int ctDec(sf::Packet& packet, sf::SocketTCP& sock);

    // Send ping respond
    int ctPing(sf::Packet& packet, sf::SocketTCP& sock);

    // Send url of video
    int ctUrl(sf::Packet& packet, sf::SocketTCP& sock);
  private:
    // Send a packet by sender
    int send(sf::SocketTCP& sender, sf::Packet& packet);
    // Sender handling //
    // Manage packet tracker->client : Token
    int tcToken(sf::SocketTCP& sender, std::string token);

    // Manage packet tracker->client : List
    int tcList(sf::SocketTCP& sender, sql_result sqlResult);

    // Manage packet tracker->client : list diffusion
    int tcListDiff(sf::SocketTCP& sender, sql_result sqlResult);

    // Manage packet tracker->client : list new diffusion
    int tcListNDiff(sf::SocketTCP& sender, sql_result sqlResult);

    // Manage packet tracker->client : message
    int tcMsg(sf::SocketTCP& sender, sf::Int32 numMsg, std::string msg);

    // Send ping respond
    int tcPing(sf::SocketTCP& sender);

    // Send url of video
    int tcUrl(sf::SocketTCP& sender, std::string& ip, std::string& url);
};

#endif /* TRACKER_HH_ */
