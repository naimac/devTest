#ifndef _I_CONFIG_RECEIVER_HPP_
#define _I_CONFIG_RECEIVER_HPP_

#include "json.hpp"
#include "commonTools.hpp"

class IConfigReceiver
{
 
public:

    enum class                                      eInit { SUCCESS, FAILURE };
    virtual eInit                                   init(const nlohmann::json &p_json) = 0;

    enum class                                      eStart { SUCCESS, FAILURE };
    virtual eStart                                  start(void) = 0;

    enum class                                      eStop { SUCCESS, FAILURE };
    virtual eStop                                   stop(int p_sigNum) = 0;

    virtual bool                                    isEventListEmpty(void) = 0;

}; // end class IReceiver

#endif