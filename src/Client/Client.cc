/*
 * Client.cpp
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "Client.hh"

Client::Client(sf::SocketTCP& control, sf::SocketUDP& data, int videoId)
: controlSocket_ (control)
, dataSocket_ (data)
, videoId_ (videoId)
{
  // TODO Auto-generated constructor stub

}

Client::~Client()
{
  // TODO Auto-generated destructor stub
  controlSocket_.Close();
  dataSocket_.Close();
  delete fileVideo_;
}

sf::SocketTCP& Client::getControlSocket() const
{
  return controlSocket_;
}

sf::SocketUDP& Client::getDataSocket() const
{
  return dataSocket_;
}

FileVideo* Client::getFileVideo() const
{
  return fileVideo_;
}

void Client::setFileVideo(FileVideo* fileVideo)
{
  this->fileVideo_ = fileVideo;
}

int Client::getVideoId() const
{
  return videoId_;
}

void Client::setVideoId(int videoId)
{
  videoId_ = videoId;
}




