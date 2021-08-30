#include "agent.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock/mock_iLog.hpp"
#include "mock/mockAgentController.hpp"

#include "json.hpp"

#define SLEEP_DURATION 5

//using
using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

TEST(Agent, SUCCESS)
{

    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== TEST AGENT.SUCCESS ====================");

    MockAgentController         l_mockController;

    Agent                       l_agent(l_mockController, l_mock_ilog);

    EXPECT_CALL(l_mockController, init(_))
        .WillOnce(
            Invoke(
                [&](nlohmann::json p_json) -> IController::eInit {
                    l_mock_ilog.LOG(LOG_DEBUG, ">>> l_mockController.init(p_json) -> SUCCESS");
                    return (IController::eInit::SUCCESS);
                }));

    EXPECT_CALL(l_mockController, start())
        .WillOnce(
            Invoke(
                [&]() -> IController::eStart {
                    l_mock_ilog.LOG(LOG_DEBUG, ">>> l_mockController.start -> SUCCESS");
                    return (IController::eStart::SUCCESS);
                }));

    EXPECT_CALL(l_mockController, stopAll(_))
        .WillOnce(
            Invoke(
                [&](int p_sigNum) -> IController::eStopAll {
                    l_mock_ilog.LOG(LOG_DEBUG, ">>> l_mockController.stop(SIGTERM) -> SUCCESS");
                    EXPECT_EQ(p_sigNum, SIGTERM);
                    return (IController::eStopAll::SUCCESS);
                }));

    nlohmann::json p_json;
    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> l_agent.init -> SUCCESS");
    EXPECT_EQ(l_agent.init(p_json), IAgent::eInit::SUCCESS);

    std::thread l_thread([&]() {
        l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> New Thread calling l_agent.stop(SIGTERM)");
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
        l_agent.stop(SIGTERM);
    });
    
    l_thread.join(); // if missing, then error "abort"

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> l_agent.start -> SUCCESS");
    EXPECT_EQ(l_agent.start(), IAgent::eStart::SUCCESS);
}

TEST(Agent, FAILURE)
{
    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== TEST AGENT.FAIL ====================");

    MockAgentController         l_mockController;
    Agent                       l_agent(l_mockController, l_mock_ilog);

    EXPECT_CALL(l_mockController, init(_))
        .WillOnce( // test 1
            Invoke(
                [&](nlohmann::json p_json) -> IController::eInit {
                    l_mock_ilog.LOG(LOG_DEBUG, ">>> [agent.failure.test.1] l_mockController.init(p_json) -> FAILURE");
                    return (IController::eInit::FAILURE);
                }))
        .WillOnce( // test 2
            Invoke(
                [&](nlohmann::json p_json) -> IController::eInit {
                    l_mock_ilog.LOG(LOG_DEBUG, ">>> [agent.failure.test.2] l_mockController.init(p_json) -> SUCCESS");
                    return (IController::eInit::SUCCESS);
                }));

    EXPECT_CALL(l_mockController, start())
        .WillOnce( // test 2
            Invoke(
                [&]() -> IController::eStart {
                    l_mock_ilog.LOG(LOG_DEBUG, ">>> [agent.failure.test.2] l_mockController.start() -> FAILURE");
                    return (IController::eStart::FAILURE);
                }));

    EXPECT_CALL(l_mockController, stopAll(_)) // probably useless
        .WillOnce( // test 3
            Invoke(
                [&](int p_sigNum) -> IController::eStopAll {
                    l_mock_ilog.LOG(LOG_DEBUG, ">>> [agent.failure.test.1/2] l_mockController.stop() -> SUCCESS");
                    EXPECT_EQ(p_sigNum, SIGTERM);
                    return (IController::eStopAll::SUCCESS);
                }));

    nlohmann::json p_json;
    l_mock_ilog.LOG(LOG_DEBUG, "before expect_eq on l_agent.init");

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [agent.failure.test1] l_agent.init -> expect failure ");
    EXPECT_EQ(l_agent.init(p_json), IAgent::eInit::FAILURE); // test 1

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [agent.failure.test2] l_agent.init -> expect success ");
    EXPECT_EQ(l_agent.init(p_json), IAgent::eInit::SUCCESS); // test 2

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [agent.failure.test2] l_agent.start -> expect failure ");
    EXPECT_EQ(l_agent.start(), IAgent::eStart::FAILURE); // test 2 // pas de lancement de la boucle

    std::thread l_thread([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
        l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [agent.failure.test3] l_agent.stop(SIGTERM)");
        l_agent.stop(SIGTERM);
    });

    l_thread.join(); // if missing, then error "abort"    l_mock_ilog.LOG(LOG_DEBUG, "after  expect_eq l_agent.start()");
}

TEST(Agent, STOP_FAILURE)
{
    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== TEST AGENT.STOP_FAIL ====================");

    MockAgentController         l_mockController;
    Agent                       l_agent(l_mockController, l_mock_ilog);

    EXPECT_CALL(l_mockController, stopAll(_))
        .WillOnce( // test 3
            Invoke(
                [&](int p_sigNum) -> IController::eStopAll {
                    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [agent.stop_failure.test4] l_mockController.y6stop(SIGTERM)");
                    EXPECT_EQ(p_sigNum, SIGTERM);
                    return (IController::eStopAll::FAILURE);
                }));

    l_mock_ilog.LOG(LOG_DEBUG, "++++++++++++++++++++> [agent.stop_failure.test4] l_agent.stop(SIGTERM)");
    EXPECT_EQ(l_agent.stop(SIGTERM), Agent::eStop::FAILURE); // test 2
}