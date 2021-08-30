#include "observer.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock/mock_iLog.hpp"

#include "json.hpp" // in case

#define SLEEP_DURATION 5 // in case

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

// no case when it returns failure

TEST(Observer, SUCCESS)
{
    Mock_ILog   l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== TEST OBSERVER.SUCCESS ====================");

    Observer l_observer(l_mock_ilog);

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> l_observer.init");
    EXPECT_EQ(l_observer.init(), IObserver::eInit::SUCCESS);

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> l_observer.stop");
    EXPECT_EQ(l_observer.stop(SIGTERM), IObserver::eStop::SUCCESS);
}