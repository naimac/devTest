#ifndef _I_OBSERVER_HPP_
#define _I_OBSERVER_HPP_

#include "agent.hpp"

class IObserver
{
 
public:

    enum class                              eInit { SUCCESS, FAILURE };
    virtual eInit                           init(void) = 0;

    enum class                              eStop { SUCCESS, FAILURE };
    virtual eStop                           stop(int p_sigNum) = 0;
 
}; // end class Observer

#endif