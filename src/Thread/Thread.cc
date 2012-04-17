/* 
 * File:   Thread.cc
 * Author: Aymeric
 * 
 * Created on 18 avril 2012, 01:40
 */

#include "Thread.hh"
namespace tools
{
  ///
  /// Constructor & Destructor
  ///
  
  Thread::Thread ()
  {
  }

  Thread::Thread (const Thread& orig)
  {
  }

  Thread::~Thread ()
  {
  }

  ///
  ///
  ///
  
  Thread::start ()
  {
    t (run);
  }
}
