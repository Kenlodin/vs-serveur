/*
 * ThreadPool.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef THREADPOOL_HH_
#define THREADPOOL_HH_

# include "Thread.hh"

template <class T>
class ThreadPool
{
  public:
    ThreadPool(int number);
    virtual ~ThreadPool();
    void start();
    void join();
  private:
    class Worker: public tools::Thread
    {
      public:
        Worker();
        void run();
    };
  private:
    tools::Thread *threadPool_;
    int number_;
};

# include "ThreadPool.hxx"

#endif /* THREADPOOL_HH_ */
