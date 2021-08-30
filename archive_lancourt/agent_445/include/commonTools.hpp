#include "iLog.hpp"
#include <string> // std::string
#include <iostream> // std::cout | std::endl
#include <list> // std::list
#include <ctime> // std::time_t
#include <thread>
#include <mutex>
#include <list>

#include <netinet/in.h>
#include <fstream>

#include "notifications.pb.h"

#include "iLog.hpp"

#include <csignal>
#include <unistd.h>

#include <queue>

#include "json.hpp"
#include "jsonTools.hpp"

#include <map>
#include <iterator>

#include "notifications.pb.h"

#ifndef _COMMON_TOOLS_HPP_
#define _COMMON_TOOLS_HPP_

// TIPS FOR PRINTING AN ENUM
// std::cout << "++++++++> " << __func__ << static_cast<std::underlying_type<e_eventType>::type>(l_eventType) << std::endl;

template <typename T>
static int getJsonParameter(T &p_myParameter, const nlohmann::json &p_json, const std::string &p_jsonKey)
{
    p_myParameter = p_json.at(p_jsonKey).get<T>();
    return 0;
}

// typedef enum
// {
//     DEFAULT_NOTIF = 0,
//     ALERT,
//     STATS,
// } e_notificationType;

typedef enum
{
    DEFAULT_SOURCE = 0,
    GLOBAL_MANAGER,
    LOCAL_MANAGER,
    AGENT,
    COLLECTOR,
    CAPTURE,
    DETECTION,
    PERCEPTION,
    VISION
} e_sourceType;

typedef enum
{
    CONFIG = 0, // forcing first position to 0, the next will be 1 and so on
    ALERT,
    STATS,
    UNDEFINED
} e_eventType; // notificationType --> proto

typedef enum
{
    DEFAULT_PRIORITY = 0,
    WARNING,
    ERROR,
    FATAL,
} e_eventPriority;

typedef enum
{
    STOP = 0, // forcing first position to 0, the next will be 1 and so on
    START
} e_moduleOperation;

struct  Module
{
    int                         id;
    std::string                 name;
    std::string                 parameters; // informations associated to a module (launch parameters, stats of running)
};

struct  Event
{
    u_int32_t                           sourceID;
    e_sourceType                        sourceType;
    int                                 cpuUsage;
    int                                 ramUsage;
    u_int64_t                           upTime;
    e_eventPriority                     eventPriority;
    e_eventType                         eventType; // notifType --> Notifications_NotificationType
    u_int64_t                           sendingDate;
    std::time_t                         eventReceptionTime;
    nlohmann::json                      jsonData;    
};

// comparison the i_eventList priority queue
struct  compareEventPriority
{
    bool operator()(const Event &p_newEvent, const Event &p_oldEvent) const
    {
        return ((int)p_newEvent.eventType > (int)p_oldEvent.eventType);
    }
};

// std::mutex                              g_eventMutex;

#endif
