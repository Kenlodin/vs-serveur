/*
 * FileVideo.hxx
 *
 *  Created on: 29 avr. 2012
 *      Author: nagriar
 */

#ifndef FILEVIDEO_HXX_
# define FILEVIDEO_HXX_

// Internal include
# include "FileVideo.hh"

inline
int FileVideo::getVideoId() const
{
  return videoId_;
}

inline
void FileVideo::setVideoId(int videoId)
{
  videoId_ = videoId;
}

#endif /* FILEVIDEO_HXX_ */
