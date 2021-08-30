#ifndef _STOPPER_HPP_
#define _STOPPER_HPP_

#include "agent.hpp"
#include "iStopper.hpp"
#include "iLog.hpp"

class Stopper : public IStopper
{
 
public:
    Stopper(ILog &p_log);
    ~Stopper(void);

    Stopper &operator=(const Stopper& p_source) = delete;
    Stopper(const Stopper& p_source) = delete;
 
    // useless for the moment -> TODO : delete it
    IStopper::eInit              init(void);

    // Kill a pid with the SIGTERM (15) signal 
    IStopper::eStopModule        stopModule(std::list<pid_t> p_modulePidList);

private:

    ILog                                &i_log;
    bool                                i_isStopRunning; // a little dumb and useless
 
}; // end class Stopper


#endif