/*
 * HandlingSender.hh
 *
 *  Created on: 25 avr. 2012
 *      Author: nagriar
 */

#ifndef HANDLINGSENDER_HH_
# define HANDLINGSENDER_HH_

// Internal include
# include "../Thread/Thread.hh"
# include "../Network/ClientList.hh"
# include "../Thread/Thread.hh"
# include "../FileManager/Chuck.hh"
# include "../FileManager/VodFile.hh"
# include "../FileManager/LiveFile.hh"
# include "../fwd.hh"
# include "Diffusion.hh"
# include "../Config/Config.hh"

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
