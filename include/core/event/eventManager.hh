#ifndef EVENTMANAGER_HH_ 
# define EVENTMANAGER_HH_ 

# include <map>

# include <core/event/event.hh>

typedef enum
{
  AUTH_MASTER
} e_event;

class EventManager
{
  public:
    static EventManager *getInstance();

    BaseEvent *setEvent(e_event ev, BaseEvent *event);

  private:
    static EventManager *instance_;
    std::map<e_event, BaseEvent*>     events;
};

#endif /* !EVENTMANAGER_HH_ */
