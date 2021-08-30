#ifndef _I_AGENT_HPP_
#define _I_AGENT_HPP_

#include "iConfigReceiver.hpp"
#include "iController.hpp"
#include "iLauncher.hpp"
#include "iStopper.hpp"
#include "iObserver.hpp"

#include <string>
#include <list>
#include <thread>
#include <mutex>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <iostream>

#include "json.hpp"

class IAgent
{

public:

    enum class                              eInit { SUCCESS, FAILURE };
    virtual eInit                           init(const nlohmann::json &p_json) = 0;

    enum class                              eStart { SUCCESS, FAILURE };
    virtual eStart                          start() = 0;

    enum class                              eStop { SUCCESS, FAILURE };
    virtual eStop                           stop(int p_sigNum) = 0;

    enum class                              eInitSignalHandler { SUCCESS, FAILURE };
    virtual eInitSignalHandler              initSignalHandler(void) = 0;

}; // end class Agent

#else

#include "iConfigReceiver.hpp"
#include "iController.hpp"
#include "iLauncher.hpp"
#include "iStopper.hpp"
#include "iObserver.hpp"

#include "iLog.hpp"
#include <string>
#include <list>
#include <thread>
#include <mutex>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <iostream>

#endif