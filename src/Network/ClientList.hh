/*
 * ClientList.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENTLIST_HH_
#define CLIENTLIST_HH_

# include "../Client/Client.hh"
# include <SFML/Network.hpp>
# include <boost/thread/mutex.hpp>

class ClientList
{
  public:
    ClientList();
    virtual ~ClientList();
    static ClientList& getInstance();
    void addClient(sf::SocketTCP* control, sf::SocketTCP* data);
    void removeClient(std::string token);
    Client* getClient(std::string token);
    std::map<std::string, Client*> getClientList() const;
    void setClientList(std::map<std::string, Client*> clientList);
  private:
    boost::mutex generalMutex_;
    std::map<std::string, Client*> clientList_;
};

#endif /* CLIENTLIST_HH_ */
