#include <core/event/eventManager.hh>

EventManager *EventManager::instance_ = NULL;
EventManager *EventManager::getInstance()
{
  if (instance_ == NULL)
    instance_ = new EventManager();
  return instance_;
}

BaseEvent *EventManager::setEvent(e_event ev, BaseEvent *event)
{
  BaseEvent *ret = NULL;
  
  if (events.find(ev) != events.end())
    ret = events[ev];
  events[ev] = event;
  return ret;
}
