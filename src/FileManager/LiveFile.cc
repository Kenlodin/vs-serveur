/*
 * LiveFile.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

// Internal include
#include "LiveFile.hh"

LiveFile::LiveFile(int videoId)
 : FileVideo (videoId)
{
  // TODO Auto-generated constructor stub

}

LiveFile::~LiveFile()
{
  // TODO Auto-generated destructor stub
}

Chunk* LiveFile::getPacket(int number)
{
  packetsMutex.lock();
  std::map<int, Chunk*>::iterator it = packets_.find(number);
  Chunk* chuck = nullptr;
  if (it != packets_.end())
    chuck = it->second;
  packetsMutex.unlock();
  return chuck;
}

void LiveFile::addPacket(int number, Chunk* data)
{
  packetsMutex.lock();
  packets_[number] = data;
  packetsMutex.unlock();
}


