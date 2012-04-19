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

std::map<std::string, Client*> ClientList::getClientList() const
{
  return clientList_;
}

void ClientList::setClientList(std::map<std::string, Client*> clientList)
{
  clientList_ = clientList;
}

ClientList& ClientList::getInstance()
{
  static ClientList instance_;

  return instance_;
}

void ClientList::addClient(sf::SocketTCP* control, sf::SocketTCP* data,
    std::string ip)
{
  //Wait token and add in list
  generalMutex_.lock();
  tempList_[ip] = new Client(control, data);
  generalMutex_.unlock();
}

void ClientList::removeClient(std::string token)
{
  generalMutex_.lock();
  Client* c = clientList_[token];
  clientList_[token] = nullptr;
  generalMutex_.unlock();
  delete c;

}

Client* ClientList::getClient(std::string token)
{
  generalMutex_.lock();
  Client* c = clientList_[token];
  generalMutex_.unlock();
  return c;
}
