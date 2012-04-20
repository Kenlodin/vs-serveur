/*
 * TypeClient.cc
 *
 *  Created on: 19 avr. 2012
 *      Author: nagriar
 */

#include "TypeClient.hh"

TypeClient::TypeClient(int videoId)
 : videoId_ (videoId)
{
  // TODO Auto-generated constructor stub

}

TypeClient::~TypeClient()
{
  // TODO Auto-generated destructor stub
}

int TypeClient::getVideoId() const
{
  return videoId_;
}

void TypeClient::setVideoId(int videoId)
{
  videoId_ = videoId;
}

FileVideo* TypeClient::getFileVideo() const
{
  return fileVideo_;
}

void TypeClient::setFileVideo(FileVideo* fileVideo)
{
  fileVideo_ = fileVideo;
}


