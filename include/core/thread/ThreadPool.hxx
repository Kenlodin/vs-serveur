/*
 * ThreadPool.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

// Internal include
#include <core/thread/ThreadPool.hh>
#include <core/thread/WorkList.hh>

template<class T>
ThreadPool<T>::Worker::Worker()
{

}

template<class T>
void ThreadPool<T>::Worker::run()
{
  try
  {
    typename WorkList<T>::OneWork work;
    COUTDEBUG("ThreadPool");
    while (Config::getInstance().isOnline())
    {
      if (WorkList<T>::getInstance().getOneWork(work))
      {
        (T::getInstance().*(work.worker))
              (work.args.first, work.args.second.first,
                  work.args.second.second);
      }
      else
        sleep(1);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what();
  }
}

template<class T>
ThreadPool<T>::ThreadPool(int number)
{
  number_ = number;
  threadPool_ = new ThreadPool::Worker[number];
}

template<class T>
ThreadPool<T>::~ThreadPool()
{
}

template<class T>
void ThreadPool<T>::start()
{
  for (int i = 0; i < number_; i++)
  {
    threadPool_[i].start();
  }
}

template<class T>
void ThreadPool<T>::join()
{
  for (int i = 0; i < number_; i++)
  {
    threadPool_[i].join();
  }
}
