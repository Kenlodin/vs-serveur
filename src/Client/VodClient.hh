/*
 * VodClient.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef VODCLIENT_HH_
# define VODCLIENT_HH_

// Internal include
# include "TypeClient.hh"
# include "../FileManager/VodFile.hh"
# include "../FileManager/Chuck.hh"

/*
 * Class which implément TypeClient interface for VODclient
 */
class VodClient : public TypeClient
{
  public:
    // Constructor
    VodClient(int videoId);

    // Destructor
    virtual ~VodClient();

    // Get chuck represent by number
    virtual Chunk* getElement(int number);
};

#endif /* VODCLIENT_HH_ */
