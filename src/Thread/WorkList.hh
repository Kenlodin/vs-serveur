/*
 * WorkList.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef WORKLIST_HH_
#define WORKLIST_HH_

# include <string>
# include <list>
# include <boost/thread/mutex.hpp>
# include <SFML/Network.hpp>
# include <map>

template<class T>
class WorkList
{
  private:
    WorkList();
    ~WorkList();
  public:
    static WorkList<T>& getInstance();
    typedef int (T::*Worker)(unsigned int, sf::Packet&, sf::SocketTCP&);
    typedef std::pair<unsigned int, std::pair<sf::Packet, sf::SocketTCP>> ListElt;
    typedef std::list<Worker> ListFun;
    typedef std::list<ListElt> ListArgs;
    typedef struct
    {
        Worker worker;
        ListElt args;
    } OneWork;
    OneWork getOneWork();
    void putWorks(Worker worker, unsigned int arg0, sf::Packet& arg1,
        sf::SocketTCP& arg2);
    void putWorks(ListFun works, ListArgs args);
  private:
    boost::mutex mutex_;
    ListFun work_;
    ListArgs args_;
};

# include "WorkList.hxx"

#endif /* WORKLIST_HH_ */
