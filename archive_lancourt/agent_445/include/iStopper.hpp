#ifndef _I_STOPPER_HPP_
#define _I_STOPPER_HPP_

#include "agent.hpp"

class IStopper
{
 
public:

    enum class                              eInit { SUCCESS, FAILURE };
    virtual eInit                           init(void) = 0;

    enum class                              eStopModule { SUCCESS, FAILURE };
    virtual eStopModule                     stopModule(std::list<pid_t> p_modulePidList) = 0;
 
}; // end class Stopper


#endif