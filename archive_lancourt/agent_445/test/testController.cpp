#include "controller.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock/mockAgentConfigReceiver.hpp"
#include "mock/mockAgentStatusReceiver.hpp"
#include "mock/mockAgentLauncher.hpp"
#include "mock/mockAgentStopper.hpp"
#include "mock/mockAgentObserver.hpp"

#include "mock/mock_iLog.hpp"

#include "json.hpp"

#define SLEEP_DURATION 5

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

std::string        p_jsonString  = "{\"id\": 1,\"protobuf_port\": 2424, \"protobuf_host\": \"127.0.0.1\",\"netconfServer.port\": 4242,\"netconfServer.address\": \"0.0.0.0\",\"netconfServer.schemasPath\": \"/home/airbus/workspace/product/etc/netconf/schemas\",\"netconfServer.privateRsaKeyPath\": \"/home/airbus/workspace/product/etc/netconf/data/key_rsa\",\"netconfServer.privateDsaKeyPath\": \"/home/airbus/workspace/product/etc/netconf/data/key_dsa\",\"netconfServer.acceptTimeout\": 35,\"netconfServer.pollTimeout\": 100,\"netconfServer.sshClients\":[{\"username\":\"local\", \"publicKeyPath\":\"/home/airbus/workspace/product/etc/netconf/data/key_rsa.pub\"}],\"programPath\": [{\"capture\":\"/home/airbus/workspace/product/bin/capture-debug\",\"vision\":\"/home/airbus/workspace/product/bin/vision-debug\"}]}";
nlohmann::json     p_networkConf = nlohmann::json::parse(p_jsonString);

TEST(Controller_INIT_STOP, SUCCESS)
{
    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);

    std::priority_queue<Event, std::vector<Event>, compareEventPriority> *g_eventList = nullptr;

    l_mock_ilog.LOG(LOG_DEBUG, "==================== Start test 1 : ControllerSucceed ====================");

    MockAgentLauncher       l_mockLauncher;
    MockAgentConfigReceiver l_mockConfigReceiver;
    MockAgentStatusReceiver l_mockStatusReceiver;
    MockAgentStopper        l_mockStopper;
    MockAgentObserver       l_mockObserver;

    std::list<pid_t>        l_modulePidList;
    // l_modulePidList.emplace_back((pid_t)666); // PUSH BACK THE PID PROCESS

    Controller l_controllerInstance(g_eventList,
                                    l_mockConfigReceiver,
                                    l_mockStatusReceiver,
                                    l_mockLauncher,
                                    l_mockStopper,
                                    l_mockObserver,
                                    l_mock_ilog);


    // ------------------------------------------- init ------------------------------------------- //

    EXPECT_CALL(l_mockConfigReceiver, init(_))
        .WillOnce(
            Invoke(
                [&](nlohmann::json p_json) -> IConfigReceiver::eInit {
                    (void)p_json;
                    l_mock_ilog.LOG(LOG_DEBUG, "init configReceiver");
                    return IConfigReceiver::eInit::SUCCESS;
                }));

    EXPECT_CALL(l_mockStatusReceiver, init(_))
        .WillOnce(
            Invoke(
                [&](nlohmann::json p_json) -> IStatusReceiver::eInit {
                    l_mock_ilog.LOG(LOG_DEBUG, "init statusReceiver");
                    return IStatusReceiver::eInit::SUCCESS;
                }));

    EXPECT_CALL(l_mockLauncher, init())
        .WillOnce(
            Invoke(
                [&]() -> ILauncher::eInit {
                    l_mock_ilog.LOG(LOG_DEBUG, "init launcher");
                    return ILauncher::eInit::SUCCESS;
                }));

    EXPECT_CALL(l_mockStopper, init())
        .WillOnce(
            Invoke(
                [&]() -> IStopper::eInit {
                    l_mock_ilog.LOG(LOG_DEBUG, "init stopper");
                    return IStopper::eInit::SUCCESS;
                }));

    EXPECT_CALL(l_mockObserver, init())
        .WillOnce(
            Invoke(
                [&]() -> IObserver::eInit {
                    l_mock_ilog.LOG(LOG_DEBUG, "init observer");
                    return IObserver::eInit::SUCCESS;
                }));

    EXPECT_EQ(l_controllerInstance.init(p_networkConf), IController::eInit::SUCCESS);

    // ------------------------------------------- stop ------------------------------------------- //

    // EXPECT_CALL(l_mockStopper, stopModule(_))
    //     .WillOnce(
    //         Invoke(
    //             [&](std::list<pid_t> p_modulePidList) -> IStopper::eStopModule {
    //                 l_mock_ilog.LOG(LOG_DEBUG, "stop module");
    //                 EXPECT_EQ(p_modulePidList, l_modulePidList);
    //                 return IStopper::eStopModule::SUCCESS;
    //             }));

    EXPECT_CALL(l_mockConfigReceiver, stop(_))
        .WillOnce(
            Invoke(
                [&](int p_idSignal) -> IConfigReceiver::eStop {
                    EXPECT_EQ(p_idSignal, 2);
                    l_mock_ilog.LOG(LOG_DEBUG, "stop configReceiver");
                    return IConfigReceiver::eStop::SUCCESS;
                }));

    EXPECT_CALL(l_mockStatusReceiver, stop(_))
        .WillOnce(
            Invoke(
                [&](int p_idSignal) -> IStatusReceiver::eStop {
                    EXPECT_EQ(p_idSignal, 2);
                    l_mock_ilog.LOG(LOG_DEBUG, "stop statusReceiver");
                    return IStatusReceiver::eStop::SUCCESS;
                }));
    EXPECT_CALL(l_mockLauncher, stop(_))
        .WillOnce(
            Invoke(
                [&](int p_idSignal) -> ILauncher::eStop {
                    EXPECT_EQ(p_idSignal, 2);
                    l_mock_ilog.LOG(LOG_DEBUG, "stop launcher");
                    return ILauncher::eStop::SUCCESS;
                }));

    EXPECT_CALL(l_mockObserver, stop(_))
        .WillOnce(
            Invoke(
                [&](int p_idSignal) -> IObserver::eStop {
                    EXPECT_EQ(p_idSignal, 2);
                    l_mock_ilog.LOG(LOG_DEBUG, "stop observer");
                    return IObserver::eStop::SUCCESS;
                }));

    EXPECT_EQ(l_controllerInstance.stopAll(2), IController::eStopAll::SUCCESS);
}