/*
 * ThreadPool.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef THREADPOOL_HH_
#define THREADPOOL_HH_

# include "Thread.hh"


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

#endif /* THREADPOOL_HH_ */
