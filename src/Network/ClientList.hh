/*
 * ClientList.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENTLIST_HH_
#define CLIENTLIST_HH_

// External include
# include <SFML/Network.hpp>
# include <list>
# include <boost/thread/mutex.hpp>

// Internal include
# include "../Client/Client.hh"
# include "../Log/Log.hh"

/*
 * Manage client of this server
 */
class ClientList
{
  private: // Private because of singleton
    // Constructor
    ClientList();

    //Destructor
    virtual ~ClientList();

  public:
    // Get instance of Clientlist
    static ClientList& getInstance();

    // Add Client in list
    int addClient(sf::SocketTCP& control, sf::SocketTCP* data
        , std::string token);

    // Link dataSocket to a client
    int link(sf::SocketTCP* data, std::string token);

    // Remove client if possible
    void removeClient(sf::SocketTCP& sock);

    // Purge temporary client if possible
    void purgeClient();

    // Get client from a socket !!! Take care of lock
    Client* getClient(sf::SocketTCP& sock);
    Client* getClient(sf::SocketTCP* sock);

    // Get client from token !!! Take care of lock
    Client* getClient(std::string token);


    // Get private IP of this socket
    std::string getPrivateIp(sf::SocketTCP sock);

    // Set private IP of a socket
    void setPrivateIp(sf::SocketTCP& sock, std::string ip);

    // Get list of client
    std::map<sf::SocketTCP, Client*> getClientList() const;

    // Add sock which create a problem
    void addBadClient(sf::SocketTCP& sock, int errorNumber);

    // get list of bad client and lock it
    std::list<std::pair<sf::SocketTCP, int>>& getBadClient();

    // unlock bad client list
    void getBadClientRelease();

  private:
    // Mutex of clientList_
    boost::mutex generalMutex_;

    // Mutex of privateIP
    boost::mutex privateIpMutex_;

    // Mutex of badClient
    boost::mutex badClientMutex_;

    // Mutex of remove temporary
    boost::mutex temporaryMutex_;

    // List of every client
    std::map<sf::SocketTCP, Client*> clientList_;

    // Temporary list of bad client
    std::list<Client*> temporaryClient_;

    // List of link between token and client
    std::map<std::string, Client*> clientLink_;

    // List of link between socket and privateIP
    std::map<sf::SocketTCP, std::string> privateIpList_;

    // List of badClient
    std::list<std::pair<sf::SocketTCP, int>> badClient_;
};

#endif /* CLIENTLIST_HH_ */
