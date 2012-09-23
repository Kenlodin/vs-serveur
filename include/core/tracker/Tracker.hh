/*
 * Tracker.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef TRACKER_HH_
#define TRACKER_HH_

//Internal include
# include <core/fwd.hh>
# include <core/PacketHandler.hh>
# include <core/sqlManager/SqlManager.hh>
# include <core/log/Log.hh>

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
    int routing(unsigned int code, Packet& packet, Client*& client);
  private:
    /**
     *  typedef of funtion handler
     */
    typedef int (Tracker::*handler)(Packet& packet, Client*& client);

    // Array of function of routing
    const handler route_[CT::LENGTH];
  // TODO Check if this part can be public
  public:
    // Receiver handling //
    /**
     *  Manage packet client->tracker : Connection master
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctConnMaster(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Connection slave
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctConnSlave(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Ask list
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskList(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Ask flux
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskFlux(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Ask Check
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskCheck(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Ask Packet
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskPacket(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Ask Range Packer
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskRpacket(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Ask Move
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskMove(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Ask deficient
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskDeficient(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Ask remove frame of video
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskRem(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Ask stop video
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctAskStop(Packet& packet, Client*& client);

    /**
     *  Manage packet client->tracker : Deconnection
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctDec(Packet& packet, Client*& client);

    /**
     *  Send ping respond
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctPing(Packet& packet, Client*& client);

    /**
     *  Send url of video
     *  @param packet received
     *  @param sock that send this message
     *  @return RETURN_VALUE_GOOD on success
     */
    int ctUrl(Packet& packet, Client*& client);
  // TODO Check if this part can be public
  public:
    /**
     *  Send a packet by sender
     *  @param sender socket where send this packet
     *  @param packet to send
     *  @return RETURN_VALUE_GOOD on success
     */
    int send(Client*& sender, Packet& packet);
    // Sender handling //
    /**
     *  Manage packet tracker->client : Token
     *  @param sender socket where send this packet
     *  @param token of new client
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcToken(Client*& sender, std::string token);

    /**
     *  Manage packet tracker->client : List
     *  @param sender socket where send this packet
     *  @param sqlResult sqlMap that contain list of file
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcList(Client*& sender, sql_result sqlResult);

    /**
     *  Manage packet tracker->client : list diffusion
     *  @param sender socket where send this packet
     *  @param sqlResult that contain list of server
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcListDiff(Client*& sender, sql_result sqlResult);

    /**
     *  Manage packet tracker->client : list new diffusion
     *  @param sender socket where send this packet
     *  @param sqlResult that contain list of server
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcListNDiff(Client*& sender, sql_result sqlResult);

    /**
     *  Manage packet tracker->client : message
     *  @param sender socket where send this packet
     *  @param numMsg message code
     *  @param msg text message
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcMsg(Client*& sender, int numMsg, std::string msg);

    /**
     *  Send ping respond
     *  @param sender socket where send this packet
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcPing(Client*& sender);

    /**
     *  Send url of video
     *  @param sender socket where send this packet
     *  @param ip of server
     *  @param url of video
     *  @return RETURN_VALUE_GOOD on success
     */
    int tcUrl(Client*& sender, std::string& ip, std::string& url);
};

#endif /* TRACKER_HH_ */
