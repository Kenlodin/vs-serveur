/*
 * ClientList.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "ClientList.hh"

ClientList::ClientList()
{
  // TODO Auto-generated constructor stub

}

ClientList::~ClientList()
{
  // TODO Auto-generated destructor stub
}

std::map<sf::SocketTCP*, Client*> ClientList::getClientList() const
{
  return clientList_;
}

void ClientList::link(sf::SocketTCP* data, Client* client)
{
  generalMutex_.lock();
  clientList_[data] = client;
  generalMutex_.unlock();
}

void ClientList::setClientList(std::map<sf::SocketTCP*, Client*> clientList)
{
  clientList_ = clientList;
}

ClientList& ClientList::getInstance()
{
  static ClientList instance_;

  return instance_;
}

void ClientList::addClient(sf::SocketTCP* control, sf::SocketTCP* data)
{
  //Wait token and add in list
  generalMutex_.lock();
  clientList_[control] = new Client(control, data);
  generalMutex_.unlock();
}

void ClientList::removeClient(sf::SocketTCP* sock)
{
  generalMutex_.lock();
  Client* c = clientList_[sock];
  clientList_[sock] = nullptr;
  generalMutex_.unlock();
  delete c;

}

Client* ClientList::getClient(sf::SocketTCP* sock)
{
  generalMutex_.lock();
  Client* c = clientList_[sock];
  generalMutex_.unlock();
  return c;
}
