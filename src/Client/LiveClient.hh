/*
 * LiveClient.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef LIVECLIENT_HH_
#define LIVECLIENT_HH_

# include "TypeClient.hh"

class LiveClient : public TypeClient
{
  public:
    LiveClient(int videoId);
    virtual ~LiveClient();
    virtual Chuck* getElement(int number);
  private:
};

#endif /* LIVECLIENT_HH_ */
