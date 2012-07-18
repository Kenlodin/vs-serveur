#ifndef EVENT_AUTH_HH_
# define EVENT_AUTH_HH_

# ifdef CORE__

#  include <core/event/event.hh>

class EventAuth : public BaseEvent
{
  public:
    virtual void launch(std::vector<boost::any> params);
};

# endif /* !CORE__ */

#endif /* !EVENT_AUTH_HH_ */
