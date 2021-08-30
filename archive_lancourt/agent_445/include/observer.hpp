#ifndef _OBSERVER_HPP_
#define _OBSERVER_HPP_

#include "agent.hpp"
#include "iLog.hpp"

class Observer : public IObserver
{
 
public:

    Observer(ILog &p_log);
    ~Observer(void);

    Observer(const Observer& p_source) = delete;
    Observer &operator=(const Observer& p_source) = delete;

    // useless for the moment -> TODO : delete it
    IObserver::eInit                init(void);  

    // useless for the moment -> TODO : delete it
    IObserver::eStop                stop(int p_sigNum);
 
private:
    
    ILog                           &i_log;
    bool                           i_isObserverRunning;
 
}; // end class Observer

#endif