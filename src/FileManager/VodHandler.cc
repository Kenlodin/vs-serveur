/*
 * VodHandler.cc
 *
 *  Created on: 1 mai 2012
 *      Author: nagriar
 */

#include "VodHandler.hh"

VodHandler::VodHandler()
{
}

VodHandler::~VodHandler()
{
}

VodHandler& VodHandler::getInstance()
{
  static VodHandler instance_;

  return instance_;
}

VodFile* VodHandler::getVod(int videoId)
{
  COUTDEBUG("New VOD n° :" << videoId);
  vodsMutex.lock();
  std::map<int, std::pair<VodFile*, int>>::iterator it = vods_.find(videoId);
  VodFile* vod;
  if (it == vods_.end())
  {
    COUTDEBUG("Open VOD n° :" << videoId);
    vod = addVod(videoId);
  }
  else
  {
    vod = it->second.first;
    it->second.second++;
  }
  vodsMutex.unlock();
  return vod;
}

void VodHandler::leaveVod(int videoId)
{
  COUTDEBUG("End VOD n° :" << videoId);
  vodsMutex.lock();
    std::map<int, std::pair<VodFile*, int>>::iterator it = vods_.find(videoId);
    if (it != vods_.end())
    {
      it->second.second--;
      if (it->second.second <= 0)
      {
        COUTDEBUG("Close VOD n° :" << videoId);
        vods_.erase(it);
      }
    } // TODO else error
}


VodFile* VodHandler::addVod(int videoId)
{
  std::pair<VodFile*, int> element (new VodFile(videoId), 1);
  vods_.insert(std::pair<int,std::pair<VodFile*, int>>(videoId
      , element));

  return element.first;
}
