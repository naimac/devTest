
#include "stopper.hpp"

#include "iLog.hpp"

Stopper::Stopper(ILog &p_log) : i_log(p_log)
{
    i_log.log(LOG_INFO, "Stopper::%s", __func__);
}

Stopper::~Stopper()
{
    i_log.log(LOG_INFO, "Stopper::%s", __func__);
}

/**
 * @brief 
 * useless for the moment -> TODO : delete it
 * 
 * @return eInitStopper 
 */
IStopper::eInit            Stopper::init(void) // maybe useless
{
    i_log.log(LOG_INFO, "Stopper::%s", __func__);
    // todo or not todo ...
    return IStopper::eInit::SUCCESS;
}

/**
 * @brief
 * Kill a pid with the SIGTERM (15) signal 
 * 
 * @param p_modulePidList 
 * @return IStopper::eStopPid 
 */
IStopper::eStopModule             Stopper::stopModule(std::list<pid_t> p_modulePidList)
{
    i_log.log(LOG_INFO, "Stopper::%s", __func__);

    // #stackOverFlowTricks : "if you have no intention to wait for the child process ... 
    // set the SIGCHLD handler to SIG_IGN to have the kernel automatically reap the children"
    signal(SIGCHLD, SIG_IGN); // avoid zombies programs (#stackOverFlow tricks)
     
    for (pid_t l_modulePid : p_modulePidList)
    {
        if (kill(l_modulePid, SIGTERM))
            return IStopper::eStopModule::FAILURE;
    }

    return IStopper::eStopModule::SUCCESS;
}