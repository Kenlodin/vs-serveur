/*
 * ClientList.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include <core/network/ClientList.hh>

ClientList::ClientList()
{
}

ClientList::~ClientList()
{
}

const std::map<boost_socket, Client*>& ClientList::getClientList() const
{
  return clientList_;
}

int ClientList::link(Client*& client, std::string& token)
{
  std::map<std::string, Client*>::iterator it;
  Client* c = nullptr;

  generalMutex_.lock();
  it = clientLink_.find(token);
  if (it  == clientLink_.end())
  {
      clientLink_[token] = client;
  }
  else
  {
    /*c = it->second; TODO FIXIT
    for (auto sock : client->getSockets())
    {
    clientList_[sock] = c;
    c->addSocket(sock);
    }
    client->getSockets()->clear();
    delete client;
    client = c;*/
  }
  generalMutex_.unlock();
  return RETURN_VALUE_GOOD;
}

ClientList& ClientList::getInstance()
{
  static ClientList instance_;

  return instance_;
}

int ClientList::addClient(Client*& client)
{
    generalMutex_.lock();
    //clientList_[client->sockets_.front()] = client; TODO FIXIT
    generalMutex_.unlock();
  return RETURN_VALUE_GOOD;
}

void ClientList::removeClient(Client*& client)
{
  /*generalMutex_.lock(); TODO FIXIT
  purgeClient();
  std::map<sf::SocketTCP, Client*>::iterator it = clientList_.find(sock);
  Client*& c;
  if (it != clientList_.end())
  {
      c = it->second;
      for (const boost_socket sock : c->getSockets())
      {
          clientList_.erase(sock);
      }
      if (c->getToken() != "")
          clientLink_.erase(c->getToken());
      generalMutex_.unlock();
      c->setIsActiv(false);
      if (c->tryLock())
          delete c;
      else
      {
          temporaryMutex_.lock();
          temporaryClient_.push_back(c);
          temporaryMutex_.unlock();
      }
      return RETURN_VALUE_GOOD;
  }
  else
  {
      generalMutex_.unlock();
      COUTDEBUG("Error : Try to remove client which don't exist.")
      return RETURN_VALUE_ERROR;
  }*/
}
  
  void ClientList::removeClient(boost_socket& sock)
{
  /*generalMutex_.lock(); TODO FIXIT
  purgeClient();
  for (const boost_socket sock : c->getSockets())
  {
      clientList_.erase(sock);
  }
  if (c->getToken() != "")
    clientLink_.erase(c->getToken());
  generalMutex_.unlock();
  c->setIsActiv(false);
  if (c->tryLock())
    delete c;
  else
  {
    temporaryMutex_.lock();
    temporaryClient_.push_back(c);
    temporaryMutex_.unlock();
  }
  return RETURN_VALUE_GOOD;*/
}

Client*& ClientList::getClient(boost_socket& sock)
{
  /*std::map<boost_socket, Client*>::iterator it; TODO FIXIT
  Client*& c = nullptr;

  generalMutex_.lock();
  it = clientList_.find(sock);
  if (it != clientList_.end())
  {
    c = it->second;
    c->lock();
  }
  generalMutex_.unlock();
  return c;*/
}

void ClientList::addBadClient(Client*& client, int errorNumber)
{
  badClientMutex_.lock();
  badClient_.insert(badClient_.begin(),
      std::pair<Client*, int>(client, errorNumber));
  badClientMutex_.unlock();
}

std::list<std::pair<Client*, int>>& ClientList::getBadClient()
{
  badClientMutex_.lock();
  return badClient_;
}

Client*& ClientList::getClient(std::string& token)
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

void ClientList::disconnectAllClient ()
{
  generalMutex_.lock ();
  for (std::pair<std::string, Client*> c : clientLink_)
  {
    delete c.second;
  }
  clientLink_.clear ();
  clientList_.clear ();
  generalMutex_.unlock ();
  temporaryMutex_.lock();
  for (auto c : temporaryClient_)
      delete c;
  temporaryClient_.clear ();
  temporaryMutex_.unlock();
  badClientMutex_.lock();
  badClient_.clear ();
  badClientMutex_.unlock();
  
}
