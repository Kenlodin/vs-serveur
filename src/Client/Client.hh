/*
 * Client.h
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENT_H_
#define CLIENT_H_

# include "../FileManager/Chuck.hh"
# include "../FileManager/FileVideo.hh"
# include <SFML/Network.hpp>

class Client
{
  public:
    Client(sf::SocketTCP& control, sf::SocketUDP& data);
    virtual ~Client();
    virtual Chuck* getElement(int number) = 0;
    sf::SocketTCP& getControlSocket() const;
    sf::SocketUDP& getDataSocket() const;

private:
    sf::SocketTCP& controlSocket_;
    sf::SocketUDP& dataSocket_;
};

#endif /* CLIENT_H_ */
