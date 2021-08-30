#include "agent.hpp"
#include "json.hpp"

#include "commonTools.hpp"

using json = nlohmann::json;


Agent *Agent::s_agent = nullptr;

Agent::Agent(IController &p_controller, ILog &p_log) :  i_controller(p_controller), i_log(p_log)
{
    i_log.log(LOG_DEBUG, "Agent::%s", __func__);
    setStaticInstance(*this);
}

/**
 * @brief
 * set a static instance of the agent class
 * 
 * @param p_agent 
 */
void                                Agent::setStaticInstance(Agent &p_agent)
{
    i_log.log(LOG_DEBUG, "Agent::%s", __func__);
    s_agent = &p_agent;
}

/**
 * @brief
 * Destroy the Agent:: Agent object
 * 
 */
Agent::~Agent()
{
    i_log.log(LOG_DEBUG, "Agent::%s", __func__);
}

/**
 * @brief
 * implementation of the receiver's initializer from a json file configuration
 * @param p_json -> the json file as an object given at the program launching
 * @return Agent::eInitAgent 
 */
IAgent::eInit                       Agent::init(const nlohmann::json &p_json)
{
    i_log.log(LOG_DEBUG, "Agent::%s", __func__);

    initSignalHandler();
    if (i_controller.init(p_json) == IController::eInit::FAILURE) // INIT RECEIVER --> init / loadmodule / setCallBack
        return IAgent::eInit::FAILURE;

    i_isAgentRunning = true;
    return IAgent::eInit::SUCCESS;
}

/**
 * @brief
 * static method send in the initSignalHandler (see below) to the l_sigation.sa_handler
 * 
 * @param p_sigNum 
 */
void                                Agent::stopHandlerMethod(int p_sigNum) // see if it's possible to pass the agent's stop method directly rather than passing trhough the stopHandlerMethod
{
    s_agent->stop(p_sigNum);
}

/**
 * @brief
 * initialize the signal handler
 * 
 * @return IAgent::eInitSignalHandler 
 */
IAgent::eInitSignalHandler           Agent::initSignalHandler()
{
    i_log.log(LOG_DEBUG, "Agent::%s", __func__);
    i_log.log(LOG_INFO, "Initialize sigaction");    
    struct sigaction l_sigaction;

    l_sigaction.sa_handler = stopHandlerMethod; // stopHandler
    sigemptyset(&l_sigaction.sa_mask);
    l_sigaction.sa_flags = SA_RESTART;

    if(sigaction(SIGINT, &l_sigaction, 0) == -1
        || sigaction(SIGTERM, &l_sigaction, 0) == -1
        || sigaction(SIGQUIT, &l_sigaction, 0) == -1 )
    {
        i_log.LOG(LOG_ERR, "--Failed to init sigaction");
        return IAgent::eInitSignalHandler::FAILURE; 
    }

    i_log.LOG(LOG_DEBUG, "Sigaction initialized");
    i_log.LOG(LOG_DEBUG, "-----");
   
    return IAgent::eInitSignalHandler::SUCCESS;
}      

/**
 * @brief
 * start the controller and sleep each 5 ms
 *
 * @return Agent::eStartAgent 
 */
IAgent::eStart                      Agent::start(void)
{
    i_log.LOG(LOG_DEBUG, "Agent::%s", __func__);    
    if (i_controller.start() == IController::eStart::FAILURE) // NETCONF RUN
        return IAgent::eStart::FAILURE;

    while (i_isAgentRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    return IAgent::eStart::SUCCESS;
}

/**
 * @brief
 * stop the controller which stop all the modules
 * 
 * @param p_sigNum 
 * @return IAgent::stop 
 */
IAgent::eStop                        Agent::stop(int p_sigNum)
{
    i_log.LOG(LOG_DEBUG, "Agent::%s Signal [%i] received !", __func__, p_sigNum);    

    if (i_controller.stopAll(p_sigNum) == IController::eStopAll::FAILURE)
        return IAgent::eStop::FAILURE;

    i_isAgentRunning = false;

    i_log.LOG(LOG_DEBUG, "Stop Agent process : Done");
    
    return IAgent::eStop::SUCCESS;
}