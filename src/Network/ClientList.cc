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

int ClientList::link(sf::SocketTCP* data, std::string token)
{
  generalMutex_.lock();
  Client* c = clientLink_[token];
  if (c == nullptr)
  {
    generalMutex_.unlock();
    return RETURN_VALUE_ERROR;
  }
  clientList_[data] = c;
  generalMutex_.unlock();
  return RETURN_VALUE_GOOD;
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

void ClientList::addClient(sf::SocketTCP* control, sf::SocketTCP* data,
    std::string token)
{
  //Wait token and add in list
  generalMutex_.lock();
  Client* c = new Client(control, data, token);
  clientList_[control] = c;
  clientLink_[token] = c;
  generalMutex_.unlock();
}

void ClientList::removeClient(sf::SocketTCP* sock)
{
  generalMutex_.lock();
  Client* c = clientList_[sock];
  if (c != nullptr)
  {
    clientList_[sock] = nullptr;
    clientLink_[c->getToken()] = nullptr;
  }
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
