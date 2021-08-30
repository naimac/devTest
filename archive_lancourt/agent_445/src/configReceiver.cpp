#include "configReceiver.hpp"
#include "iController.hpp"

#include "json.hpp"
#include "jsonTools.hpp"
using json = nlohmann::json;

#include "netconfServer.hpp"

#include "commonTools.hpp"

/**
 * @brief
 * Construct a new Config Receiver:: Config Receiver object
 * 
 * @param p_netconfServer 
 * @param p_log 
 */
ConfigReceiver::ConfigReceiver(INetconfServer &p_netconfServer,
                               std::priority_queue<Event, std::vector<Event>, compareEventPriority> *p_eventList,
                               ILog & p_log) : i_netconfServer(p_netconfServer),
                                               i_eventList(p_eventList),
                                               i_log(p_log)
{
    i_log.log(LOG_DEBUG, "ConfigReceiver::%s", __func__);
    i_isRunning = true;
}

/**
 * @brief
 * Destroy the Config Receiver:: Config Receiver object
 * 
 */
ConfigReceiver::~ConfigReceiver()
{
    i_log.log(LOG_INFO, "ConfigReceiver::%s", __func__);
    stop(SIGTERM);
}

/**
 * @brief
 * Call the init the netconfServer
 * 
 * @param p_configInitializer : obtained through the main.cpp / agent.cpp
 * @return ConfigReceiver::eInit 
 */
ConfigReceiver::eInit                     ConfigReceiver::init(const nlohmann::json &p_configInitializer)
{
    i_log.log(LOG_INFO, "ConfigReceiver::%s", __func__);

    if (initNetconfServer(p_configInitializer) == ConfigReceiver::eInitNetconfServer::FAILURE)// netconfServer initialization
        return eInit::FAILURE;

    return eInit::SUCCESS;
}

/**
 * @brief
 * Call the init method of the i_netconfServer object
 * 
 * @param p_configInitializer : obtained through the agent.cpp, which obtain it trough the main.cpp
 * @return ConfigReceiver::eInitNetconfServer 
 */
ConfigReceiver::eInitNetconfServer                           ConfigReceiver::initNetconfServer(const nlohmann::json &p_initConfig)
{
    i_log.log(LOG_INFO, "ConfigReceiver::%s ", __func__);

    if (i_netconfServer.init(p_initConfig) == INetconfServer::eInit::FAIL)
    {
        i_log.log(LOG_ERR, "ConfigReceiver::%s - Fail to init netconfServer !", __func__);
        return eInitNetconfServer::FAILURE;
    }

    if (i_netconfServer.loadModule("magellan-agent", "") == INetconfServer::eLoadModule::FAIL) // add module to context
    {
        i_log.log(LOG_ERR, "ConfigReceiver::%s - Fail to loadModule", __func__);
        return eInitNetconfServer::FAILURE;
    }

    // setEditCallBack --> set the callback : "editCallBack" (editCallBack == netConfEditCallBack)
    // -----> for sending config from the manager to the agent
    // the function needed to edit IN THE AGENT the information received FROM the Manager
    // need to convert a node to a json object
    i_netconfServer.setEditCallBack(std::bind(&ConfigReceiver::netconfEditCallBack, this, std::placeholders::_1, std::placeholders::_2)); // set server getCall

    // setGetCallBack --> set the callback : "getCallBack" (getCallBack == netConfGetCallBack)
    // -----> for sending stat from the agent to the manager
    // the function needed to edit BY the agent the stats (running informations) that will be received BY the Manager fron the agent
    // TODO : need to convert a json object to a node one

    // i_netconfClient.setGetCallBack(....) // for later usage

    return eInitNetconfServer::SUCCESS;
}

/**
 * @brief
 * Callback for getEvents
 * TODO ... OR NOT
 * TODO if there's still need a netconf client
 * 
 * @param p_session 
 * @param p_node 
 * @param p_retNode 
 * @return INetconfServer::eGetCallBack 
 */
