/*
 * Network.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

//Internal include
# include <core/network/Network.hh>
# include <core/diffusion/Diffusion.hh>
# include <core/tracker/Tracker.hh>
# include <core/thread/WorkList.hh>
# include <core/adminServer/AdminServer.hh>
# include <core/network/ClientList.hh>

Network::Network(int control_port, int data_port)
    : route_(
    {
        &Network::clientTracker,
        &Network::trackerClient,
        &Network::clientDiffusion,
        &Network::diffusionClient,
        &Network::diffusionDiffusion,
        NULL,
        &Network::adminServer})
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
    COUTDEBUG("Network : mauvais routing.");
    ClientList::getInstance().addBadClient(sock, RETURN_VALUE_ERROR);
  }
}

void Network::clientTracker(unsigned int route, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  COUTDEBUG("Client --> Tracker");
  WorkList<Tracker>::getInstance().putWorks(&Tracker::routing, route, packet,
      sock);
}

void Network::trackerClient(unsigned int route __attribute__((unused))
  , sf::Packet& packet __attribute__((unused)), sf::SocketTCP& sock)
{
  COUTDEBUG("Tracker --> Client");
  COUTDEBUG("Client : mauvais routing.");
  ClientList::getInstance().addBadClient(sock, RETURN_VALUE_ERROR);
  //return RETURN_VALUE_ERROR;
}

void Network::clientDiffusion(unsigned int route, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  COUTDEBUG("Client --> Diffusion");
  WorkList<Diffusion>::getInstance().putWorks(&Diffusion::routing, route,
      packet, sock);
}

void Network::diffusionClient(unsigned int route __attribute__((unused))
  , sf::Packet& packet __attribute__((unused)), sf::SocketTCP& sock)
{
  COUTDEBUG("Diffusion --> Client");
  COUTDEBUG("Client : mauvais routing.");
  ClientList::getInstance().addBadClient(sock, RETURN_VALUE_ERROR);
  //return RETURN_VALUE_ERROR;
}

void Network::diffusionDiffusion(unsigned int route, sf::Packet& packet,
    sf::SocketTCP& sock)
{
  COUTDEBUG("Diffusion --> Diffusion");
  WorkList<Diffusion>::getInstance().putWorks(&Diffusion::routing_internal,
      route, packet, sock);
}

void Network::adminServer(unsigned int route, sf::Packet& packet
        , sf::SocketTCP& sock)
{
  WorkList<AdminServer>::getInstance ().putWorks (&AdminServer::routing,
                                                  route, packet, sock);
}

void Network::run()
{
  COUTDEBUG("Démarrage du serveur.");
  sf::SelectorTCP selector;
  selector.Add(*dataSocket_);
  selector.Add(*controlSocket_);
  COUTDEBUG("Serveur démarré");
  while (Config::getInstance ().isOnline ())
  {
    std::list<std::pair<sf::SocketTCP, int>>& toRemove =
        ClientList::getInstance().getBadClient();
    while (!toRemove.empty())
    {
      COUTDEBUG("Suppression d'un client.");
      std::pair<sf::SocketTCP, int>& badClient = toRemove.front();
      selector.Remove(badClient.first);
      if (badClient.second == RETURN_VALUE_ERROR)
        ClientList::getInstance().removeClient(badClient.first);
      toRemove.pop_front();
    }
    ClientList::getInstance().getBadClientRelease();

    unsigned int nb = selector.Wait(1);
    for (unsigned int i = 0; i < nb; i++)
    {
      sf::SocketTCP sock = selector.GetSocketReady(i);
      if (sock == *controlSocket_ || sock == *dataSocket_)
      {
        COUTDEBUG("Nouveau client.");
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
        if ((status = sock.Receive(packet)) != sf::Socket::Done)
        {
          COUTDEBUG("Deconnection d'un client.");
          ClientList::getInstance().addBadClient(sock, RETURN_VALUE_ERROR);
          continue;
        }
        COUTDEBUG("Nouveau packet.");
        routing(packet, sock);
      }
    }
  }
}
