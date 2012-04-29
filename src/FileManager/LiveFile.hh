/*
 * LiveFile.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef LIVEFILE_HH_
# define LIVEFILE_HH_

// External include
# include <boost/thread/mutex.hpp>
# include <map>

// Internal include
# include "FileVideo.hh"

/*
 * Virtual file that represent a live
 */
class LiveFile : public FileVideo
{
  public:
    LiveFile(int videoId);

    // Destructor
    virtual ~LiveFile();

    // Get packet
    Chunk* getPacket(int number);

    // Insert a new packet
    void addPacket(int number, Chunk* data);
  private:
    // Contain every live packet.
    std::map<int, Chunk*> packets_;

    // Mutex for packets_
    boost::mutex packetsMutex;
};

#endif /* LIVEFILE_HH_ */
