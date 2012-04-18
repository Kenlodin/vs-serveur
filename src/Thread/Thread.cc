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

  Thread::~Thread ()
  {
  }

  ///
  ///
  ///

  void
  Thread::start ()
  {
    t_ = boost::thread (&Thread::run, this);
  }

  void
  Thread::join ()
  {
    t_.join ();
  }

  bool
  Thread::joinable ()
  {
    return t_.joinable ();
  }

  void
  Thread::interrupt ()
  {
    t_.interrupt ();
  }

  bool
  Thread::interruption_requested ()
  {
    return t_.interruption_requested ();
  }
}
