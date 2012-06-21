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

/*
 * This class keep information of a connecting client in tracker or diffusion
 */
class Client
{
  public:
    // Constructor
    Client(sf::SocketTCP* control, sf::SocketTCP*& data, std::string token);

    // Destructor
    virtual ~Client();

    // Get controlSocket
    sf::SocketTCP* getControlSocket() const;

    // Get dataSocket
    sf::SocketTCP* getDataSocket() const;

    // Use controlSocket to send a packet
    int sendControl(sf::Packet& packet);

    // Use dataSocket to send a packet
    int sendData(sf::Packet& packet);

    // Set control socket
    void setControlSocket(sf::SocketTCP* controlSocket);

    // Set data socket
    void setDataSocket(sf::SocketTCP* dataSocket);

    // Get token client
    std::string& getToken();

    // Set token client
    void setToken(std::string token);

    // Get client type
    FileVideo* getTypeClient() const;

    // Set client type
    void setTypeClient(FileVideo* typeClient);

    // Try to lock this client
    bool tryLock();

    // Lock this client
    void lock();

    // Unlock this client
    void unlock();
private:
    // Socket for tracker dialog
    sf::SocketTCP* controlSocket_;

    // Socket for diffusion data transfert
    sf::SocketTCP* dataSocket_;

    // Interface which represent a VOD or Live connection
    FileVideo* typeClient_;

    // Token of connection
    std::string token_;

    // Mutex of this instance of client
    boost::mutex using_;
};

//Inline Get/Set
# include "Client.hxx"

#endif /* CLIENT_H_ */
