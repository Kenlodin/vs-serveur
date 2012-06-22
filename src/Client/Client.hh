/*
 * Client.h
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENT_H_
# define CLIENT_H_

// External include
# include <SFML/Network.hpp>
# include <boost/thread/mutex.hpp>

// Internal include
# include "../fwd.hh"
# include "../Log/Log.hh"
# include "../FileManager/FileVideo.hh"

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
    Client(sf::SocketTCP* control, sf::SocketTCP*& data, std::string token);

    /**
     * Destructor
     */
    virtual ~Client();

    /**
     * Get controlSocket
     *  @return pointer of SocketTCP can be null
     */
    sf::SocketTCP* getControlSocket() const;

    /**
     *  Get dataSocket
     *  @return pointer of SocketTCP can be null
     */
    sf::SocketTCP* getDataSocket() const;

    /**
     *  Use controlSocket to send a packet
     *  @param packet packet to be send
     *  @return RETURN_VALUE_GOOD on success and RETURN_VALUE_ERROR on error
     */
    int sendControl(sf::Packet& packet);

    /**
     *  Use dataSocket to send a packet
     *  @param packet packet to be send
     *  @return RETURN_VALUE_GOOD on success and RETURN_VALUE_ERROR on error
     */
    int sendData(sf::Packet& packet);

    /**
     *  Set control socket
     *  @param controlSocket new ControlSocket for this client can be null
     */
    void setControlSocket(sf::SocketTCP* controlSocket);

    /**
     *  Set data socket
     *  @param dataSocket new DataSocket for this client can be null
     */
    void setDataSocket(sf::SocketTCP* dataSocket);

    /**
     *  Get token client
     *  @return token of this client
     */
    std::string& getToken();

    /**
     *  Set token client
     *  @param token new token for this client
     */
    void setToken(std::string token);

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
     *  Socket for tracker dialog
     */
    sf::SocketTCP* controlSocket_;

    /**
     *  Socket for diffusion data transfert
     */
    sf::SocketTCP* dataSocket_;

    /**
     *  Interface which represent a VOD or Live connection
     */
    FileVideo* typeClient_;

    /**
     *  Token of connection
     */
    std::string token_;

    /**
     *  Mutex of this instance of client
     */
    boost::mutex using_;
};

//Inline Get/Set
# include "Client.hxx"

#endif /* CLIENT_H_ */
