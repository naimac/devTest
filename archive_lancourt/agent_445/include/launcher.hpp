#ifndef _LAUNCHER_HPP_
#define _LAUNCHER_HPP_

#include "agent.hpp"
#include "commonTools.hpp"
#include "iLog.hpp"

class Launcher : public ILauncher
{
 
public:

    Launcher(ILog &p_log, char **envp);
    ~Launcher(void);

    Launcher(const Launcher& p_source) = delete;
    Launcher &operator=(const Launcher& p_source) = delete;
 
    // useless for the moment -> TODO : delete it
    ILauncher::eInit                   init(void);

    // useless for the moment -> TODO : delete it
    ILauncher::eStart                  start(void);

    // Set the running to false
    ILauncher::eStop                   stop(int p_sigNum);

    // Launch a program pointed to by module.name (module define in the include/commonTools.hpp)
    // with its given parameters pointed to by module.parameters
    ILauncher::eLaunchModule           launchModule(Module p_module, pid_t *p_modulePid);

    ILog                                &i_log; 
    char                                **i_envp;
    bool                                i_isLauncherRunning;
 
}; // end class Launcher


#endif