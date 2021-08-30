#include "agent.hpp"

#include "statusReceiver.hpp"
#include "iStatusReceiver.hpp"

#include "configReceiver.hpp"
#include "iConfigReceiver.hpp"

#include "iController.hpp"
#include "controller.hpp"

#include "iObserver.hpp"
#include "observer.hpp"

#include "iLauncher.hpp"
#include "launcher.hpp"

#include "iStopper.hpp"
#include "stopper.hpp"

#include "netconfServer.hpp"
#include <string.h>
#include <unistd.h>
#include "syslog.hpp"
#include "mock/mock_iLog.hpp"

#include "commonTools.hpp"

int main(int argc, char **argv, char **envp)
{
    if (geteuid() != 0)
    {
        fprintf(stderr, "Please run as root member\n");
        syslog(LOG_ERR, "Try to launch capture but not as root, can't start capture");
        closelog();
        return EXIT_FAILURE;
    }

    if (argc != 2)
    {
        std::cout << "JSONFILE NEEDED --> ./bin/debug [jsonString]" << std::endl;
        return EXIT_FAILURE;
    }

    Syslog          l_log("Agent", LOG_PID | LOG_NDELAY, LOG_USER);

    // i_eventList
    std::priority_queue<Event, std::vector<Event>, compareEventPriority> g_eventList;

    Launcher        l_launcher(l_log, envp);
    Stopper         l_stopper(l_log);
    Observer        l_observer(l_log);
    NetconfServer   l_netconfServer(l_log);
    ConfigReceiver  l_configReceiver(l_netconfServer, &g_eventList, l_log);
    StatusReceiver  l_statusReceiver(&g_eventList, l_log);
    Controller      l_controller(&g_eventList, l_configReceiver, l_statusReceiver, l_launcher, l_stopper, l_observer, l_log);

    if (argc != 2)
    {
        std::cout << "JSONFILE NEEDED (reminder : do not forget the sudo permission) --> sudo ./bin/debug [json]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string l_jsonString = argv[1];
    nlohmann::json l_json;

    try
    {
        // transform the string object to a nlohmann::json one
        l_json = nlohmann::json::parse(l_jsonString);
    }
    catch(const std::exception& e)
    {
        l_log.log(LOG_ERR, "main json parsing failure : %s", e.what());
        return EXIT_FAILURE;
    }
    
    Agent           l_agent(l_controller, l_log);

    // pass, to init method of agent instance, the json string given at the program launching
    if (l_agent.init(l_json) == IAgent::eInit::FAILURE)
    {
        return EXIT_FAILURE;
    }

    l_agent.start();

	// reset the priority queue with empty content
    g_eventList = std::priority_queue<Event, std::vector<Event>, compareEventPriority>();
    return 0;
}
