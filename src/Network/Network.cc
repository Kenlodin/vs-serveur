/*
 * Network.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "Network.hh"
# include "../Diffusion/Diffusion.hh"
# include "../Tracker/Tracker.hh"

Network::Network(int control_port, int data_port)
: route_ (
	{
			&Network::clientTracker,
			&Network::trackerClient,
			&Network::clientDiffusion,
			&Network::diffusionClient,
			&Network::diffusionDiffusion
	})
{
	control_port_ = control_port;
	data_port_ = data_port;
	control_socket_ = new sf::SocketTCP();
	data_socket_ = new sf::SocketTCP();
	control_socket_->Listen(control_port_);
	data_socket_->Listen(data_port_);

}

Network::~Network() {
	data_socket_->Close();
	control_socket_->Close();
	delete data_socket_;
	delete control_socket_;
	// TODO Auto-generated destructor stub
}

static int thread_listener (sf::SocketTCP sock) {
	sf::SocketTCP new_client;
	sf::IPAddress ip;

	while (sock.IsValid())
	{
		sock.Accept(new_client, &ip);
		//TODO Keep_client;
	}
	return 1;
}

int Network::start() {
	/*pthread_create(control_thread, NULL, static_cast<void*(*)(void*)>(thread_listener)
			, static_cast<void*>(&control_socket_));
	pthread_create(data_thread, NULL, static_cast<void*(*)(void*)>(thread_listener)
				, static_cast<void*>(&data_socket_));*/
	return 1;
}

inline int routing(sf::Packet* packet) {
	return FALSE;
}

int Network::clientTracker(unsigned int route, sf::Packet* packet) {
	return FALSE;
}

int Network::trackerClient(unsigned int route, sf::Packet* packet) {
	return FALSE;
}

int Network::clientDiffusion(unsigned int route, sf::Packet* packet) {
	return FALSE;
}

int Network::diffusionClient(unsigned int route, sf::Packet* packet) {
	return FALSE;
}

int Network::diffusionDiffusion(unsigned int route, sf::Packet* packet) {
	return FALSE;
}






