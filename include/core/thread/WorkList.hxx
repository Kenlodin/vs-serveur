/*
 * WorkList.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include <core/thread/WorkList.hh>

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
bool WorkList<T>::getOneWork(WorkList<T>::OneWork& oneWork)
{
  mutex_.lock();
  bool retValue = false;
  if (!work_.empty())
  {
    oneWork.worker = *(work_.begin());
    work_.pop_front();
    oneWork.args = *(args_.begin());
    args_.pop_front();
    retValue = true;
  }
  mutex_.unlock();
  if (retValue)
    COUTDEBUG("OneWorkGet");
  return retValue;
}

template<class T>
void WorkList<T>::putWorks(Worker worker, unsigned int arg0, Packet& arg1,
    Client*& arg2)
{
  COUTDEBUG("OneWorkPut : begin");
  mutex_.lock();
  std::pair<Packet, Client*> second = std::pair<Packet,
      Client*>(arg1, arg2);
  ListElt elt = ListElt(arg0, second);
  work_.push_back(worker);
  args_.push_back(elt);
  mutex_.unlock();
  COUTDEBUG("OneWorkPut : end");
}

template<class T>
void WorkList<T>::putWorks(ListFun works, ListArgs args)
{
  mutex_.lock();
  work_.splice(work_.end(), works);
  args_.splice(args_.end(), args);
  mutex_.unlock();
}

