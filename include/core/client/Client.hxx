/*
 * Client.hxx
 *
 *  Created on: 29 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENT_HXX_
# define CLIENT_HXX_

# include <core/client/Client.hh>

inline
std::list<boost_socket>& Client::getSockets()
{
  return sockets_;
}

inline
void Client::addSocket(boost_socket& newSocket)
{
    //sockets_.push_back(newSocket);
}

inline
void Client::remSocket(boost_socket& oldSocket)
{
    //sockets_.remove(oldSocket); TODO Problem
}

inline
std::string& Client::getToken()
{
  return token_;
}

inline
void Client::setToken(std::string token, int privilegeLevel)
{
  token_ = token;
  privilegeLevel_ = privilegeLevel;
}

inline
std::string& Client::getPublicIp()
{
  return publicIp_;
}

inline
std::string& Client::getPrivateIp()
{
  return privateIp_;
}

inline
void Client::setPrivateIp(std::string privateIp)
{
    privateIp_ = privateIp;
}

inline
FileVideo* Client::getTypeClient() const
{
  return typeClient_;
}

inline
void Client::setTypeClient(FileVideo* typeClient)
{
  typeClient_ = typeClient;
}

inline
bool Client::getIsActiv()
{
    return isActiv_;
}

inline
void Client::setIsActiv(bool newState)
{
    isActiv_ = newState;
}

inline
bool Client::tryLock()
{
  return using_.try_lock();
}

inline
void Client::lock()
{
  using_.lock();
}

inline
void Client::unlock()
{
  using_.unlock();
}


#endif /* CLIENT_HXX_ */
