#include <core/event/event.hh>

int BaseEvent::launch(std::vector<boost::any> params)
{
  if (old_event_ != NULL)
    return old_event_->launch(params);
  return 0;
}

BaseEvent *BaseEvent::del(BaseEvent *event)
{
  if (event == this)
  {
    this->exit();
    return old_event_;
  }
  if (old_event_ == NULL)
    return NULL;
  old_event_ = old_event_->del(event);
  return this;
}
