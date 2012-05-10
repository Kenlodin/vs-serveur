/*
 * Diffusion.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef DIFFUSION_HH_
# define DIFFUSION_HH_

// Internal include
# include "../PacketHandler.hh"
# include "../FileManager/Chuck.hh"
# include "../fwd.hh"
# include "../Log/Log.hh"

/*
 * Class which implement interface PacketHandler for the routing of packet
 */
class Diffusion: public PacketHandler
{
  private: // Private because of singleton
    // Constructor
    Diffusion();

    // Destructor
    virtual ~Diffusion();
  public:
    // Get singleton instance
    static Diffusion& getInstance();

    // Route packet from client
    int routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock);

    // Route packet from diffusion server
    int routing_internal(unsigned int code, sf::Packet& packet,
        sf::SocketTCP& sock);
  private:
    // typedef for function packet handler
    typedef int (Diffusion::*handler)(sf::Packet& packet, sf::SocketTCP& sock);

    // Constant array of fonction for routing
    const handler route_[CD::LENGTH];

    // Constant array of fonction for internal routing
    const handler route_internal[DD::LENGTH];
  private:
    // Send packet with sender socket
    int send(sf::SocketTCP& sender, sf::Packet& packet);

    // Fonction handler //
    //Fonction which receive just token
    int cdToken(sf::Packet& packet, sf::SocketTCP& sock);

    // Fonction which receive demand of video from diffusion server
    int ddVideoDemand(sf::Packet& packet, sf::SocketTCP& sock);

    // Fonction which receive demand of ping from server
    int ddPingPong(sf::Packet& packet, sf::SocketTCP& sock);

    // Fonction which link server for live
    int ddLiveLink(sf::Packet& packet, sf::SocketTCP& sock);

    // Receive fragment of video live
    int ddLiveData(sf::Packet& packet, sf::SocketTCP& sock);

    // Receive fragment of video data
    int ddVodData(sf::Packet& packet, sf::SocketTCP& sock);
  public:
    // Fonction which send data chuck for client
    int dcData(sf::SocketTCP& sender, int number, Chunk* chuck);

    // Fonction which send data headers for client
    int dcData(sf::SocketTCP& sender, int code, avifile::s_chunk* headers);
};

#endif /* DIFFUSION_HH_ */
