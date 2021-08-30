#ifndef _I_LAUNCHER_HPP_
#define _I_LAUNCHER_HPP_

#include "agent.hpp"

class ILauncher
{
 
public:

    enum class                        eInit { SUCCESS, FAILURE };
    virtual eInit                     init(void)  = 0;  

    enum class                        eStart { SUCCESS, FAILURE };
    virtual eStart                    start(void) = 0;

    enum class                        eStop { SUCCESS, FAILURE };
    virtual eStop                     stop(int p_sigNum)  = 0;

    enum class                        eLaunchModule { SUCCESS, FAILURE };
    virtual eLaunchModule             launchModule(Module p_module, pid_t *p_modulePid) = 0;

}; // end class Launcher

#endif