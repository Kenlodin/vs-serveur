/*
 * HandlingSender.hh
 *
 *  Created on: 25 avr. 2012
 *      Author: nagriar
 */

#ifndef HANDLINGSENDER_HH_
# define HANDLINGSENDER_HH_

// Internal include
# include <core/thread/Thread.hh>
# include <core/network/ClientList.hh>
# include <core/thread/Thread.hh>
# include <core/fileManager/Chuck.hh>
# include <core/fileManager/VodFile.hh>
# include <core/fileManager/LiveFile.hh>
# include <core/fwd.hh>
# include <core/diffusion/Diffusion.hh>
# include <core/config/Config.hh>

/**
 * Pool of thread which send data for client
 */
class HandlingSender
{
  public:
    /**
     *  Constructor
     *  @param number number of thread that will be create
     */
    HandlingSender(int number);

    /**
     *  Destructor
     */
    virtual ~HandlingSender();
  public:
    /**
     *  Start every thread in thread pool
     */
    void start();

    /**
     *  Join every thread in thread pool
     */
    void join();

    /**
     *  Represent a thread
     */
    class Worker: public tools::Thread
        {
          public:
            Worker();

            /*
             *  Overload of function run
             */
            void run();
        };
  private:
    // Array of pool of thread
    tools::Thread *threadPool_;

    // Number of threads
    int number_;
};

#endif /* HANDLINGSENDER_HH_ */
