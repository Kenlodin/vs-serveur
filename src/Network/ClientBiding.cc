/*
 * ClientBiding.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "ClientBiding.hh"
#include "ClientList.hh"

ClientBiding::ClientBiding()
{
  // TODO Auto-generated constructor stub

}

ClientBiding::~ClientBiding()
{
  // TODO Auto-generated destructor stub
}

ClientBiding& ClientBiding::getInstance()
{
  static ClientBiding instance_;

  return instance_;
}

void ClientBiding::addDataSocket(sf::SocketTCP& newConnexion, sf::IPAddress ip)
{
  sf::SocketTCP* saveConnexion = new sf::SocketTCP(newConnexion);
  generalMutex_.lock();
  sf::SocketTCP* controlSocket = controlClient_[ip.ToString()];
  if (controlSocket == nullptr)
    dataClient_[ip.ToString()] = saveConnexion;
  else
  {
    ClientList::getInstance().addClient(controlSocket, saveConnexion);
    controlClient_[ip.ToString()] = nullptr;
  }
  generalMutex_.unlock();
}

void ClientBiding::addControlSocket(sf::SocketTCP& newConnexion,
    sf::IPAddress ip)
{
  sf::SocketTCP* saveConnexion = new sf::SocketTCP(newConnexion);
  generalMutex_.lock();
  sf::SocketTCP* dataSocket = dataClient_[ip.ToString()];
  if (dataSocket == nullptr)
    controlClient_[ip.ToString()] = saveConnexion;
  else
  {
    ClientList::getInstance().addClient(saveConnexion, dataSocket);
    dataClient_[ip.ToString()] = nullptr;
  }
  generalMutex_.unlock();
}

