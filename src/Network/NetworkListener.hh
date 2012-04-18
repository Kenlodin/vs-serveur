/*
 * NetworkListener.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef NETWORKLISTENER_HH_
#define NETWORKLISTENER_HH_

# include "../Thread/Thread.hh"
# include <SFML/Network.hpp>

class NetworkListener : public tools::Thread
{
  public:
    NetworkListener(sf::SocketTCP& serveur, void(*add)(sf::SocketTCP&, sf::IPAddress&));
    virtual ~NetworkListener();
    virtual void run ();
  private:
    sf::SocketTCP& server_;
    void(*add_)(sf::SocketTCP&, sf::IPAddress&);
};

#endif /* NETWORKLISTENER_HH_ */
