/*
 * Client.h
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENT_H_
#define CLIENT_H_

# include <SFML/Network.hpp>
# include "../fwd.hh"
# include "TypeClient.hh"

class Client
{
  public:
    Client(sf::SocketTCP*& control, sf::SocketTCP*& data);
    virtual ~Client();

    sf::SocketTCP* getControlSocket() const;
    sf::SocketTCP* getDataSocket() const;
    int sendControl(sf::Packet& packet);
    int sendData(sf::Packet& packet);
    void setDataSocket(sf::SocketTCP* dataSocket);
private:
    sf::SocketTCP* controlSocket_;
    sf::SocketTCP* dataSocket_;
    TypeClient* typeClient;
};

#endif /* CLIENT_H_ */
