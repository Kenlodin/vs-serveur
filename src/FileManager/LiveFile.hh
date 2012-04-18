/*
 * LiveFile.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef LIVEFILE_HH_
#define LIVEFILE_HH_

# include "FileVideo.hh"
# include <boost/thread/mutex.hpp>
# include <map>

class LiveFile : public FileVideo
{
  public:
    LiveFile(int videoId);
    virtual ~LiveFile();
    Chuck* getPacket(int number);
    void addPacket(int number, Chuck* data);
  private:
    std::map<int, Chuck*> packets_;
    boost::mutex packetsMutex;
};

#endif /* LIVEFILE_HH_ */
