/*
 * Network.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#include "Network.hh"
# include "../Diffusion/Diffusion.hh"
# include "../Tracker/Tracker.hh"

Network::Network(int control_port, int data_port, Tracker* tracker,
    Diffusion* diffusion)
    : route_(
    { &Network::clientTracker, &Network::trackerClient,
        &Network::clientDiffusion, &Network::diffusionClient,
        &Network::diffusionDiffusion })
{
  controlPort_ = control_port;
  controlSocket_ = new sf::SocketTCP();
  controlSocket_->Listen(controlPort_);

  dataPort_ = data_port;
  dataSocket_ = new sf::SocketTCP();
  dataSocket_->Listen(dataPort_);

  tracker_ = tracker;
  diffusion_ = diffusion;
}

Network::~Network()
{
  dataSocket_->Close();
  controlSocket_->Close();
  delete dataSocket_;
  delete controlSocket_;
  // TODO Auto-generated destructor stub
}

int Network::start()
{
  return 1;
}

int Network::routing(sf::Packet* packet)
{
  sf::Int16 opcode;
  int type;
  int code;

  *packet >> opcode;
  code = EXTRACT_CODE(opcode);
  type = EXTRACT_TYPE(opcode);
  if (code < CD::LENGTH)
    return (this->*route_[type])(code, packet);
  else
    return TRUE;
}

int Network::clientTracker(unsigned int route, sf::Packet* packet)
{
  return tracker_->routing(route, packet);
}

int Network::trackerClient(unsigned int route, sf::Packet* packet)
{
  return TRUE;
}

int Network::clientDiffusion(unsigned int route, sf::Packet* packet)
{
  return diffusion_->routing(route, packet);
}

int Network::diffusionClient(unsigned int route, sf::Packet* packet)
{
  return TRUE;
}

int Network::diffusionDiffusion(unsigned int route, sf::Packet* packet)
{
  return diffusion_->routing_internal(route, packet);
}

int Network::sendControl(sf::Packet& packet)
{
  if (controlSocket_->Send(packet) != sf::Socket::Status::Done)
    return TRUE;
  return FALSE;
}

int Network::sendData(sf::Packet& packet)
{
  if (dataSocket_->Send(packet) != sf::Socket::Status::Done)
    return TRUE;
  return FALSE;
}
