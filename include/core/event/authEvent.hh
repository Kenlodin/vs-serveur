#ifndef EVENT_AUTH_HH_
# define EVENT_AUTH_HH_

# ifdef CORE__

#  include <SFML/Network.hpp>
#  include <core/event/event.hh>
#  include <core/sqlManager/SqlManager.hh>
#  include <core/network/ClientList.hh>
#  include <core/tracker/Tracker.hh>

class EventAuth : public BaseEvent
{
  public:
    virtual int launch(std::vector<boost::any> params);
};

# endif /* !CORE__ */

#endif /* !EVENT_AUTH_HH_ */
