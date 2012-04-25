/*
 * HandlingSender.hh
 *
 *  Created on: 25 avr. 2012
 *      Author: nagriar
 */

#ifndef HANDLINGSENDER_HH_
#define HANDLINGSENDER_HH_

# include "../Thread/Thread.hh"
# include "../Network/ClientList.hh"
# include "../Thread/Thread.hh"
# include "../FileManager/Chuck.hh"
# include "../fwd.hh"
# include "Diffusion.hh"

class HandlingSender
{
  public:
    HandlingSender(int number);
    virtual ~HandlingSender();
  public:
    void start();
    void join();
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

#endif /* HANDLINGSENDER_HH_ */
