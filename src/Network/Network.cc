/*
 * Network.cc
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

//Internal include
# include <core/network/Network.hh>
# include <core/thread/WorkList.hh>
# include <core/client/Client.hh>
# include <core/network/ClientList.hh>

Network::Network(std::list<unsigned short>& ports)
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

void Network::handleAccept(Client* newClient, int index
        , const boost::system::error_code& error)
{
  if (!error)
  {
    ClientList::getInstance().addClient(newClient);
    Dispatcher::getInstance().launchAsyncRead(newClient
      , newClient->getSockets().front());
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
  startAccepts();
  while (Config::getInstance ().isOnline ())
  {
    ClientList::getInstance().purgeClient();  
    usleep(1000);
  }
}
