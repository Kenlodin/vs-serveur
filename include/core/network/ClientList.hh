/*
 * ClientList.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENTLIST_HH_
#define CLIENTLIST_HH_

// External include
# include <boost/asio/ip/tcp.hpp>
# include <list>
# include <set>
# include <boost/thread/mutex.hpp>

// Internal include
# include <core/client/Client.hh>
# include <core/log/Log.hh>
# include <core/sqlManager/SqlManager.hh>
# include <core/network/Dispatcher.hh>

/*
 * Manage client of this server
 */
class ClientList
{
  private: // Private because of singleton
    /**
     *  Constructor
     */
    ClientList();

    /**
     * Destructor
     */
    virtual ~ClientList();

  public:
    /**
     *  Get instance of Clientlist
     *  @return instance of Clientlist
     */
    static ClientList& getInstance();

    /**
     *  Add Client in list
     *  @param client to be add
     *  @return RETURN_VALUE_GOOD on success
     */
    int addClient(Client*& client);

    /**
     *  Link dataSocket to a client
     *  @param data data socket of client
     *  @param token of the client
     *  @return RETURN_VALUE_GOOD on success
     */
    int link(Client*& client, std::string& token);

    /**
     *  Remove client if possible
     *  @param sock that represent one client
     */
    int removeClient(Client*& client);
    
    /**
     *  Purge temporary client if possible
     */
    void purgeClient();

    /**
     *  Get client from token !!! Take care of lock
     *  @param token that represent one client
     *  @return client represented by this token
     */
    Client* getClient(std::string& token);

    /**
     *  Get list of client
     *  @return the list of client list
     */
    const std::set<Client*>& getClientList() const;

    /**
     *  Add sock which create a problem
     *  @param sock that send a bad packet
     *  @param errorNumber of this bad packet
     */
    void addBadClient(Client*& client, int errorNumber);

    /**
     *  Disconnect All client
     */
    void disconnectAllClient ();
    
  private:
    // Mutex of clientList_
    boost::mutex generalMutex_;

    // Mutex of remove temporary
    boost::mutex temporaryMutex_;

    // List of every client
    std::set<Client*> clientList_;

    // Temporary list of temporary client
    std::list<Client*> temporaryClient_;

    // List of link between token and client
    std::map<std::string, Client*> clientLink_;

};

#endif /* CLIENTLIST_HH_ */