/*
INetconfServer::eGetCallBack                ConfigReceiver::netconfGetCallBack(nc_session &p_session, lyd_node *p_node, lyd_node **p_retNode)
{

    return INetconfServer::eGetCallBack::FAIL;
}
*/

/**
 * @brief
 * Callback for needed by the netconfServer library 
 * (editing a json object representing the received information through the netconf protocol)
 * 
 * @param p_session 
 * @param p_node 
 * @return INetconfServer::eEditCallBack 
 */
INetconfServer::eEditCallBack               ConfigReceiver::netconfEditCallBack(nc_session &p_session, lyd_node *p_node)
{
    i_log.log(LOG_INFO, "ConfigReceiver::%s", __func__);

    nlohmann::json      l_modulesConfig;

    ly_set *pathAgent = lyd_find_path(p_node, "/magellan-agent:agent"); // namespace:conteneur

    if (!pathAgent)
        return INetconfServer::eEditCallBack::FAIL;

    try
    {
        l_modulesConfig = JsonTools::lydNodeToJson(p_node);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return INetconfServer::eEditCallBack::FAIL;
    }
    addEvent(l_modulesConfig, CONFIG);

    return INetconfServer::eEditCallBack::SUCCESS;
}

/**
 * @brief 
 * Run the netconfServer
 * 
 * @return ConfigReceiver::eStart 
 */
ConfigReceiver::eStart                      ConfigReceiver::start()
{
    i_log.log(LOG_INFO, "ConfigReceiver::%s", __func__);

    if (i_netconfServer.run() == INetconfServer::eRun::FAIL)
        return (eStart::FAILURE);

    return (eStart::SUCCESS);
}

/**
 * @brief
 * Set the i_isRunning to false + reset the i_eventList to an empty one 
 * 
 * @param p_sigNum signal number as a macro : SIGTERM, SIGINT, SIGSTOP 
 * @return ConfigReceiver::eStop 
 */
ConfigReceiver::eStop                       ConfigReceiver::stop(int p_sigNum)
{
    i_log.log(LOG_INFO, "ConfigReceiver::%s [%i]", __func__, p_sigNum);

    if (i_netconfServer.stop() == INetconfServer::eStop::FAIL)
        return eStop::FAILURE;

    i_isRunning = false;

    // move it to the agent
    // set i_eventList with an empty priority_queue
    // *i_eventList = std::priority_queue<Event, std::vector<Event>, compareEventPriority>();

    return (eStop::SUCCESS);
}

/**
 * @brief
 * Set and push an event in the i_eventList with the received informations
 * 
 * @param p_json 
 * @return ConfigReceiver::eAddEvent 
 */
ConfigReceiver::eAddEvent                   ConfigReceiver::addEvent(nlohmann::json p_json, e_eventType p_eventType)
{
    i_log.log(LOG_INFO, "ConfigReceiver::%s ", __func__);

    Event         l_newEvent;
    
    l_newEvent.sourceID = 0;

    l_newEvent.sourceType = LOCAL_MANAGER;

    l_newEvent.cpuUsage = 0;

    l_newEvent.ramUsage = 0;

    l_newEvent.upTime = 0;

    l_newEvent.eventPriority = DEFAULT_PRIORITY;

    l_newEvent.eventType = p_eventType;

    l_newEvent.sendingDate = 0;

    l_newEvent.eventReceptionTime = std::time(nullptr);

    l_newEvent.jsonData = p_json;

    // std::lock_guard<std::mutex> l_mutexGetEvent(i_eventMutex);
    std::lock_guard<std::mutex> l_mutexGetEvent(i_eventMutex);
    i_eventList->push(l_newEvent);

    return (eAddEvent::SUCCESS);
}

/**
 * @brief
 * Return if the list of event is empty or not
 * 
 * @return true 
 * @return false 
 */
bool                                        ConfigReceiver::isEventListEmpty(void)
{
    i_log.log(LOG_DEBUG, "ConfigReceiver::%s ", __func__);
    return (i_eventList->empty());
}