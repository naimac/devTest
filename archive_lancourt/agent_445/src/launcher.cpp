#include "launcher.hpp"

#include <unistd.h>

Launcher::Launcher(ILog &p_launcherLog, char **p_envp) : i_log(p_launcherLog), i_envp(p_envp)
{
    i_log.log(LOG_INFO, "Launcher::%s", __func__);
}

Launcher::~Launcher()
{
    i_log.log(LOG_INFO, "Launcher::%s", __func__);
}

// useless for the moment -> TODO : delete it
ILauncher::eInit        Launcher::init()
{
    i_log.log(LOG_INFO, "Launcher::%s", __func__);
    return ILauncher::eInit::SUCCESS;
}

// useless for the moment -> TODO : delete it
ILauncher::eStart        Launcher::start()
{
    i_log.log(LOG_INFO, "Launcher::%s", __func__);
    // todo if usefull
    return ILauncher::eStart::SUCCESS;
}

/**
 * @brief
 * Set the running to false
 * 
 * @param p_sigNum 
 * @return ILauncher::eStop 
 */
ILauncher::eStop         Launcher::stop(int p_sigNum)
{
    i_log.log(LOG_INFO, "Launcher::%s [%i]", __func__, p_sigNum);
    i_isLauncherRunning = false;
    return ILauncher::eStop::SUCCESS;
}

/**
 * rbrief
 * Launch a program pointed to by module.name 
 * with its given parameters pointed to by module.parameters
 * 
 * @param p_module 
 * @param p_modulePid 
 * @return ILauncher::eLaunchModule 
 */
ILauncher::eLaunchModule         Launcher::launchModule(Module p_module, pid_t *p_modulePid)
{
    i_log.log(LOG_INFO, "Launcher::%s , module pid : %d", __func__, p_modulePid);
    
    // local array variable needed as parameter for execve syscall
    char            *l_param[3];

    l_param[0] = (char *)p_module.name.c_str();
    l_param[1] = (char *)p_module.parameters.c_str();
    l_param[2] = nullptr; // 1. RTFM , 2. if you pass an array to a method, without giving its size ... how the method is suppose to know the end of the array ? ... so "nullptr"

    i_log.log(LOG_INFO, "Fork execution");
    *p_modulePid = fork();
    i_log.log(LOG_INFO, "After fork, fork pid_t : %i", *p_modulePid);

    if (*p_modulePid == 0) // child process
    {
        // success;
        i_log.log(LOG_INFO, "execve execution");
        if ((execve(l_param[0], l_param, i_envp)) == -1)
        {
            i_log.log(LOG_INFO, "tata execve fail");
            return ILauncher::eLaunchModule::FAILURE;
        }
        i_log.log(LOG_INFO, "execve succeed");
        return ILauncher::eLaunchModule::SUCCESS;
    }
    else if (*p_modulePid > 0) // parent process
    {
        // do nothing
    }
    else if (*p_modulePid < 0) // error
    {
        i_log.log(LOG_ERR, "Fork failed !!!");
        return ILauncher::eLaunchModule::FAILURE;
    }

    return ILauncher::eLaunchModule::SUCCESS;
}