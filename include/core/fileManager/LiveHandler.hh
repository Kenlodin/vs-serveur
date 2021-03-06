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
# include <core/fileManager/LiveFile.hh>

/*
 * Manage live in/output
 */
class LiveHandler
{
  private: // Private because of singleton
    /**
     * Constructor
     */
    LiveHandler();

    /**
     *  Destructor
     */
    virtual ~LiveHandler();
  public:
    /**
     *  Get instance of LiveHandler
     *  @return instance of this class
     */
    static LiveHandler& getInstance();

    /**
     *  Get a live
     *  @param videoId id of live needed
     *  @return LiveFile that represent the live
     */
    LiveFile* getLive (int videoId);

    /**
     *  Leave a live
     *  @param videoId of live got
     */
    void leaveLive (int videoId);
  private:
    /**
     *  Link this server with a live server
     *  @param videoId that represent the live
     *  @return LiveFile created and linked
     */
    LiveFile* addLive (int videoId);
  private:
    // Reference every live
    std::map<int, std::pair<LiveFile*, int>> lives_;
    // Mutex for lives_
    boost::mutex livesMutex;
};

#endif /* LIVEHANDLER_HH_ */
