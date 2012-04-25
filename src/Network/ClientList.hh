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
# include <list>
# include "../Log/Log.hh"
# include <boost/thread/mutex.hpp>

class ClientList
{
  public:
    ClientList();
    virtual ~ClientList();
    static ClientList& getInstance();
    void addClient(sf::SocketTCP& control, sf::SocketTCP* data
        , std::string token);
    int link(sf::SocketTCP* data, std::string token);
    void removeClient(sf::SocketTCP& sock);
    Client* getClient(sf::SocketTCP& sock);
    Client* getClient(sf::SocketTCP* sock);
    Client* getClient(std::string token);
    std::string getPrivateIp(sf::SocketTCP sock);
    void setPrivateIp(sf::SocketTCP& sock, std::string ip);
    std::map<sf::SocketTCP, Client*> getClientList() const;
    void addBadClient(sf::SocketTCP& sock);
    std::list<sf::SocketTCP>& getBadClient();
    void getBadClientRelease();

  private:
    boost::mutex generalMutex_;
    boost::mutex privateIpMutex_;
    boost::mutex badClientMutex_;
    std::map<sf::SocketTCP, Client*> clientList_;
    std::map<std::string, Client*> clientLink_;
    std::map<sf::SocketTCP, std::string> privateIpList_;
    std::list<sf::SocketTCP> badClient_;
};

#endif /* CLIENTLIST_HH_ */
