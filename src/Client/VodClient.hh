/*
 * VodClient.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef VODCLIENT_HH_
#define VODCLIENT_HH_

# include "Client.hh"
# include "../FileManager/VodFile.hh"
# include "../FileManager/Chuck.hh"

class VodClient : public Client
{
  public:
    VodClient(sf::SocketTCP& control, sf::SocketUDP& data, int videoId);
    virtual ~VodClient();
    virtual Chuck* getElement(int number);
};

#endif /* VODCLIENT_HH_ */
