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
    /**
     *  Constructor
     *  @param control_port of the server
     *  @param data_port of the server
     */
    Network(int control_port, int data_port);

    /**
     *  Destructor
     */
    virtual ~Network();
  public:
    /**
     *  Run accepting and routing process
     */
    void run ();

    /**
     *  Function which route packet
     *  @param packet received
     *  @param sock that send this packet
     */
    void routing(sf::Packet& packet, sf::SocketTCP& sock);
  private:
    // typedef of fonction handler
    typedef void (Network::*handler)(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    // Constant Array of handler
    const handler route_[ConnexionType::LENGTH];
  private:
    // Fonction handlers //
    /**
     *  Route a packet from client to tracker
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param sock that send this message
     */
    void clientTracker(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    /**
     *  Route a packet from tracker to client
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param sock that send this message
     */
    void trackerClient(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    /**
     *  Route a packet from client to diffusion
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param sock that send this message
     */
    void clientDiffusion(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    /**
     *  Route a packet from diffusion to client
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param sock that send this message
     */
    void diffusionClient(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);

    /**
     *  Route a packet from diffusion to diffusion
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param sock that send this message
     */
    void diffusionDiffusion(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock);
    
    /**
     *  Route a packet from administrator to server
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param sock that send this message
     */
    void adminServer(unsigned int route, sf::Packet& packet
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
