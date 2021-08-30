#ifndef _AGENT_HPP_
#define _AGENT_HPP_

#include "iAgent.hpp"
#include "iConfigReceiver.hpp"
#include "iStatusReceiver.hpp"

#include "notifications.pb.h"

#include "iLog.hpp"
#define     BUFFER_SIZE     2000

class Agent : public IAgent
{

public:

    static Agent                   *s_agent;

    Agent(void);

    Agent(IController &p_controller, ILog &p_log);

    ~Agent(void);

    Agent(const Agent &p_source) = delete;
    Agent &operator=(const Agent &p_source) = delete;
    
    // initialize the controller & initialize the signal handleing
    IAgent::eInit                   init(const nlohmann::json & p_json);    

    // start the controller which start the receivers (configReceiver[netconf] & notifReceiver[protobuf])
    IAgent::eStart                  start(void);

    // stop the controller which stop all the modules
    IAgent::eStop                   stop(int p_sigNum);

private:

    bool                            i_isAgentRunning;

    IController                     &i_controller;
    ILog                            &i_log;

    // initialize the signalHandler
    IAgent::eInitSignalHandler      initSignalHandler(void);

    // set a static instance of the agent class, needed by the signalhandler
    void                            setStaticInstance(Agent &p_agent);

    // method given to the initSignalHandler
    static void                     stopHandlerMethod(int p_sigNum);

}; // end class Agent

#else

#endif