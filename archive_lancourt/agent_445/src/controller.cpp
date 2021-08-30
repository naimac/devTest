#include "controller.hpp"
#include "commonTools.hpp"

/**
 * @brief : Construct a new Controller:: Controller object
 * 
 * @param p_launcher 
 * @param p_stopper 
 * @param p_observer 
 * @param p_log 
 */
Controller::Controller(std::priority_queue<Event, std::vector<Event>, compareEventPriority> *p_eventList,
                       IConfigReceiver &p_configReceiver,
                       IStatusReceiver &p_statusReceiver,
                       ILauncher &p_launcher,
                       IStopper &p_stopper,
                       IObserver &p_observer,
                       ILog &p_log) : i_eventList(p_eventList),
                                      i_configReceiver(p_configReceiver),
                                      i_statusReceiver(p_statusReceiver),
                                      i_launcher(p_launcher),
                                      i_stopper(p_stopper),
                                      i_observer(p_observer),
                                      i_log(p_log)
{
    i_log.log(LOG_INFO, "Controller::%s", __func__);
}

/**
 * @brief
 * Destroy the Controller:: Controller object
 * 
 */
Controller::~Controller()
{
    i_log.log(LOG_INFO, "Controller::%s", __func__);
}

/**
 * @brief
 * Construct a map structure to store a pair "module / absolutePathToTheModuleBinary"
 * 
 * @param p_json -> the json string given at the program launching
 * @return IController::eInit 
 */
IController::eInit                  Controller::init(const nlohmann::json &p_json)
{
    i_log.log(LOG_INFO, "Controller::%s ", __func__);
    i_running = true;

    if (i_configReceiver.init(p_json) == IConfigReceiver::eInit::FAILURE ||
        i_statusReceiver.init(p_json) == IStatusReceiver::eInit::FAILURE ||
        i_launcher.init() == ILauncher::eInit::FAILURE ||
        i_stopper.init() == IStopper::eInit::FAILURE ||
        i_observer.init() == IObserver::eInit::FAILURE)
        return IController::eInit::FAILURE;

    std::string     capturePath;
    std::string     visionPath;

    try
    {
        // retrieve the programPath array present in the configuration file path to the program
        const nlohmann::json &l_jsonProgramPath = p_json.at("programPath"); // get the path for each program name

        // for each element of the programPath array
        // retrieving the absolute path of the executable (capture, vision ...)
        for (const auto &l_progPath : l_jsonProgramPath)
        {
            try
            {
                JsonTools::getJsonParameter(l_progPath, "capture", &capturePath);
                i_map.insert(std::make_pair("capture", capturePath));
            }
            catch(const std::exception& e)
            {
                i_log.log(LOG_INFO, "Unable to retrieve the [capture] path needed for launching it : %s ", e.what());
            }

            try
            {
                JsonTools::getJsonParameter(l_progPath, "vision", &visionPath); // a entourer de try catch
                i_map.insert(std::make_pair("vision", visionPath));
            }
            catch(const std::exception& e)
            {
                i_log.log(LOG_INFO, "Unable to retrieve the [vision] path needed for launching it : %s ", e.what());
            }
        }
    }
    catch (const std::exception &e)
    {
        i_log.log(LOG_DEBUG, "Controller::%s - JSON PARSING FAILURE - unable to retrieve field programPath | e.what[ %s ]", __func__, e.what());
        return IController::eInit::FAILURE;
    }

    // COMMENT KEPT IN CASE OF DEBUGGING
    // std::map<std::string, std::string>::iterator it = i_map.begin();
    // while (it != i_map.end())
    // {
    //     i_log.log(LOG_DEBUG, "XXXXXXXX it->first : [%s] | it->second : [%s]", it->first.c_str(), it->second.c_str());
    //     it++;
    // }
    // i_log.log(LOG_DEBUG, "capturePath [%s]", capturePath.c_str());

    return IController::eInit::SUCCESS;
}

