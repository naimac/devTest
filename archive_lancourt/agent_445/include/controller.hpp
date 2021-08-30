#ifndef _CONTROLER_HPP_
#define _CONTROLER_HPP_

#include "agent.hpp"
#include "iLog.hpp"
#include "iController.hpp"
#include "commonTools.hpp"

class Controller : public IController
{
 
public:

// ----------------------------------------------------------------------------------------------- [ function ]

    Controller(std::priority_queue<Event, std::vector<Event>, compareEventPriority> *p_eventList,
                IConfigReceiver &p_configReceiver, 
                IStatusReceiver &p_statusReceiver,
                ILauncher &p_launcher, 
                IStopper &p_stopper, 
                IObserver &p_observer, 
                ILog &p_log);

    ~Controller(void);
 
    Controller(const Controller& p_source) = delete;
    Controller &operator=(const Controller& p_source) = delete;
    
    // brief construct a map structure to store a pair "module / absolutePathToTheModuleBinary"
    IController::eInit                  init(const nlohmann::json &p_json);  

    // brief start the receivers (for the moment only configReceiver, later I'll add notifReceiver) 
    IController::eStart                 start(void);

    // brief : stop all the classes references , according to the given signal
    IController::eStopAll               stopAll(int p_sigNum);

private: // =================================================================================================== //

    void                                printEventDebug(Event p_event);

    // launch the "eventHandler" method in a new thread
    IController::eThreadManager         threadManager(void);

    // Launched in a new thread
    // loop for fetching a new event from the event list
    // and give it to the controller method "eventProcessing"
    void                                eventHandler(void); // onEvent

    // get the top event (the highest priority), and pop it from the i_eventList
    // see i_eventList at the bottom of the page
    Event                               getEvent(void);

    // get the module list and loop on each module to call
    // the launchModule method of the launcher class
    void                                processEvent(Event p_event);

    // retrieve modules (see commonTools.hpp) from a json file push each one in a list
    // set the "module" fields by parsing the json file given to the program
    std::list<Module>                   getModulesListFromJson(nlohmann::json    &p_json);

    void                                pushPid(pid_t modulePid);
// ----------------------------------------------------------------------------------------------- [ attribute ]

    IConfigReceiver                     &i_configReceiver;
    IStatusReceiver                     &i_statusReceiver;
    ILauncher                           &i_launcher;
    IStopper                            &i_stopper;
    IObserver                           &i_observer;
    ILog                                &i_log;
    bool                                i_running;

    std::thread                         i_eventThread;
    std::mutex                          i_eventMutex;

    // MAP
    std::map<std::string, std::string>  i_map;
    
    // module pid
    std::list<pid_t>                    i_modulePidList;

    // i_eventList
    std::priority_queue<Event, std::vector<Event>, compareEventPriority> *i_eventList;

}; // end class Controller

#endif