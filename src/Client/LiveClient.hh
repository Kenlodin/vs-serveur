/*
 * LiveClient.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef LIVECLIENT_HH_
#define LIVECLIENT_HH_

# include "Client.hh"

class LiveClient : public Client
{
  public:
    LiveClient(sf::SocketTCP& control, sf::SocketUDP& data);
    virtual ~LiveClient();
    virtual Chuck* getElement(int number);
  private:
};

#endif /* LIVECLIENT_HH_ */
