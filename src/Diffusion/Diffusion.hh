/*
 * Diffusion.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef DIFFUSION_HH_
#define DIFFUSION_HH_

# include "../PacketHandler.hh"
# include "../FileManager/Chuck.hh"
# include "../fwd.hh"
# include "../Log/Log.hh"

class Diffusion: public PacketHandler
{
  private:
    Diffusion();
    virtual ~Diffusion();
  public:
    static Diffusion& getInstance();
    int routing(unsigned int code, sf::Packet& packet, sf::SocketTCP& sock);
    int routing_internal(unsigned int code, sf::Packet& packet,
        sf::SocketTCP& sock);
  private:
    typedef int (Diffusion::*handler)(sf::Packet& packet, sf::SocketTCP& sock);
    const handler route_[CD::LENGTH];
    const handler route_internal[DD::LENGTH];
  private:
    int send(sf::SocketTCP& sender, sf::Packet& packet);
    int cdToken(sf::Packet& packet, sf::SocketTCP& sock);
    int ddVideoDemand(sf::Packet& packet, sf::SocketTCP& sock);
    int ddPingPong(sf::Packet& packet, sf::SocketTCP& sock);
    int ddLiveLink(sf::Packet& packet, sf::SocketTCP& sock);
  public:
    int dcData(sf::SocketTCP& sender, Chuck* chuck);
    int dcData(sf::SocketTCP& sender, int code, avifile::s_chunk* headers);
};

#endif /* DIFFUSION_HH_ */
