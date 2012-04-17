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

class Network {
public:
	Network(int control_port, int data_port);
	virtual ~Network();
	int start();
	int routing(sf::Packet* packet);
private:
	typedef int (Network::*handler)(unsigned int route, sf::Packet* packet);
	const handler route_[ConnexionType::LENGTH];
private:
	int clientTracker (unsigned int route, sf::Packet* packet);
	int trackerClient (unsigned int route, sf::Packet* packet);
	int clientDiffusion (unsigned int route, sf::Packet* packet);
	int diffusionClient (unsigned int route, sf::Packet* packet);
	int diffusionDiffusion (unsigned int route, sf::Packet* packet);
private:
	sf::SocketTCP* control_socket_;
	unsigned short control_port_;
	pthread_t* control_thread;

	sf::SocketTCP* data_socket_;
	unsigned short data_port_;
	pthread_t* data_thread;

	Diffusion* diffusion_;
	Tracker* tracker_;
};

#endif /* NETWORK_HH_ */
