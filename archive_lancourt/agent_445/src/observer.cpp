#include "observer.hpp"

/**
 * @brief Construct a new Observer:: Observer object
 * 
 * @param p_log 
 */
Observer::Observer(ILog &p_log) : i_log(p_log)
{
    i_log.log(LOG_INFO, "Observer::%s", __func__);
}

/**
 * @brief Destroy the Observer:: Observer object
 * 
 */
Observer::~Observer()
{
    i_log.log(LOG_INFO, "Observer::%s", __func__);
}

/**
 * @brief todo
 * useless for the moment -> TODO : delete it
 * 
 */
IObserver::eInit        Observer::init(void) // todo
{
    i_log.log(LOG_INFO, "Observer::%s", __func__);
    // todo
    return IObserver::eInit::SUCCESS;
}

/**
 * @brief todo 
 * useless for the moment -> TODO : delete it
 * 
 * @param p_sigNum 
 * @return IObserver::eStop 
 */
IObserver::eStop        Observer::stop(int p_sigNum)
{
    i_log.log(LOG_INFO, "Observer::%s", __func__);
    // todo
    (void)p_sigNum;
    return IObserver::eStop::SUCCESS;
}