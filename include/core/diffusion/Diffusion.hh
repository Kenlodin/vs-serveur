/*
 * Diffusion.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef DIFFUSION_HH_
# define DIFFUSION_HH_

// Internal include
# include <core/PacketHandler.hh>
# include <core/fileManager/Chuck.hh>
# include <core/fwd.hh>
# include <core/log/Log.hh>
# include <core/tracker/Tracker.hh>

/**
 * Class which implement interface PacketHandler for the routing of packet
 */
class Diffusion: public PacketHandler
{
  private: // Private because of singleton
    /**
     *  Constructor
     */
    Diffusion();

    /**
     *  Destructor
     */
    virtual ~Diffusion();
  public:
    /*
     *  Get singleton instance
     *  @return singleton of Diffusion class
     */
    static Diffusion& getInstance();

    /**
     *  Route packet from client
     *  @param code second part of opcode
     *  @param packet packet received
     *  @param sock sock of this packet
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Route packet from diffusion server
     *  @param code second part of opcode
     *  @param packet packet received
     *  @param sock sock of this packet
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int routing_internal(unsigned int code, sf::Packet& packet,
        sf::SocketTCP& sock);
  private:
    /**
     *  typedef for function packet handler
     */
    typedef int (Diffusion::*handler)(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Constant array of fonction for routing
     */
    const handler route_[CD::LENGTH];

    /**
     *  Constant array of fonction for internal routing
     */
    const handler route_internal[DD::LENGTH];
  private:
    /**
     *  Send packet with sender socket
     *  @param sender socket where send packet
     *  @param packet packet to send
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int send(sf::SocketTCP& sender, sf::Packet& packet);

    /**
     *  Send message on error
     *  @param sender socket where send packet
     *  @param numMsh message code
     *  @param msg string message
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int dcMsg(sf::SocketTCP& sender, sf::Int32 numMsg, std::string msg);

    // Fonction handler //
    /**
     * Fonction which receive just token
     * @param packet packet received without opcode
     * @param sock sock which send it
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int cdToken(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Fonction which receive demand of video from diffusion server
     * @param packet packet received without opcode
     * @param sock sock which send it
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int ddVideoDemand(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Fonction which receive demand of ping from server
     * @param packet packet received without opcode
     * @param sock sock which send it
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int ddPingPong(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Fonction which link server for live
     * @param packet packet received without opcode
     * @param sock sock which send it
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int ddLiveLink(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Receive fragment of video live
     *  @param packet packet received without opcode
     *  @param sock sock which send it
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int ddLiveData(sf::Packet& packet, sf::SocketTCP& sock);

    /**
     *  Receive fragment of video data
     *  @param packet packet received without opcode
     *  @param sock sock which send it
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int ddVodData(sf::Packet& packet, sf::SocketTCP& sock);
  public:
    /**
     * Fonction which send data chuck for client
     * @param sender socket where send packet
     * @param number number of the chunk send
     * @param chuck chunk to send
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int dcData(sf::SocketTCP& sender, int number, Chunk* chuck);

    /**
     *  Fonction which send data headers for client
     *  @param sender socket where send packet
     *  @param number number of the chunk header send
     *  @param code code identifier of header
     *  @param headers content of avi header
     *  @return RETURN_VALUE_GOOD on success else RETURN_VALUE_ERROR
     */
    int dcData(sf::SocketTCP& sender, int number, int code, avifile::s_chunk* headers);
};

#endif /* DIFFUSION_HH_ */
