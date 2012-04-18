/*
 * ThreadPool.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "ThreadPool.hh"
#include "WorkList.hh"

ThreadPool::Worker::Worker()
{

}

void ThreadPool::Worker::run()
{
  try
  {
    std::string work;
    while (true)
    {
       work = WorkList::getInstance().getOneWork();
       std::cout << work << std::endl;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what();
  }
}

ThreadPool::ThreadPool(int number)
{
// TODO Auto-generated constructor stub
  number_ = number;
  threadPool_ = new ThreadPool::Worker[number];
}

ThreadPool::~ThreadPool()
{
// TODO Auto-generated destructor stub
}



void ThreadPool::start()
{
  for (int i = 0; i < number_; i++)
  {
    threadPool_[i].start();
  }
}

void ThreadPool::join ()
{
  for (int i = 0; i < number_; i++)
  {
    threadPool_[i].join();
  }
}
