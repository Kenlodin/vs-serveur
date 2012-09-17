#ifndef EVENT_HH_
# define EVENT_HH_

# include <vector>
# include <boost/any.hpp>

class BaseEvent
{
  public:
    virtual int launch(std::vector<boost::any> params) = 0;
};

#endif /* !EVENT_HH_ */
