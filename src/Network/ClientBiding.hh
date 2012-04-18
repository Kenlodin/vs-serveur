/*
 * ClientBiding.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef CLIENTBIDING_HH_
#define CLIENTBIDING_HH_

# include <SFML/Network.hpp>
# include <boost/thread/mutex.hpp>

class ClientBiding
{
  public:
    ClientBiding();
    virtual ~ClientBiding();
    static ClientBiding& getInstance();
    void addDataSocket(sf::SocketTCP& newConnexion, sf::IPAddress ip);
    void addControlSocket(sf::SocketTCP& newConnexion, sf::IPAddress ip);
  private:
    boost::mutex generalMutex_;
    std::map<std::string, sf::SocketTCP*> controlClient_;
    std::map<std::string, sf::SocketTCP*> dataClient_;

};

#endif /* CLIENTBIDING_HH_ */
