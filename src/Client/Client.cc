/*
 * Client.cpp
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include <core/client/Client.hh>

Client::Client( boost::asio::io_service& ioService)
    : privilegeLevel_(10), publicIp_(""), privateIp_(""), token_("")
    , isActiv_(true)
{
    sockets_.push_back(boostIp::tcp::socket(ioService));
}

Client::~Client()
{
    for (boost_socket& sock : sockets_)
    {
        sock.close();
    }
    //TODO delete current action
    using_.unlock();
}

int Client::send(Packet& packet)
{
    /*for (boost_socket sock : sockets)
    {
        sock.send(boost::asio::const_buffer(packet));
    }*/
    return RETURN_VALUE_ERROR;
}
