/*
 * LiveHandler.cpp
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

//Internal include
#include "LiveHandler.hh"
#include "../SqlManager/SqlManager.hh"

LiveHandler::LiveHandler()
{
  // TODO Auto-generated constructor stub

}

LiveHandler::~LiveHandler()
{
  // TODO Auto-generated destructor stub
}

LiveHandler& LiveHandler::getInstance()
{
  static LiveHandler instance_;

  return instance_;
}

LiveFile* LiveHandler::getLive(int videoId)
{
  COUTDEBUG("New live n° :" << videoId);
  livesMutex.lock();
  std::map<int, std::pair<LiveFile*, int>>::iterator it = lives_.find(videoId);
  LiveFile* live;
  if (it == lives_.end())
  {
    COUTDEBUG("New live link n° :" << videoId);
    live = addLive(videoId);
  }
  else
  {
    live = it->second.first;
    it->second.second++;
  }
  livesMutex.unlock();
  return live;
}

void LiveHandler::leaveLive(int videoId)
{
  COUTDEBUG("End of live n° :" << videoId);
  livesMutex.lock();
  std::map<int, std::pair<LiveFile*, int>>::iterator it = lives_.find(videoId);
  if (it != lives_.end())
  {
    it->second.second--;
    if (it->second.second <= 0)
    {
      COUTDEBUG("End of live deconnection n° :" << videoId);
      lives_.erase(it);
    }
  } // TODO else error
}

LiveFile* LiveHandler::addLive(int videoId)
{
  //TODO
  return nullptr;
}

