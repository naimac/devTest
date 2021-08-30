#include "statusReceiver.hpp"
#include "iController.hpp"

#include "json.hpp"
#include "jsonTools.hpp"
using json = nlohmann::json;

#include "commonTools.hpp"

/**
 * @brief
 * Construct a new Status Receiver:: Status Receiver object
 * 
 * @param p_netconfServer 
 * @param p_log 
 */
StatusReceiver::StatusReceiver(std::priority_queue<Event, std::vector<Event>, compareEventPriority> *p_eventList,
                               ILog & p_log) : i_eventList(p_eventList),
                                               i_log(p_log)
{
    i_isRunning = false;
    i_isUdpSocketClosed = true;
    i_log.log(LOG_DEBUG, "StatusReceiver::%s", __func__);
}

/**
 * @brief
 * Destroy the Status Receiver:: Status Receiver object
 * 
 */
StatusReceiver::~StatusReceiver()
{
    i_log.log(LOG_INFO, "StatusReceiver::%s", __func__);

    // keep comment if needing it later
    // i_log.log(LOG_DEBUG, "go stop(SIGTERM)");
    // stop(SIGTERM);
}

/**
 * @brief
 * Call the init the protobufServer
 * init the protoServer , the json file correspond to the configuration file pass to the program
 * 
 * @param p_configInitializer : obtained through the main.cpp / agent.cpp
 * @return StatusReceiver::eInit 
 */
