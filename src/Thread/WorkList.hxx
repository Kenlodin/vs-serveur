/*
 * WorkList.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "WorkList.hh"

template<class T>
WorkList<T>::WorkList()
    : mutex_()
{

}

template<class T>
WorkList<T>::~WorkList()
{
}

template<class T>
WorkList<T>& WorkList<T>::getInstance()
{
  static typename WorkList<T>::WorkList instance_;

  return instance_;
}

template<class T>
typename WorkList<T>::OneWork WorkList<T>::getOneWork()
{
  mutex_.lock();
  OneWork oneWork;
  oneWork.worker = *(work_.begin());
  work_.pop_front();
  oneWork.args = *(args_.begin());
  args_.pop_front();
  mutex_.unlock();
  return oneWork;
}

template<class T>
void WorkList<T>::putWorks(Worker worker, unsigned int arg0, sf::Packet& arg1,
    sf::SocketTCP& arg2)
{
  mutex_.lock();
  std::pair<sf::Packet, sf::SocketTCP> second = std::pair<sf::Packet,
      sf::SocketTCP>(arg1, arg2);
  ListElt elt = ListElt(arg0, second);
  work_.push_back(worker);
  args_.push_back(elt);
  mutex_.unlock();
}

template<class T>
void WorkList<T>::putWorks(ListFun works, ListArgs args)
{
  mutex_.lock();
  work_.splice(work_.begin(), works);
  args_.splice(args_.begin(), args);
  mutex_.unlock();
}
