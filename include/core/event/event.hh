#ifndef EVENT_HH_
# define EVENT_HH_

# include <vector>
# include <boost/any.hpp>
# include <core/module/baseModule.hh>

class BaseEvent : public BaseModule
{
  public:
    virtual int launch(std::vector<boost::any> params);
    BaseEvent *del(BaseEvent *event);

  protected:
    BaseEvent *old_event_;
};

#endif /* !EVENT_HH_ */