IStatusReceiver::eInit                     StatusReceiver::init(const nlohmann::json &p_configInitializer)
{
    i_log.log(LOG_INFO, "StatusReceiver::%s", __func__);

    std::string l_protobufHost;
    int         l_protobufPort;

    try
    {
        getJsonParameter(l_protobufHost, p_configInitializer, "protobuf_host");
        getJsonParameter(l_protobufPort, p_configInitializer, "protobuf_port");
    }
    catch (const std::exception &e)
    {
        i_log.log(LOG_ERR, "Json retrieving failed on fields <protobuf_host> or <protobuf_prot> : [%s]", e.what());
        return IStatusReceiver::eInit::FAILURE;
    }

    // UDP
    if ((i_udpSocketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        i_log.log(LOG_ERR, "Error on setting UDP socket !");
        return IStatusReceiver::eInit::FAILURE;
    }
    
    i_serverSocketAddress.sin_addr.s_addr   =   INADDR_ANY; // TODO --> FIND VALUE TO PUT WITH HOST?
    i_serverSocketAddress.sin_port          =   htons(l_protobufPort);
    i_serverSocketAddress.sin_family        =   AF_INET;

    int bindResult;
    
    // man bind --> on success, 0 is returned
    if ((bindResult = 
            bind(i_udpSocketfd, reinterpret_cast<sockaddr*>(&i_serverSocketAddress), sizeof(i_serverSocketAddress)) ) != 0)
    {
        i_log.log(LOG_DEBUG, "ThreadID [%d] | Receiver::%s --> BIND FAILED !", std::this_thread::get_id(), __func__);
        return eInit::FAILURE;
    }
    i_log.log(LOG_DEBUG, "ThreadID [%d] | Receiver::%s --> BIND SUCCEED !", std::this_thread::get_id(), __func__);

    i_isUdpSocketClosed = false;

    i_isRunning = true;

    return IStatusReceiver::eInit::SUCCESS;
}

/**
 * @brief 
 * Run the protoServer & test if the thread launched is joinable
 * if not it return a failure on starting the server
 * 
 * @return StatusReceiver::eStart 
 */
StatusReceiver::eStart                      StatusReceiver::start()
{
    i_log.log(LOG_INFO, "StatusReceiver::%s", __func__);

    i_protobufThread = std::thread(&StatusReceiver::receiveProtobuf, this);

    if (!i_protobufThread.joinable())
    {
        i_log.log(LOG_DEBUG, "i_protobufThread NOT joinable !");
        return eStart::FAILURE;
    }
    i_log.log(LOG_DEBUG, "++ i_protobufThread created and joinable ++");

    return (eStart::SUCCESS);
}

/**
 * @brief ReceiverProtobuf
 * wait on the network for receive a message on protocol protobuf
 * add a new event in the eventList when receiving a message
 * 
 */
void                                        StatusReceiver::receiveProtobuf()
{

    i_log.log(LOG_INFO, "Receiver::%s - ThreadID [%i]", __func__, std::this_thread::get_id());

    char                l_buffer[BUFFER_LEN];
    ssize_t             l_bytesReceived = 0;
    socklen_t           l_serverAddressLen = sizeof(i_serverSocketAddress);
    Event               l_newEvent;
    Notifications       l_notifications;
    

    while (i_isRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        l_bytesReceived = recvfrom(i_udpSocketfd, l_buffer, 2000, MSG_DONTWAIT, reinterpret_cast<sockaddr *>(&i_serverSocketAddress), &l_serverAddressLen);

        if (l_bytesReceived == -1)
        {
            i_log.log(LOG_DEBUG, "No notifications received on protobuf server ...");
            continue;
        }

        l_buffer[l_bytesReceived] = '\0'; // probably useless

        if (l_bytesReceived != 0)
        {

            std::cout << "Bytes received !" << std::endl << std::endl;
            i_log.log(LOG_INFO, "%s : statusReceiver bytes received from protobuf reception ---------------------> bytesReceived [%zd]", __func__, l_bytesReceived);
            l_notifications.PrintDebugString();

            if (l_notifications.ParseFromString(std::string(l_buffer, 0, l_bytesReceived))) // debug
            {
                std::cout << l_notifications.DebugString().c_str() << std::endl;
                i_log.log(LOG_INFO, "[%s]", l_notifications.DebugString().c_str());
                if (l_notifications.IsInitialized())
                {
                    // keep it temporary for debugging
                    /*
                    std::cout << "print stats : " << std::endl;
                    l_notifications.stats().PrintDebugString();

                    std::cout << std::endl << "print cpu" << std::endl;
                    std::cout << l_notifications.stats().cpuusage() << std::endl;
                    */

                    addEvent(l_notifications);  // A REMETTRE
                }
                else
                {
                    i_log.log(LOG_ERR, "Error : i_notifications structure not initialized !");
                }
            }
            else
            {
                i_log.log(LOG_ERR, "Error on parsing protobuf message");
            }
        }
    }
}

/**
 * @brief
 * Set the i_isRunning to false + reset the i_eventList to an empty one 
 * 
 * @param p_sigNum signal number as a macro : SIGTERM, SIGINT, SIGSTOP 
 * @return StatusReceiver::eStop 
 */
StatusReceiver::eStop                       StatusReceiver::stop(int p_sigNum)
{
    i_log.log(LOG_INFO, "StatusReceiver::%s [%i]", __func__, p_sigNum);

    i_isRunning = false;
    
    i_log.log(LOG_DEBUG, "--------------- BEFORE closing the socket");
    i_log.log(LOG_DEBUG, "Socket still open");

    if (i_isUdpSocketClosed == false)
    {
        i_log.log(LOG_DEBUG, "close the socket");
        close(i_udpSocketfd);
        i_isUdpSocketClosed = true;
        i_log.log(LOG_DEBUG, "Socket closed");
    }

    i_log.log(LOG_DEBUG, "Joining i_protobufThread");
	if (i_protobufThread.joinable())
	{
		i_protobufThread.join();
	}

    i_log.log(LOG_DEBUG, "xxxxxxxxxxxxxxx");

	// todo : see if later an error management more precise with a return failure will be needed
	// if not remove the return success and put the method with a void return
    return (eStop::SUCCESS);
}

/**
 * @brief
 * Set and push an event in the i_eventList with the received informations
 * 
 * @param p_json 
 * @return StatusReceiver::eAddEvent 
 */
StatusReceiver::eAddEvent                   StatusReceiver::addEvent(Notifications p_notifications)
{
    i_log.log(LOG_INFO, "StatusReceiver::%s ", __func__);

    Event         l_newEvent;

    l_newEvent.sourceID = p_notifications.sourceid();

    l_newEvent.sourceType = (e_sourceType)p_notifications.sourcetype();

    std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXX" << p_notifications.cpuusage() << std::endl;
    l_newEvent.cpuUsage = std::stoi(p_notifications.cpuusage());

    l_newEvent.ramUsage = std::stoi(p_notifications.ramusage());

    l_newEvent.upTime = p_notifications.uptime();

    l_newEvent.eventPriority = (e_eventPriority)p_notifications.priority();

    l_newEvent.eventType = (e_eventType)p_notifications.notificationtype();

    l_newEvent.sendingDate = p_notifications.sendingdate();

    l_newEvent.eventReceptionTime = std::time(nullptr);


    std::string l_tmp = p_notifications.message();
    l_newEvent.jsonData = nlohmann::json::parse(l_tmp);

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
bool                                        StatusReceiver::isEventListEmpty(void)
{
    i_log.log(LOG_DEBUG, "StatusReceiver::%s ", __func__);
    return (i_eventList->empty());
}

