/*
 * WorkList.cc
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#include "WorkList.hh"

WorkList::WorkList()
    : mutex_()
{
  work_ = new std::list<std::string>;

}

WorkList::~WorkList()
{
  delete work_;
}

WorkList& WorkList::getInstance()
{
  static WorkList instance_;

  return instance_;
}

std::string WorkList::getOneWork()
{
  mutex_.lock();
  std::string work = work_->front();
  work_->pop_front();
  mutex_.unlock();
  return work;
}

void WorkList::putWorks(std::string work)
{
  mutex_.lock();
  work_->push_back(work);
  mutex_.unlock();
}

void WorkList::putWorks(std::list<std::string> works)
{
  mutex_.lock();
  work_->splice(work_->begin(), works);
  mutex_.unlock();
}

