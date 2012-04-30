/*
 * VodHandler.hh
 *
 *  Created on: 1 mai 2012
 *      Author: nagriar
 */

#ifndef VODHANDLER_HH_
# define VODHANDLER_HH_

// External include
# include <boost/thread/mutex.hpp>

// Internal include
# include "VodFile.hh"

class VodHandler
{
  private: // Private because of singleton
      //Constructor
      VodHandler();

      // Destructor
      virtual ~VodHandler();
    public:
      // Get instance of LiveHandler
      static VodHandler& getInstance();

      // Get a live
      VodFile* getVod (int videoId);

      // Leave a live
      void leaveVod (int videoId);
    private:
      // Link this server with a live server
      VodFile* addVod (int videoId);
    private:
      // Reference every vod file
      std::map<int, std::pair<VodFile*, int>> vods_;
      // Mutex for vods_
      boost::mutex vodsMutex;
};

#endif /* VODHANDLER_HH_ */
