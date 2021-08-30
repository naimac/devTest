#include "agent.hpp"
#include "iLog.hpp"

#include "commonTools.hpp"

#ifndef _CONFIG_RECEIVER_HPP_
#define _CONFIG_RECEIVER_HPP_

#include "iNetconfServer.hpp"

class ConfigReceiver : public IConfigReceiver
{
 
public: // -------------------------------------------------------------------------------- [ PUBLIC ]

    ConfigReceiver(INetconfServer &p_netconfServer, std::priority_queue<Event, std::vector<Event>, compareEventPriority> *p_eventList, ILog &p_log); 

    ~ConfigReceiver(void);
 
    ConfigReceiver(const IConfigReceiver& p_source) = delete;
    ConfigReceiver &operator=(const IConfigReceiver& p_source) = delete;

    // init the netconfServer , the json file correspond to the configuration file pass to the program
    eInit                           init(const nlohmann::json &p_json);  

    // run the netconfServer
    IConfigReceiver::eStart         start(void);

    // brief set the i_isRunning to false + reset the i_eventList to an empty one 
    IConfigReceiver::eStop          stop(int p_sigNum);

    // brief return if the list of event is empty or not
    bool                            isEventListEmpty(void); 

private: // -------------------------------------------------------------------------------- [ PRIVATE ]

    INetconfServer                  &i_netconfServer;
    ILog                            &i_log;
    std::thread                     i_eventThread;
    std::mutex                      i_eventMutex;
    bool                            i_isRunning;
    
    enum class                      eInitNetconfServer { SUCCESS, FAILURE };

    // brief call the init method of the i_netconfServer object
    eInitNetconfServer              initNetconfServer(const nlohmann::json &p_json);

    // brief call the init method of the i_ netconfServer object
    INetconfServer::eEditCallBack   netconfEditCallBack(nc_session &p_session, lyd_node *p_node);

    enum class                      eAddEvent{ SUCCESS, FAILURE };

    // set and push an event in the i_eventList with the received informations
    eAddEvent                       addEvent(nlohmann::json p_json, e_eventType p_type);

    // i_eventList
    std::priority_queue<Event, std::vector<Event>, compareEventPriority> *i_eventList;

#endif
};
