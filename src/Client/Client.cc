/*
 * Client.cpp
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "Client.hh"

Client::Client(sf::SocketTCP*& control, sf::SocketTCP*& data)
: controlSocket_ (control)
, dataSocket_ (data)
{
  // TODO Auto-generated constructor stub

}

Client::~Client()
{
  // TODO Auto-generated destructor stub
  controlSocket_->Close();
  dataSocket_->Close();
  delete controlSocket_;
  delete dataSocket_;
}

sf::SocketTCP* Client::getControlSocket() const
{
  return controlSocket_;
}

sf::SocketTCP* Client::getDataSocket() const
{
  return dataSocket_;
}

int Client::sendControl(sf::Packet& packet)
{
  if (controlSocket_->Send(packet) != sf::Socket::Status::Done)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

int Client::sendData(sf::Packet& packet)
{
  if (dataSocket_->Send(packet) != sf::Socket::Status::Done)
    return RETURN_VALUE_ERROR;
  return RETURN_VALUE_GOOD;
}

void Client::setDataSocket(sf::SocketTCP* dataSocket)
{
  dataSocket_ = dataSocket;
}


