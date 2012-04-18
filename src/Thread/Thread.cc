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
  
  void Thread::start ()
  {
    t_ = boost::thread(&Thread::run, this);
  }
  
  void Thread::run ()
  {
    std::cout << "Coucou !" << std::endl;
  }
  
  void Thread::join ()
  {
    t_.join ();
  }
}
