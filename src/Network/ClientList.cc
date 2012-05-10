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
  std::map<std::string, Client*>::iterator it;
  Client* c = nullptr;

  generalMutex_.lock();
  it = clientLink_.find(token);
  if (it  == clientLink_.end())
  {
    generalMutex_.unlock();
    return RETURN_VALUE_ERROR;
  }
  c = it->second;
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

int ClientList::addClient(sf::SocketTCP& control, sf::SocketTCP* data,
    std::string token)
{
  //Wait token and add in list
  generalMutex_.lock();
  if (clientList_.find(control) != clientList_.end()
      || (data && clientList_.find(*data) != clientList_.end())
      || clientLink_.find(token) != clientLink_.end())
  {
    generalMutex_.unlock();
    return RETURN_VALUE_ERROR;
  }
  Client* c = new Client(control, data, token);
  clientList_[control] = c;
  if (data != nullptr)
    clientList_[*data] = c;
  clientLink_[token] = c;
  generalMutex_.unlock();
  return RETURN_VALUE_GOOD;
}

void ClientList::removeClient(sf::SocketTCP& sock)
{
  purgeClient();
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
    if (c->tryLock())
      delete c;
    else
    {
      temporaryMutex_.lock();
      temporaryClient_.insert(temporaryClient_.end(), c);
      temporaryMutex_.unlock();
    }
  }
  else if (sock.IsValid())
  {
    privateIpMutex_.lock();
    privateIpList_.erase(sock);
    privateIpMutex_.unlock();
    sock.Close();
  }
  generalMutex_.unlock();

}

Client* ClientList::getClient(sf::SocketTCP* sock)
{
  std::map<sf::SocketTCP, Client*>::iterator it;
  Client* c = nullptr;

  generalMutex_.lock();
  it = clientList_.find(*sock);
  if (it != clientList_.end())
  {
    c = it->second;
    c->lock();
  }
  generalMutex_.unlock();
  return c;
}

Client* ClientList::getClient(sf::SocketTCP& sock)
{
  std::map<sf::SocketTCP, Client*>::iterator it;
  Client* c = nullptr;

  generalMutex_.lock();
  it = clientList_.find(sock);
  if (it != clientList_.end())
  {
    c = it->second;
    c->lock();
  }
  generalMutex_.unlock();
  return c;
}

void ClientList::addBadClient(sf::SocketTCP sock, int errorNumber)
{
  badClientMutex_.lock();
  badClient_.insert(badClient_.begin(),
      std::pair<sf::SocketTCP, int>(sock, errorNumber));
  badClientMutex_.unlock();
}

std::list<std::pair<sf::SocketTCP, int>>& ClientList::getBadClient()
{
  badClientMutex_.lock();
  return badClient_;
}

Client* ClientList::getClient(std::string token)
{
  std::map<std::string, Client*>::iterator it;
  Client* client = nullptr;

  generalMutex_.lock();
  it = clientLink_.find(token);
  if (it != clientLink_.end())
  {
    client = it->second;
    client->lock();
  }
  generalMutex_.unlock();
  return client;
}

void ClientList::purgeClient()
{
  Client* c = nullptr;
  temporaryMutex_.lock();
  unsigned int length = temporaryClient_.size();
  for (unsigned int i = 0; i < length; i++)
  {
    c = temporaryClient_.front();
    if (c->tryLock())
      delete c;
    else
      temporaryClient_.insert(temporaryClient_.end(), c);
    temporaryClient_.pop_front();
  }
  temporaryMutex_.unlock();
}

void ClientList::getBadClientRelease()
{
  badClientMutex_.unlock();
}

