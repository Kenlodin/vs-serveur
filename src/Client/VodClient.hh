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
    VodClient(sf::SocketTCP& control, sf::SocketUDP& data);
    virtual ~VodClient();
    virtual Chuck* getElement(int number);
  private:
    VodFile* currentVideo;
};

#endif /* VODCLIENT_HH_ */