/**
 * @brief
 * Start the receivers (for the moment only configReceiver, later I'll add statusReceiver) 
 * (if need be) have to call the "start" methods of stopper, launcher and observer 
 * (for the moment the start method is useless in stopper, launcher and observer)
 * 
 * @return IController::eStart 
 */
IController::eStart                 Controller::start(void)
{
    i_log.log(LOG_INFO, "Controller::%s ", __func__);
    
    i_configReceiver.start();
    i_statusReceiver.start();

    this->threadManager();

    return IController::eStart::SUCCESS;
}

/**
 * @brief
 * Stop all the classes references , according to the given signal
 * 
 * @param p_signal 
 * @return IController::eStopAll 
 */
IController::eStopAll             Controller::stopAll(int p_signal)
{
    i_log.log(LOG_DEBUG, "Controller::%s [%i]", __func__, p_signal);

    i_running = false;

    if (!i_modulePidList.empty())
        i_stopper.stopModule(i_modulePidList);

    if (i_configReceiver.stop(p_signal) == IConfigReceiver::eStop::FAILURE ||
        i_statusReceiver.stop(p_signal) == IStatusReceiver::eStop::FAILURE ||
        i_launcher.stop(p_signal) == ILauncher::eStop::FAILURE ||
        i_observer.stop(p_signal) == IObserver::eStop::FAILURE)
        return IController::eStopAll::FAILURE;

    if (i_eventThread.joinable())
        i_eventThread.join();

    return IController::eStopAll::SUCCESS;
}

/**
 * @brief
 * Launch the "eventHandler" method in a new thread
 * 
 * @return IController::eThreadManager 
 */
IController::eThreadManager         Controller::threadManager(void)
{
    i_log.log(LOG_DEBUG, "Controller::%s - i_running = %i", __func__, i_running);

    i_eventThread = std::thread(&Controller::eventHandler, this);

    if (!i_eventThread.joinable())
    {
        i_log.log(LOG_ERR, "i_eventThread not joinable !");
        i_running = false;
        return IController::eThreadManager::FAILURE;
    }

    return IController::eThreadManager::SUCCESS;
}

/**
 * @brief
 * Launched in a new thread
 * loop for fetching a new event from the event list 
 * and give it to the controller method "eventProcessing"
 * 
 */
void                                Controller::eventHandler(void) // eventHandler
{
    i_log.log(LOG_DEBUG, "Controller::%s - i_running = %i", __func__, i_running);

    while (i_running == true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        // if (i_configReceiver.isEventListEmpty()) // tenter un poll ici
        if (i_eventList->empty() == true) // tenter un poll ici
            continue; // GO THREAD SLEEP

		i_log.log(LOG_DEBUG, "i_eventList NOT EMPTY");

        Event l_newTopEvent = getEvent();
        processEvent(l_newTopEvent);

        //i_log.log(LOG_DEBUG, "l_newTopEvent.jsonData : [%s]", l_newTopEvent.jsonData);
    }
}

/**
 * @brief 
 * 
 */
void                                Controller::printEventDebug(Event p_event)
{
    std::cout << "1. ++++++ p_event.sourceID [" << p_event.sourceID << "]" << std::endl;

    // debug for printing an event
    std::cout << "2. ------------> p_event.sourceType [";
    std::cout << static_cast<std::underlying_type<Notifications_SourceType>::type>(p_event.sourceType);
    std::cout << "]" << std::endl;

    // debug
    std::cout << "3. ++++++ p_event.cpuUsage [" << p_event.cpuUsage << "]" << std::endl;

    // debug
    std::cout << "4. ++++++ p_event.ramUsage [" << p_event.ramUsage << "]" << std::endl;

    // debug
    std::cout << "5. ++++++ p_event.upTime [" << p_event.upTime << "]" << std::endl;

    // debug for printing an event
    std::cout << "6. ------------> p_event.priority [";
    std::cout << static_cast<std::underlying_type<e_eventPriority>::type>(p_event.eventPriority);
    std::cout << "]" << std::endl;

    // debug for printing an event
    std::cout << "7. ------------> p_event.eventType [";
    std::cout << static_cast<std::underlying_type<e_eventType>::type>(p_event.eventType);
    std::cout << "]" << std::endl;

    // debug
    std::cout << "8. ++++++ p_event.sendingDate [" << p_event.sendingDate << "]" << std::endl;

    p_event.eventReceptionTime = std::time(nullptr);
    // debug
    std::cout << "9. ++++++ p_event.eventReceptionTime [" << p_event.eventReceptionTime << "]" << std::endl;

    // debug
    std::cout << "10.++++++ p_event.jsonData [" << p_event.jsonData << "]" << std::endl;
}

