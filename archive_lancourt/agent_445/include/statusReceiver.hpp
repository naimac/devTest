#include "agent.hpp"
#include "iLog.hpp"

#include "commonTools.hpp"

#include <sys/types.h>
#include <sys/socket.h>

#ifndef _STATUS_RECEIVER_HPP_
#define _STATUS_RECEIVER_HPP_

# define BUFFER_LEN 2000

class StatusReceiver : public IStatusReceiver
{
 
public: // -------------------------------------------------------------------------------- [ PUBLIC ]

    StatusReceiver(std::priority_queue<Event, std::vector<Event>, compareEventPriority> *p_eventList, ILog &p_log); 

    ~StatusReceiver(void);
 
    StatusReceiver(const IStatusReceiver& p_source) = delete;
    StatusReceiver &operator=(const IStatusReceiver& p_source) = delete;

    // init the protoServer , the json file correspond to the configuration file pass to the program
    IStatusReceiver::eInit          init(const nlohmann::json &p_json);  

    // run the protoServer
    IStatusReceiver::eStart         start(void);

    // brief set the i_isRunning to false + reset the i_eventList to an empty one 
    IStatusReceiver::eStop          stop(int p_sigNum);

    // get the top event (the highest priority), and pop it from the i_eventList
    // see i_eventList at the bottom of the page
    Event                           getEvent(void);
    
    // brief return if the list of event is empty or not
    bool                            isEventListEmpty(void);

private: // -------------------------------------------------------------------------------- [ PRIVATE ]

    ILog                            &i_log;
    std::thread                     i_protobufThread;                     
    std::thread                     i_eventThread;
    std::mutex                      i_eventMutex;
    bool                            i_isRunning;

    int                             i_udpSocketfd;
    sockaddr_in                     i_serverSocketAddress;
    bool                            i_isUdpSocketClosed;

    enum class                      eAddEvent{ SUCCESS, FAILURE };

    // set and push an event in the i_eventList with the received informations
    eAddEvent                       addEvent(Notifications p_notifications);

    //  Set and push an event in the i_eventList with the received informations
    void                            receiveProtobuf(void);

    // i_eventList
    std::priority_queue<Event, std::vector<Event>, compareEventPriority> *i_eventList;

#endif
};
