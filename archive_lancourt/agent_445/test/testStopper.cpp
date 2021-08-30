#include "stopper.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "mock/mock_iLog.hpp"
#include "mock/mock_libc.hpp"

#include <signal.h>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

MOCK_LIBC_METHOD2(kill, int(pid_t, int));
// MOCK_LIBC_METHOD2(signal, sighandler_t(int, sighandler_t));

TEST(Stopper, SUCCESS)
{
    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== TEST STOPPER.SUCCESS ====================");

    Stopper l_stopper(l_mock_ilog);
    
    std::list<pid_t> p_modulePidList;
    p_modulePidList.emplace_back(36); // fake_pid

    // EXPECT_CALL(MOCK_LIBC_INSTANCE(signal), signal(_, _))
    //     .WillOnce(
    //         Invoke(
    //             [&](int p_signum, sighandler_t p_handler) -> sighandler_t {
    //                 EXPECT_EQ(p_signum, SIGTERM);
    //                 EXPECT_NEQ(p_handler, ???);
    //                 return ???;
    //             }));

    EXPECT_CALL(MOCK_LIBC_INSTANCE(kill), kill(_, _))
        .WillOnce(
            Invoke(
                [&](pid_t p_pid, int p_sigNum) -> int {
                    EXPECT_EQ(p_pid, p_modulePidList.front());
                    EXPECT_EQ(p_sigNum, SIGTERM);
                    return 0;
                }));

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [stopper.success.test1] l_stopper.init");
    EXPECT_EQ(l_stopper.init(), IStopper::eInit::SUCCESS);

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [stopper.success.test1] l_stopper.stopModule");
    EXPECT_EQ(l_stopper.stopModule(p_modulePidList), IStopper::eStopModule::SUCCESS);
}

TEST(Stopper, FAILURE)
{
    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== TEST STOPPER.FAIL ====================");

    Stopper l_stopper(l_mock_ilog);
    
    std::list<pid_t> p_modulePidList;
    p_modulePidList.emplace_back(36); // fake_pid

    EXPECT_CALL(MOCK_LIBC_INSTANCE(kill), kill(_, _))
        .WillOnce(
            Invoke(
                [&](pid_t p_pid, int p_sigNum) -> int {
                    EXPECT_EQ(p_pid, p_modulePidList.front());
                    EXPECT_EQ(p_sigNum, SIGTERM);
                    return -1;
                }));

// stopper.init returs always SUCCESS
    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [stopper.failure.test2] l_stopper.init -> SUCCESS");
    EXPECT_EQ(l_stopper.init(), IStopper::eInit::SUCCESS);

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [stopper.failure.test2] l_stopper.stopModule -> FAILURE ");
    EXPECT_EQ(l_stopper.stopModule(p_modulePidList), IStopper::eStopModule::FAILURE);
}