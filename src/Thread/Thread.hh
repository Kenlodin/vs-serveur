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

  /**
   * La classe thread permet de lancer des threads aussi facilement qu'en Java.
   * Il suffit d'hériter de cette classe, d'override la fonction run() et
   * d'appeller la fonction start.
   * Cette classe utilise les threads de la bibliothèque boost
   */
  class Thread
  {
    
   public:
    /**
     * Constructor
     */
    Thread ();
    
    /**
     * Destructor
     */
    virtual ~Thread ();
    
   public:
    /**
     * Cette fonction permet de lancer le thread.
     */
    void start ();
    
    /**
     * Cette fonction doit être overrider par la classe fille. C'est en quelque
     * sort le "point d'entrée" du thread.
     */
    virtual void run () {};
    
    /**
     * Cette fonction attends la fin de l'execution du thread.
     */
    void join ();
    
    /**
     * Cette fonction permet de savoir si le thread est en cours d'execution.
     * @return bool
     */
    bool joinable ();
    
    /**
     * Cette fonction permet de demander l'interruption d'un thread selon
     * certaines conditions. Pour plus d'infos regarder la doc de boost.thread
     */
    void interrupt ();
    
    /**
     * Permet de savoir si le thread à une demande d'interruption en cours.
     * @return bool
     */
    bool interruption_requested ();

   private:
    boost::thread t_;
    

  } ;
}
#endif	/* THREAD_HH */

