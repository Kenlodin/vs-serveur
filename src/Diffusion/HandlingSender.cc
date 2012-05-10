/*
 * HandlingSender.cc
 *
 *  Created on: 25 avr. 2012
 *      Author: nagriar
 */

// Internal include
#include "HandlingSender.hh"
#include "../SqlManager/SqlManager.hh"


HandlingSender::HandlingSender(int number)
{
  number_ = number;
  threadPool_ = new Worker[number];
}

HandlingSender::~HandlingSender()
{
  delete[] threadPool_;
}

void HandlingSender::start()
{
  for (int i = 0; i < number_; i++)
    threadPool_[i].start();
}

HandlingSender::Worker::Worker()
{
}

void HandlingSender::Worker::run()
{
  Client* client;
  int begin;
  int end;
  std::string token;
  sql_result res = SqlManager::getInstance().getNextsHandlings(
      Config::getInstance ().getInt ("server_id"));
  for (unsigned int i = 0; i < res.size(); i++)
  {
    COUTDEBUG(("Get Work to send data"));
    sql_tuple t = res.at(i);
    begin = atoi(t["packet_begin"].c_str());
    end = atoi(t["packet_end"].c_str());
    token = t["client_token"].c_str();
    client = ClientList::getInstance().getClient(token);
    if (client == nullptr)
    {
      COUTDEBUG(("No client with token = " + token));
      continue;
    }
    if (client->getDataSocket() == nullptr) // TODO Error
    {
      COUTDEBUG(("No data socket on client : " + token));
      client->unlock();
      continue;
    }
    if (client->getTypeClient() == nullptr
        || client->getTypeClient()->getFileVideo() == nullptr) // TODO Error
        {
          COUTDEBUG(("No video type on client : " + token));
          client->unlock();
          continue;
        }
    if (begin == 0) // TODO Live
    {
      COUTDEBUG("Send header n° :" << begin << " to " + token);
      FileVideo* video = client->getTypeClient()->getFileVideo();
      for (int i = avifile::e_opcode::AVI_RIFF_AVI; i < 5; i++)
        Diffusion::getInstance().dcData(*(client->getDataSocket()), i,
            video->getFileHeader()[i]);
    }
    for (int nbPacket = begin; nbPacket < end; i++)
    {
      COUTDEBUG("Send packet n° " << nbPacket << " to " << token);
      Chunk* chuck = client->getTypeClient()->getElement(nbPacket);
      Diffusion::getInstance().dcData(*(client->getDataSocket()), nbPacket, chuck);
    }
    client->unlock();
  }

}

void HandlingSender::join()
{
  for (int i = 0; i < number_; i++)
    threadPool_[i].join();
}

