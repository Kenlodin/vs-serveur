/*
 * Network.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

# include "Network.hh"
# include "../Diffusion/Diffusion.hh"
# include "../Tracker/Tracker.hh"
# include "ClientList.hh"

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

int Network::routing(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Int16 opcode;
  int type;
  int code;

  packet >> opcode;
  code = EXTRACT_CODE(opcode);
  type = EXTRACT_TYPE(opcode);
  if (code < CD::LENGTH)
    return (this->*route_[type])(code, packet, sock);
  else
    return RETURN_VALUE_ERROR;
}

int Network::clientTracker(unsigned int route, sf::Packet& packet, sf::SocketTCP& sock)
{
  return tracker_->routing(route, packet, sock);
}

int Network::trackerClient(unsigned int route, sf::Packet& packet, sf::SocketTCP& sock)
{
  return RETURN_VALUE_ERROR;
}

int Network::clientDiffusion(unsigned int route, sf::Packet& packet, sf::SocketTCP& sock)
{
  return diffusion_->routing(route, packet, sock);
}

int Network::diffusionClient(unsigned int route, sf::Packet& packet, sf::SocketTCP& sock)
{
  return RETURN_VALUE_ERROR;
}

int Network::diffusionDiffusion(unsigned int route, sf::Packet& packet, sf::SocketTCP& sock)
{
  return diffusion_->routing_internal(route, packet, sock);
}

void Network::run ()
{
  sf::SelectorTCP selector;
  selector.Add(*dataSocket_);
  selector.Add(*controlSocket_);
  while (true)
  {
    unsigned int nb = selector.Wait();
    for (unsigned int i = 0; i < nb; i++)
    {
      sf::SocketTCP sock = selector.GetSocketReady(i);
      if (sock == *controlSocket_ || sock == *dataSocket_)
      {
        sf::SocketTCP client;
        sock.Accept(client, nullptr);
        selector.Add(client);
      }
      else
      {
        sf::Packet packet;
        sock.Receive(packet);
        int returnValue = routing(packet, sock);
        if (returnValue != RETURN_VALUE_GOOD)
          selector.Remove(sock);
        if (returnValue == RETURN_VALUE_ERROR)
        {
          ClientList::getInstance().removeClient(&sock); //TODO
          sock.Close();
        }
      }
    }
  }
}
