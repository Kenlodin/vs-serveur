#ifndef BASE_MODULE_HH_
# define BASE_MODULE_HH_

/*
 * BaseModule is the interface between core and module
 */

class BaseModule
{

  public:
    virtual void init() {};
    virtual void exit() {};

};

#endif /* !BASE_MODULE_HH_ */
