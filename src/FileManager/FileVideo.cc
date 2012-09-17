/*
 * File.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include <core/fileManager/FileVideo.hh>

FileVideo::FileVideo(int videoId)
 : videoId_ (videoId)
{
}

FileVideo::FileVideo()
{
  videoId_ = 0;
}

FileVideo::~FileVideo()
{
}
