/*
 * Client.cpp
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "Client.hh"

Client::Client(sf::SocketTCP control, sf::SocketTCP*& data, std::string token)
    : controlSocket_(control), dataSocket_(data), token_(token)
{
}

Client::~Client()
{
  if (controlSocket_.IsValid())
  {
    controlSocket_.Close();
  }
  if (dataSocket_ != nullptr && dataSocket_->IsValid())
    dataSocket_->Close();
  delete dataSocket_;
  using_.unlock();
}

int Client::sendControl(sf::Packet& packet)
{
  if (controlSocket_.Send(packet) != sf::Socket::Status::Done)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Client::sendData(sf::Packet& packet)
{
  if (dataSocket_->Send(packet) != sf::Socket::Status::Done)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}
