/*
 * Network.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "Network.hh"
# include "../Diffusion/Diffusion.hh"
# include "../Tracker/Tracker.hh"

Network::Network(int control_port, int data_port
		, Tracker* tracker, Diffusion* diffusion)
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
	tracker_ = tracker;
	diffusion_ = diffusion;
}

Network::~Network() {
	data_socket_->Close();
	control_socket_->Close();
	delete data_socket_;
	delete control_socket_;
	// TODO Auto-generated destructor stub
}

int Network::start() {
	return 1;
}

int Network::routing(sf::Packet* packet) {
	sf::Int16 opcode;
	int type;
	int code;

	*packet >> opcode;
	code = EXTRACT_CODE(opcode);
	type = EXTRACT_TYPE(opcode);
	if (code < CD::LENGTH)
		return (this->*route_[type]) (code, packet);
	else
		return TRUE;
}

int Network::clientTracker(unsigned int route, sf::Packet* packet) {
	return tracker_->routing(route, packet);
}

int Network::trackerClient(unsigned int route, sf::Packet* packet) {
	return TRUE;
}

int Network::clientDiffusion(unsigned int route, sf::Packet* packet) {
	return diffusion_->routing(route, packet);
}

int Network::diffusionClient(unsigned int route, sf::Packet* packet) {
	return TRUE;
}

int Network::diffusionDiffusion(unsigned int route, sf::Packet* packet) {
	return diffusion_->routing_internal(route, packet);
}






