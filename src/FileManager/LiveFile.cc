/*
 * LiveFile.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

// Internal include
#include <core/fileManager/LiveFile.hh>

LiveFile::LiveFile(int videoId)
    : FileVideo(videoId)
{
}

LiveFile::~LiveFile()
{
}

Chunk* LiveFile::getElement(int number)
{
  packetsMutex_.lock();
  std::map<int, Chunk*>::iterator it = packets_.find(number);
  Chunk* chuck = nullptr;
  if (it != packets_.end())
    chuck = it->second;
  packetsMutex_.unlock();
  return chuck;
}

void LiveFile::setElement(int number, Chunk* data)
{
  packetsMutex_.lock();
  packets_[number] = data;
  forwardPacket(number, data);
  packetsMutex_.unlock();
}

void LiveFile::addServer(boost_socket socketTCP)
{
  linkedServerMutex_.lock();
  //linkedServer_.insert(linkedServer_.end(), socketTCP); TODO FIXIT
  linkedServerMutex_.unlock();
}

void LiveFile::suppServer(boost_socket socketTCP)
{
  linkedServerMutex_.lock();
  //linkedServer_.remove(socketTCP); TODO FIXIT
  linkedServerMutex_.unlock();
}

void LiveFile::forwardPacket(int number, Chunk* data)
{
  linkedServerMutex_.lock();
  Packet packet;
  int16_t opcode = DD::LIVE_DATA;

  packet << opcode;
  packet << getVideoId();
  packet << number;
  packet.Append(data->subChunk_, 8);
  packet.Append(data->subChunk_->data, data->subChunk_->size);
  /*for (boost_socket& sock : linkedServer_) //Todo deco
  {
    sock.Send(packet);
  }*/
  linkedServerMutex_.unlock();
}

