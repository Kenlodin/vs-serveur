/*
 * LiveHandler.h
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef LIVEHANDLER_HH_
# define LIVEHANDLER_HH_

//External include
# include <map>
# include <boost/thread/mutex.hpp>

//Internal include
# include "LiveFile.hh"

/*
 * Manage live in/output
 */
class LiveHandler
{
  private: // Private because of singleton
    //Constructor
    LiveHandler();

    // Destructor
    virtual ~LiveHandler();
  public:
    // Get instance of LiveHandler
    static LiveHandler& getInstance();

    // Get a live
    LiveFile* getLive (int videoId);

    // Leave a live
    void leaveLive (int videoId);
  private:
    // Link this server with a live server
    LiveFile* addLive (int videoId);
  private:
    // Reference every live
    std::map<int, std::pair<LiveFile*, int>> lives_;
    // Mutex for lives_
    boost::mutex livesMutex;
};

#endif /* LIVEHANDLER_HH_ */
