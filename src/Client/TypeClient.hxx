/*
 * TypeClient.hxx
 *
 *  Created on: 29 avr. 2012
 *      Author: nagriar
 */

#ifndef TYPECLIENT_HXX_
# define TYPECLIENT_HXX_

//Internal include
# include "TypeClient.hh"

inline
int TypeClient::getVideoId() const
{
  return videoId_;
}

inline
FileVideo* TypeClient::getFileVideo() const
{
  return fileVideo_;
}

inline
void TypeClient::setFileVideo(FileVideo* fileVideo)
{
  fileVideo_ = fileVideo;
}

#endif /* TYPECLIENT_HXX_ */
