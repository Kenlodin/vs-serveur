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
# include <pthread.h>
# include "../fwd.hh"
# include "../Diffusion/Diffusion.hh"
# include "../Tracker/Tracker.hh"

class Network
{
  public:
    Network(int control_port, int data_port, Tracker* tracker,
        Diffusion* diffusion);
    virtual ~Network();
  public:
    int start();
    int routing(sf::Packet* packet);
    int sendControl(sf::Packet& packet);
    int sendData(sf::Packet& packet);
  private:
    typedef int (Network::*handler)(unsigned int route, sf::Packet* packet);
    const handler route_[ConnexionType::LENGTH];
  private:
    int clientTracker(unsigned int route, sf::Packet* packet);
    int trackerClient(unsigned int route, sf::Packet* packet);
    int clientDiffusion(unsigned int route, sf::Packet* packet);
    int diffusionClient(unsigned int route, sf::Packet* packet);
    int diffusionDiffusion(unsigned int route, sf::Packet* packet);
  private:
    sf::SocketTCP* controlSocket_;
    unsigned short controlPort_;
    pthread_t* control_thread;
    std::map<std::string, sf::SocketTCP> controlClient;

    sf::SocketTCP* dataSocket_;
    unsigned short dataPort_;
    pthread_t* data_thread;
    std::map<std::string, sf::SocketTCP> dataClient;

    Diffusion* diffusion_;
    Tracker* tracker_;
};

#endif /* NETWORK_HH_ */
