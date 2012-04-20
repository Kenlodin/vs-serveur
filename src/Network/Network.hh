/*
 * Network.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef NETWORK_HH_
#define NETWORK_HH_

# include <SFML/System.hpp>
# include <SFML/Network.hpp>
# include "../Thread/Thread.hh"
# include "../fwd.hh"
# include "../Diffusion/Diffusion.hh"
# include "../Tracker/Tracker.hh"

class Network : public tools::Thread
{
  public:
    Network(int control_port, int data_port, Tracker* tracker,
        Diffusion* diffusion);
    virtual ~Network();
  public:
    void run ();
    void routing(sf::Packet& packet, sf::SocketTCP& sock);

  private:
    typedef void (Network::*handler)(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);
    const handler route_[ConnexionType::LENGTH];
  private:
    void clientTracker(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);
    void trackerClient(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);
    void clientDiffusion(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);
    void diffusionClient(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);
    void diffusionDiffusion(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);
  private:
    sf::SocketTCP* controlSocket_;
    unsigned short controlPort_;


    sf::SocketTCP* dataSocket_;
    unsigned short dataPort_;


    Diffusion* diffusion_;
    Tracker* tracker_;
};

#endif /* NETWORK_HH_ */