/**
 * @brief 
 * Get the top event (the highest priority), and pop it from the list
 * 
 * memo lockgard --> se delock automatiquement apres la fonction
 * contrairement au unique lock
 * 
 * mutable == permet de lock/unlock le mutex dans une methode const
 * 
 * @return t_event 
 */
Event                               Controller::getEvent(void)
{
    i_log.log(LOG_DEBUG, "ConfigReceiver::%s ", __func__);

    std::lock_guard<std::mutex> l_mutexGetEvent(i_eventMutex);
    
    Event topEvent = i_eventList->top();
    i_eventList->pop();

    return (topEvent);
}

/**
 * @brief
 * Get the module list and loop on each module to call 
 * the launchModule method of the launcher class 
 * 
 * @param p_event (defined in include/commonTools.hpp) 
 */
void                                Controller::processEvent(Event p_event)
{
    i_log.log(LOG_INFO, "Controller::%s - i_running = %i", __func__, i_running);
    std::list<Module>   l_moduleList;

    pid_t               l_modulePid;

    printEventDebug(p_event);

    if (p_event.eventType == CONFIG)
    {
        if (!i_modulePidList.empty())
        {
            i_stopper.stopModule(i_modulePidList);
            i_modulePidList.clear(); // CLEAR THE PID PROCESS
        }

        l_moduleList = getModulesListFromJson(p_event.jsonData);

        for (Module module : l_moduleList)
        {
            i_launcher.launchModule(module, &l_modulePid);
            i_modulePidList.emplace_back(l_modulePid); // PUSH BACK THE PID PROCESS
        }
    }
}

/**
 * @brief
 * Retrieve modules (see commonTools.hpp) from a json file push each one in a list
 * set the "module" fields by parsing the json file given to the program
 * 
 * @param p_json 
 * @return std::list<Module> 
 * 
 */
std::list<Module>                   Controller::getModulesListFromJson(nlohmann::json  &p_json)
{
    i_log.log(LOG_INFO, "Controller::%s - i_running = %i", __func__, i_running);
    std::list<Module>   l_moduleList;

    int l_moduleCount = 0;

    try
    {
        l_moduleCount = p_json.at("magellan-agent:agent").at("module").size();
        i_log.log(LOG_DEBUG, " module count [%d]", l_moduleCount);
    }
    catch(const std::exception& e)
    {
        i_log.log(LOG_ERR, "Unable to retrieve the module count ! [%s]", e.what());
        return l_moduleList;
    }

    std::string l_name;

    for (int i = 0; i < l_moduleCount; i++)
    {
        Module l_module;

        l_module.id = p_json.at("magellan-agent:agent").at("module").at(i).at("id").get<int>();
        l_name = p_json.at("magellan-agent:agent").at("module").at(i).at("name").get<std::string>();

        std::map<std::string, std::string>::iterator it = i_map.find(l_name);
        if (it != i_map.end())
            l_module.name = it->second;

        l_module.parameters = p_json.at("magellan-agent:agent").at("module").at(i).at("parameters").get<std::string>();

        l_moduleList.emplace_back(l_module);
    }

    return l_moduleList;
}
