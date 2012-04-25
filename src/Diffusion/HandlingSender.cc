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
  sql_result res = SqlManager::getInstance().getNextsHandlings(0); //TODO severId


}

void HandlingSender::join()
{
  for (int i = 0; i < number_; i++)
    threadPool_[i].join();
}


