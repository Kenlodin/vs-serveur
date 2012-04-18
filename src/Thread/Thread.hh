/* 
 * File:   Thread.hh
 * Author: Aymeric
 *
 * Created on 18 avril 2012, 01:40
 */

#ifndef THREAD_HH
#define	THREAD_HH

#include <boost/thread.hpp>

namespace tools
{

  class Thread
  {
    
   public:
    ///
    /// Constructor & Destructor
    ///
    Thread ();
    virtual ~Thread ();
    
   public:
    ///
    /// Function 
    ///
    void start ();
    virtual void run ();
    void join ();
    
    
   private:
    //std::shared_ptr<boost::thread> t_;
    boost::thread t_;
    

  } ;
}
#endif	/* THREAD_HH */

