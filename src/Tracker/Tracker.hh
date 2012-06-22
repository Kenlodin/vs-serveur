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
    /**
     *  Constructor
     */
    Tracker();

    /**
     *  Destructor
     */
    virtual ~Tracker();
  public:
    /**
     *  Get instance of tracker
     *  @return instance of Tracker class
     */
    static Tracker& getInstance();

    /**
     *  Routing handler for packet of tracker
     *  @param code second part of opcode
     *  @param packet received
     *  @param sock that send this packet
     */
    int routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock);
  private:
    /**
     *  typedef of funtion handler
     */
    typedef int (Tracker::*handler)(sf::Packet& packet, sf::SocketTCP& sock);

    // Array of function of routing
    const handler route_[CT::LENGTH];
  private:
    // Receiver handling //
    /**
     *  Manage packet client->tracker : Connection master
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctConnMaster(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Connection slave
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctConnSlave(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Ask list
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskList(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Ask flux
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskFlux(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Ask Check
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskCheck(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Ask Packet
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskPacket(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Ask Range Packer
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskRpacket(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Ask Move
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskMove(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Ask deficient
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskDeficient(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Ask remove frame of video
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskRem(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Ask stop video
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskStop(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Manage packet client->tracker : Deconnection
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctDec(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Send ping respond
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctPing(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Send url of video
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctUrl(sf::Packet& packet, sf::SocketTCP& sock);
  private:
    /**
     *  Send a packet by sender
     *  @param sender socket where send this packet
     *  @param packet to send
     *  @return RETURN_VALUE_GOOD on success
     */
    int send(sf::SocketTCP& sender, sf::Packet& packet);
    // Sender handling //
    /**
     *  Manage packet tracker->client : Token
     *  @param sender socket where send this packet
     *  @param token of new client
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcToken(sf::SocketTCP& sender, std::string token);

    /**
     *  Manage packet tracker->client : List
     *  @param sender socket where send this packet
     *  @param sqlResult sqlMap that contain list of file
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcList(sf::SocketTCP& sender, sql_result sqlResult);

    /**
     *  Manage packet tracker->client : list diffusion
     *  @param sender socket where send this packet
     *  @param sqlResult that contain list of server
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcListDiff(sf::SocketTCP& sender, sql_result sqlResult);

    /**
     *  Manage packet tracker->client : list new diffusion
     *  @param sender socket where send this packet
     *  @param sqlResult that contain list of server
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcListNDiff(sf::SocketTCP& sender, sql_result sqlResult);

    /**
     *  Manage packet tracker->client : message
     *  @param sender socket where send this packet
     *  @param numMsg message code
     *  @param msg text message
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcMsg(sf::SocketTCP& sender, sf::Int32 numMsg, std::string msg);

    /**
     *  Send ping respond
     *  @param sender socket where send this packet
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcPing(sf::SocketTCP& sender);

    /**
     *  Send url of video
     *  @param sender socket where send this packet
     *  @param ip of server
     *  @param url of video
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcUrl(sf::SocketTCP& sender, std::string& ip, std::string& url);
};

#endif /* TRACKER_HH_ */
