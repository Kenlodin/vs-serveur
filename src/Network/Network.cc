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
# include <core/client/Client.hh>
# include <core/adminServer/AdminServer.hh>
# include <core/network/ClientList.hh>

Network::Network(std::list<unsigned short>& ports)
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
  serverPorts_.splice(serverPorts_.begin(), ports);
  for (unsigned short port : serverPorts_)
  {
      acceptors_.push_back(boostIp::tcp::acceptor(ioService_
                        , boostIp::tcp::endpoint(boostIp::tcp::v4(), port)));
      
  }
}

Network::~Network()
{
    /*for (boost_socket sock : acceptors)
    {
        sock.close();
        //TODO Purge clients
    }*/
}

void Network::routing(Packet& packet, Client*& client)
{
  uint16_t opcode;
  unsigned int type;
  unsigned int code;

  packet >> opcode;
  code = EXTRACT_CODE(opcode);
  type = EXTRACT_TYPE(opcode);
  if (type < ConnexionType::LENGTH)
    (this->*route_[type])(code, packet, client);
  else
  {
    COUTDEBUG("Network : mauvais routing.");
    ClientList::getInstance().addBadClient(client, RETURN_VALUE_ERROR);
  }
}

void Network::clientTracker(unsigned int route, Packet& packet,
    Client*& client)
{
  COUTDEBUG("Client*& --> Tracker");
  WorkList<Tracker>::getInstance().putWorks(&Tracker::routing, route, packet,
      client);
}

void Network::trackerClient(unsigned int route __attribute__((unused))
  , Packet& packet __attribute__((unused)), Client*& client)
{
  COUTDEBUG("Tracker --> Client");
  COUTDEBUG("Client*& : mauvais routing.");
  ClientList::getInstance().addBadClient(client, RETURN_VALUE_ERROR);
  //return RETURN_VALUE_ERROR;
}

void Network::clientDiffusion(unsigned int route, Packet& packet,
    Client*& client)
{
  COUTDEBUG("Client*& --> Diffusion");
  WorkList<Diffusion>::getInstance().putWorks(&Diffusion::routing, route,
      packet, client);
}

void Network::diffusionClient(unsigned int route __attribute__((unused))
  , Packet& packet __attribute__((unused)), Client*& client)
{
  COUTDEBUG("Diffusion --> Client");
  COUTDEBUG("Client*& : mauvais routing.");
  ClientList::getInstance().addBadClient(client, RETURN_VALUE_ERROR);
  //return RETURN_VALUE_ERROR;
}

void Network::diffusionDiffusion(unsigned int route, Packet& packet,
    Client*& client)
{
  COUTDEBUG("Diffusion --> Diffusion");
  WorkList<Diffusion>::getInstance().putWorks(&Diffusion::routing_internal,
      route, packet, client);
}

void Network::adminServer(unsigned int route, Packet& packet
        , Client*& client)
{
  WorkList<AdminServer>::getInstance ().putWorks (&AdminServer::routing,
                                                  route, packet, client);
}

void Network::handleAccept(Client* newClient, int index
        , const boost::system::error_code& error)
{
  if (!error)
  {
    ClientList::getInstance().addClient(newClient);
    launchAsyncRead(newClient);
  }
  else
    delete newClient;
  startAccept(index);
}

void none()
{
}

void Network::startAccepts()
{
    int index = 0;
    for (auto& acceptor : acceptors_)
    {
      Client* newClient = new Client(ioService_);
      auto fun = boost::bind(&Network::handleAccept, this, newClient, index 
      , boost::asio::placeholders::error); 
      
      acceptor.async_accept(newClient->getSockets().front(), fun);
      index++;
    }
}

void Network::startAccept(int index)
{
  Client* newClient = new Client(ioService_);
  auto fun = boost::bind(&Network::handleAccept, this, newClient, index
      , boost::asio::placeholders::error); 
  acceptors_[index].async_accept(newClient->getSockets().front(), fun); 
}

void Network::run()
{
  COUTDEBUG("Démarrage du serveur.");
  COUTDEBUG("Serveur démarré");
  while (Config::getInstance ().isOnline ())
  {
    startAccepts();
    
  }
}
