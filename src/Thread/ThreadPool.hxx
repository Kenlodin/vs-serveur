/*
 * ThreadPool.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "ThreadPool.hh"
#include "WorkList.hh"

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
    coutDebug("ThreadPool");
    while (true)
    {
      work = WorkList<T>::getInstance().getOneWork();
      (T::getInstance().*(work.worker))
          (work.args.first, work.args.second.first,
              work.args.second.second);
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
// TODO Auto-generated constructor stub
  number_ = number;
  threadPool_ = new ThreadPool::Worker[number];
}

template<class T>
ThreadPool<T>::~ThreadPool()
{
// TODO Auto-generated destructor stub
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
