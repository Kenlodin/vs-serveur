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

std::string ClientList::getPrivateIp(sf::SocketTCP sock)
{
  privateIpMutex_.lock();
  std::string res = privateIpList_[sock];
  privateIpList_.erase(sock);
  privateIpMutex_.unlock();
  return res;
}

void ClientList::setPrivateIp(sf::SocketTCP& sock, std::string ip)
{
  privateIpMutex_.lock();
  privateIpList_[sock] = ip;
  privateIpMutex_.unlock();
}

std::map<sf::SocketTCP, Client*> ClientList::getClientList() const
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
  clientList_[*data] = c;
  c->setDataSocket(data);
  generalMutex_.unlock();
  return RETURN_VALUE_GOOD;
}

ClientList& ClientList::getInstance()
{
  static ClientList instance_;

  return instance_;
}

void ClientList::addClient(sf::SocketTCP& control, sf::SocketTCP* data,
    std::string token)
{
  //Wait token and add in list
  generalMutex_.lock();
  Client* c = new Client(control, data, token);
  clientList_[control] = c;
  clientLink_[token] = c;
  generalMutex_.unlock();
}

void ClientList::removeClient(sf::SocketTCP& sock)
{
  generalMutex_.lock();
  std::map<sf::SocketTCP, Client*>::iterator it = clientList_.find(sock);
  Client* c;
  if (it != clientList_.end())
  {
    c = it->second;
    clientList_.erase(c->getControlSocket());
    if (c->getDataSocket() != nullptr)
      clientList_.erase(*(c->getDataSocket()));
    clientLink_.erase(c->getToken());
    delete c;
  }
  else
  {
    sock.Close();
  }
  generalMutex_.unlock();

}

Client* ClientList::getClient(sf::SocketTCP* sock)
{
  generalMutex_.lock();
  Client* c = clientList_[*sock];
  generalMutex_.unlock();
  return c;
}

Client* ClientList::getClient(sf::SocketTCP& sock)
{
  generalMutex_.lock();
  Client* c = clientList_[sock];
  generalMutex_.unlock();
  return c;
}

void ClientList::addBadClient(sf::SocketTCP& sock)
{
  badClientMutex_.lock();
  badClient_.insert(badClient_.begin(), sock);
  badClientMutex_.unlock();
}

std::list<sf::SocketTCP>& ClientList::getBadClient()
{
  badClientMutex_.lock();
  return badClient_;
}

void ClientList::getBadClientRelease()
{
  badClientMutex_.unlock();
}

