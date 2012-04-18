/*
 * LiveHandler.h
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef LIVEHANDLER_HH_
#define LIVEHANDLER_HH_

# include "LiveFile.hh"
# include <map>
# include <boost/thread/mutex.hpp>

class LiveHandler
{
  private:
    LiveHandler();
    virtual ~LiveHandler();
  public:
    static LiveHandler& getInstance();
    LiveFile* getLive (int videoId);
    void leaveLive (int videoId);
  private:
    LiveFile* addLive (int videoId);
  private:
    std::map<int, std::pair<LiveFile*, int>> lives_;
    boost::mutex livesMutex;
};

#endif /* LIVEHANDLER_HH_ */
