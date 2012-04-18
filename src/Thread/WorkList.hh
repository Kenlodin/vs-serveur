/*
 * WorkList.hh
 *
 *  Created on: 18 avr. 2012
 *      Author: nagriar
 */

#ifndef WORKLIST_HH_
#define WORKLIST_HH_

# include <string>
# include <list>
# include <boost/thread/mutex.hpp>

class WorkList
{
  private:
    WorkList();
    ~WorkList();
  public:
    static WorkList& getInstance();

    std::string getOneWork();
    void putWorks(std::string work);
    void putWorks(std::list<std::string> works);
  private:
    boost::mutex mutex_;
    std::list<std::string>* work_;
};

#endif /* WORKLIST_HH_ */
