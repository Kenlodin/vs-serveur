/*
 * File.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "FileVideo.hh"

FileVideo::FileVideo(int videoId)
 : videoId_ (videoId)
{
  // TODO Auto-generated constructor stub

}

FileVideo::FileVideo()
{
  videoId_ = 0;
}

FileVideo::~FileVideo()
{
  // TODO Auto-generated destructor stub
}

int FileVideo::getVideoId() const
{
  return videoId_;
}

void FileVideo::setVideoId(int videoId)
{
  videoId_ = videoId;
}


