/*
 * Client.h
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENT_H_
# define CLIENT_H_

// External include
# include <boost/asio/ip/tcp.hpp>
# include <boost/thread/mutex.hpp>
# include <list>

// Internal include
# include <core/fwd.hh>
# include <core/log/Log.hh>
# include <core/fileManager/FileVideo.hh>
# include <core/network/Packet.hh>


typedef boost::asio::ip::tcp::socket boost_socket;

/**
 * This class keep information of a connecting client in tracker or diffusion
 */
class Client
{
  public:
    /**
     *  Constructor
     *  @param control Traqueur socket of client can be null
     *  @param data Diffusion socket of client can be null
     *  @param token Connexion token of client
     */
    Client(boost_socket& socket, std::string& publicIp);

    /**
     * Destructor
     */
    virtual ~Client();

    /**
     * Get controlSocket
     *  @return Sockets
     */
    const std::list<boost_socket>& getSockets() const;

    /**
     *  Use controlSocket to send a packet
     *  @param newSocket socket for this client
     */
    void addSocket(boost_socket& socket);

    /**
     *  Use dataSocket to send a packet
     *  @param packet packet to be send
     *  @return RETURN_VALUE_GOOD on success and RETURN_VALUE_ERROR on error
     */
    int send(Packet& packet);

    /**
     *  Set control socket
     *  @param oldSocket socket remove from client
     */
    void remSocket(boost_socket& oldSocket);

    /**
     *  Get token client
     *  @return token of this client
     */
    std::string& getToken();

    /**
     *  Set token client
     *  @param token new token for this client
     */
    void setToken(std::string token, int privilegeLevel);
    
    /**
     *  Get token client
     *  @return public ip of this client
     */
    std::string& getPublicIp();
    
    /**
     *  Get token client
     *  @return private ip of this client
     */
    std::string& getPrivateIp();
    
    /**
     *  Set private ip client
     *  @param private ip for this client
     */
    void setPrivateIp(std::string privateIp);

    /**
     *  Get client type
     *  @return File that represent the current file readed by this client
     */
    FileVideo* getTypeClient() const;

    /**
     *  Set client type
     *  @param typeClient new typeClient for this client can be null
     */
    void setTypeClient(FileVideo* typeClient);
    
    /**
     * Set isActiv 
     * @param isActiv
     */
    void setIsActiv(bool newState);
    
    /**
     * Get isActiv
     * @return isActiv of client
     */
    bool getIsActiv();

    /**
     *  Try to lock this client
     *  @return true on success false if this client is already lock
     */
    bool tryLock();

    /**
     *  Lock this client
     */
    void lock();

    /**
     *  Unlock this client
     */
    void unlock();
private:
    /**
     *  Socket for server's dialog
     */
    std::list<boost_socket> sockets_;
    
    /**
     *  Privilege level
     */
    int privilegeLevel_;

    /**
     *  Interface which represent a VOD or Live connection
     */
    FileVideo* typeClient_; //TODO Change it to current action
    
    /**
     *  Public ip of client
     */
    std::string publicIp_;
    
    /**
     *  Private ip of client
     */
    std::string privateIp_;

    /**
     *  Token of connection
     */
    std::string token_;
    
    /**
     *  if it is true client will be remove
     */
    bool isActiv_;

    /**
     *  Mutex of this instance of client
     */
    boost::mutex using_;
};

//Inline Get/Set
# include <core/client/Client.hxx>

#endif /* CLIENT_H_ */
