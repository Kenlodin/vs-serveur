/*
 * Network.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

# include "Network.hh"
# include "../Diffusion/Diffusion.hh"
# include "../Tracker/Tracker.hh"
# include "../Thread/WorkList.hh"
# include "ClientList.hh"

Network::Network(int control_port, int data_port)
    : route_(
    {
        &Network::clientTracker,
        &Network::trackerClient,
        &Network::clientDiffusion,
        &Network::diffusionClient,
        &Network::diffusionDiffusion })
{
  controlPort_ = control_port;
  controlSocket_ = new sf::SocketTCP();
  controlSocket_->Listen(controlPort_);

  dataPort_ = data_port;
  dataSocket_ = new sf::SocketTCP();
  dataSocket_->Listen(dataPort_);
}

Network::~Network()
{
  if (dataSocket_->IsValid())
    dataSocket_->Close();
  if (controlSocket_->IsValid())
    controlSocket_->Close();
  delete dataSocket_;
  delete controlSocket_;
  // TODO Auto-generated destructor stub
}

void Network::routing(sf::Packet& packet, sf::SocketTCP& sock)
{
  sf::Uint16 opcode;
  unsigned int type;
  unsigned int code;

  packet >> opcode;
  code = EXTRACT_CODE(opcode);
  type = EXTRACT_TYPE(opcode);
  if (type < ConnexionType::LENGTH)
    (this->*route_[type])(code, packet, sock);
  else
  {
    coutDebug("Network : mauvais routing.");
    ClientList::getInstance().addBadClient(sock);
  }
}

void Network::clientTracker(unsigned int route, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  coutDebug("Client --> Tracker");
  WorkList<Tracker>::getInstance().putWorks(&Tracker::routing, route, packet,
      sock);
}

void Network::trackerClient(unsigned int route, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  coutDebug("Tracker --> Client");
  coutDebug("Client : mauvais routing.");
  ClientList::getInstance().addBadClient(sock);
  //return RETURN_VALUE_ERROR;
}

void Network::clientDiffusion(unsigned int route, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  coutDebug("Client --> Diffusion");
  WorkList<Diffusion>::getInstance().putWorks(&Diffusion::routing, route,
      packet, sock);
}

void Network::diffusionClient(unsigned int route, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  coutDebug("Diffusion --> Client");
  coutDebug("Client : mauvais routing.");
  ClientList::getInstance().addBadClient(sock);
  //return RETURN_VALUE_ERROR;
}

void Network::diffusionDiffusion(unsigned int route, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  coutDebug("Diffusion --> Diffusion");
  WorkList<Diffusion>::getInstance().putWorks(&Diffusion::routing_internal,
      route, packet, sock);
}

void Network::run()
{
  coutDebug("Démarrage du serveur.");
  sf::SelectorTCP selector;
  selector.Add(*dataSocket_);
  selector.Add(*controlSocket_);
  coutDebug("Serveur démarré");
  while (true)
  {
    std::list<sf::SocketTCP>& toRemove =
        ClientList::getInstance().getBadClient();
    while (!toRemove.empty())
    {
      coutDebug("Suppression d'un client.");
      sf::SocketTCP& badClient = toRemove.front();
      ClientList::getInstance().removeClient(badClient);
      selector.Remove(badClient);
      toRemove.pop_front();
    }
    ClientList::getInstance().getBadClientRelease();
    unsigned int nb = selector.Wait();
    for (unsigned int i = 0; i < nb; i++)
    {
      sf::SocketTCP sock = selector.GetSocketReady(i);
      if (sock == *controlSocket_ || sock == *dataSocket_)
      {
        coutDebug("Nouveau client.");
        sf::SocketTCP client;
        sf::IPAddress ip;
        sock.Accept(client, &ip);
        ClientList::getInstance().setPrivateIp(client, ip.ToString());
        selector.Add(client);
      }
      else
      {
        sf::Packet packet;
        sf::Socket::Status status;
        if ((status = sock.Receive(packet)) != sf::Socket::Done) // TODO Dec Client
        {
          coutDebug("Suppression d'un client.");
          ClientList::getInstance().removeClient(sock);
          selector.Remove(sock);
          continue;
        }
        coutDebug("Nouveau packet.");
        routing(packet, sock);
      }
    }
  }
}
