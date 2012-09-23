/*
 * HandlingSender.cc
 *
 *  Created on: 25 avr. 2012
 *      Author: nagriar
 */

// Internal include
#include <core/diffusion/HandlingSender.hh>
#include <core/sqlManager/SqlManager.hh>


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
  while (Config::getInstance ().isOnline ())
  {
    Client* client;
    int begin;
    int end;
    std::string token;
    sql_result res = SqlManager::getInstance().getNextsHandlings(
        Config::getInstance ().getInt ("server_id"));
    for (unsigned int i = 0; i < res.size(); i++)
    {
      //COUTDEBUG(("Get Work to send data"));
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
      if (client->getTypeClient() == nullptr)
      {
        COUTDEBUG(("No video type on client : " + token));
        client->setTypeClient(new VodFile(atoi(t["file_id"].c_str()))); //TODO Live OUTPUT
      }
      if (begin == 0) // TODO Live problem
      {
        //COUTDEBUG("Send header no :" << begin << " to " + token);
        FileVideo* video = client->getTypeClient();
        for (int i = avifile::e_opcode::AVI_RIFF_AVI; i < 5; i++)
          Diffusion::getInstance().dcData(client,i , i,
              video->getFileHeader()[i]);
      }
      for (int nbPacket = begin; nbPacket <= end; nbPacket++)
      {
        //COUTDEBUG("Send packet no " << nbPacket << " to " << token);
        Chunk* chunk = client->getTypeClient()->getElement(nbPacket);
        Diffusion::getInstance().dcData(client, nbPacket + 5, chunk);
	delete chunk;
      }
      client->unlock();
    }
  if (res.size() == 0)
  sleep(2);
  }
}

void HandlingSender::join()
{
  for (int i = 0; i < number_; i++)
    threadPool_[i].join();
}

