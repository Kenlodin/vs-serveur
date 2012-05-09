/*
 * LiveClient.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef LIVECLIENT_HH_
# define LIVECLIENT_HH_

// Internal Include
# include "TypeClient.hh"

/*
 * This class implement TypeClient interface to provide method
 * to get Chuck for live client
 */
class LiveClient: public TypeClient
{
  public:
    // Constructor
    LiveClient(int videoId);

    // Destructor
    virtual ~LiveClient();

    // Get Chuck represented by number
    virtual Chunk* getElement(int number);
};

//Inline get/set
# include "LiveClient.hxx"

#endif /* LIVECLIENT_HH_ */
