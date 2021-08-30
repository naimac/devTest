#ifndef _I_CONTROLLER_HPP_
#define _I_CONTROLLER_HPP_

#include "agent.hpp"
#include "commonTools.hpp"

class IController
{
 
public:

    enum class                      eInit { SUCCESS, FAILURE };
    virtual eInit                   init(const nlohmann::json &p_json) = 0;  

    enum class                      eStart { SUCCESS, FAILURE };
    virtual eStart                  start(void) = 0;

    enum class                      eStopAll { SUCCESS, FAILURE };
    virtual eStopAll                stopAll(int p_sigNum) = 0;

    virtual std::list<Module>       getModulesListFromJson(nlohmann::json &p_json) = 0;
    
    enum class                      eThreadManager { SUCCESS, FAILURE };
    virtual eThreadManager          threadManager(void) = 0;

    virtual void                    eventHandler(void) = 0; // a virer

    virtual Event                   getEvent(void) = 0;

}; // end class Balancer

#endif