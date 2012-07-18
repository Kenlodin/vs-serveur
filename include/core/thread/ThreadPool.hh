/*
 * ThreadPool.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef THREADPOOL_HH_
# define THREADPOOL_HH_

// Internal include
# include <core/thread/Thread.hh>

/*
 * Class which manage a pool of thread
 */
template <class T>
class ThreadPool
{
  public:
    /**
     *  Constructor
     *  @param number of thread created
     */
    ThreadPool(int number);

    /**
     *  Destructor
     */
    virtual ~ThreadPool();

    /**
     *  Start every thread
     */
    void start();

    /**
     *  Join every thread
     */
    void join();
  private:
    /**
     *  Represent a thread
     */
    class Worker: public tools::Thread
    {
      public:
        Worker();

        /**
         * Overloading of function of thread
         */
        void run();
    };
  private:
    // Array of thread
    tools::Thread *threadPool_;

    // Number of thread
    int number_;
};

# include <core/thread/ThreadPool.hxx>

#endif /* THREADPOOL_HH_ */
