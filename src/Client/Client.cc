/*
 * Client.cpp
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "Client.hh"

Client::Client(sf::SocketTCP& control, sf::SocketTCP& data, int videoId)
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

sf::SocketTCP& Client::getDataSocket() const
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

int Client::sendControl(sf::Packet& packet)
{
  if (controlSocket_.Send(packet) != sf::Socket::Status::Done)
    return TRUE;
  return FALSE;
}

int Client::sendData(sf::Packet& packet)
{
  if (dataSocket_.Send(packet) != sf::Socket::Status::Done)
    return TRUE;
  return FALSE;
}


