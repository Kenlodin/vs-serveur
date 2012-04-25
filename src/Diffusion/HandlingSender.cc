/*
 * HandlingSender.cc
 *
 *  Created on: 25 avr. 2012
 *      Author: nagriar
 */

#include "HandlingSender.hh"
#include "../SqlManager/SqlManager.hh"

HandlingSender::HandlingSender(int number)
{
  number_ = number;
  threadPool_ = new Worker[number];
}

HandlingSender::~HandlingSender()
{
  // TODO Auto-generated destructor stub
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
  sql_result res = SqlManager::getInstance().getNextsHandlings(0); //TODO severId
  for (unsigned int i = 0; i < res.size(); i++)
  {
    sql_tuple t = res.at(i);
    begin = atoi(t["packet_begin"].c_str());
    end = atoi(t["packet_end"].c_str());
    token = t["client_token"].c_str();
    client = ClientList::getInstance().getClient(token);
    if (client == nullptr || client->getDataSocket() == nullptr) // TODO Error
      continue;
    if (begin == 0)
    {
      FileVideo* video = client->getTypeClient()->getFileVideo();
      for (int i = avifile::e_opcode::OPCODE_RIFF_AVI; i < 5; i++)
        Diffusion::getInstance().dcData(*(client->getDataSocket()), i,
            video->getFileHeader()[i]);
    }
    for (int nbPacket = begin; nbPacket < end; i++)
    {
      Chuck* chuck = client->getTypeClient()->getElement(nbPacket);
      Diffusion::getInstance().dcData(*(client->getDataSocket()), chuck);
    }
  }

}

void HandlingSender::join()
{
  for (int i = 0; i < number_; i++)
    threadPool_[i].join();
}
