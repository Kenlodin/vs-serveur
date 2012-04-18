/*
 * Network.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

# include "Network.hh"
# include "../Diffusion/Diffusion.hh"
# include "../Tracker/Tracker.hh"
# include "ClientBiding.hh"

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

static void addData (sf::SocketTCP& socket, sf::IPAddress& ip)
{
  ClientBiding::getInstance().addDataSocket(socket, ip);
}

static void addControl (sf::SocketTCP& socket, sf::IPAddress& ip)
{
  ClientBiding::getInstance().addControlSocket(socket, ip);
}

int Network::start()
{
  control_thread = new NetworkListener(*controlSocket_, addControl);
  control_thread->start();
  data_thread = new NetworkListener(*dataSocket_, addData);
  data_thread->start();
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


