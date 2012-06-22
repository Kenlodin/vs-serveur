/*
 * WorkList.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef WORKLIST_HH_
#define WORKLIST_HH_

//External include
# include <string>
# include <list>
# include <boost/thread/mutex.hpp>
# include <SFML/Network.hpp>
# include <map>

/*
 * Represent a list of work thread safe
 */
template<class T>
class WorkList
{
  private: // Private because of singleton
    /**
     *  Constructor
     */
    WorkList();

    /**
     *  Destructor
     */
    ~WorkList();
  public:
    /**
     *  get instance of worklist
     *  @return instance of WorkList
     */
    static WorkList<T>& getInstance();

    /**
     *  typedef of function of worker
     */
    typedef int (T::*Worker)(unsigned int, sf::Packet&, sf::SocketTCP&);

    /**
     *  typedef of arguments
     */
    typedef std::pair<unsigned int, std::pair<sf::Packet, sf::SocketTCP>> ListElt;

    /**
     *  typedef of list of worker
     */
    typedef std::list<Worker> ListFun;

    /**
     *  typedef of list of arguments
     */
    typedef std::list<ListElt> ListArgs;

    /**
     *  typedef of a work
     */
    typedef struct
    {
        Worker worker;
        ListElt args;
    } OneWork;

    /**
     *  Get a work and add it in OneWork
     *  @param onework that will contain work
     *  @return true on success false else
     */
    bool getOneWork(OneWork& onework);

    /**
     *  Put work to list of work
     *  @param worker function that handler this action
     *  @param arg0 first parametter of this function
     *  @param arg1 second parametter
     *  @param arg2 third parametter
     */
    void putWorks(Worker worker, unsigned int arg0, sf::Packet& arg1,
        sf::SocketTCP& arg2);

    /**
     *  Put works to list of work
     *  @param works list of handler
     *  @param args parametter for this handler
     */
    void putWorks(ListFun works, ListArgs args);
  private:
    // Mutex of work_ and args_
    boost::mutex mutex_;

    // List of function
    ListFun work_;

    // List of args
    ListArgs args_;
};

# include "WorkList.hxx"

#endif /* WORKLIST_HH_ */
