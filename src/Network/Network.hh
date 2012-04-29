/*
 * Network.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef NETWORK_HH_
# define NETWORK_HH_

//External include
# include <SFML/System.hpp>
# include <SFML/Network.hpp>

//Internal include
# include "../Thread/Thread.hh"
# include "../fwd.hh"
# include "../Diffusion/Diffusion.hh"
# include "../Tracker/Tracker.hh"
# include "../Log/Log.hh"

/*
 * Class which manager input connection and routing
 */
class Network : public tools::Thread
{
  public:
    // Constructor
    Network(int control_port, int data_port);

    // Destructor
    virtual ~Network();
  public:
    // Run accepting and routing process
    void run ();

    // Function which route packet
    void routing(sf::Packet& packet, sf::SocketTCP& sock);
  private:
    // typedef of fonction handler
    typedef void (Network::*handler)(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    // Constant Array of handler
    const handler route_[ConnexionType::LENGTH];
  private:
    // Fonction handlers //
    // Route a packet from client to tracker
    void clientTracker(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    // Route a packet from tracker to client
    void trackerClient(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    // Route a packet from client to diffusion
    void clientDiffusion(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    // Route a packet from diffusion to client
    void diffusionClient(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    // Route a packet from diffusion to diffusion
    void diffusionDiffusion(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);
  private:
    // Variables of tracker
    sf::SocketTCP* controlSocket_;
    unsigned short controlPort_;

    // Variables of diffusion
    sf::SocketTCP* dataSocket_;
    unsigned short dataPort_;
};

#endif /* NETWORK_HH_ */
