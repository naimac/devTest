#include "configReceiver.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock/mock_iLog.hpp"
#include "mock/mock_iNetconfServer.hpp"
#include "mock/mockAgentConfigReceiver.hpp"

#include "json.hpp"

#define SLEEP_DURATION 5

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

// nlohmann::json     p_networkConf = nlohmann::json::parse(p_jsonString);

std::priority_queue<Event, std::vector<Event>, compareEventPriority> *g_eventList;

TEST(ConfigReceiver, SUCCESS)
{
    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== Start test 1 : ConfigReceiverSucceed ====================");

    Mock_INetconfServer l_mockNetconfServer;
    ConfigReceiver l_configReceiver(l_mockNetconfServer, g_eventList, l_mock_ilog);

    EXPECT_CALL(l_mockNetconfServer, init(_)) // test 1
        .WillOnce(
            Invoke([&](const nlohmann::json &p_json) -> INetconfServer::eInit {
                return INetconfServer::eInit::SUCCESS;
            }));

    EXPECT_CALL(l_mockNetconfServer, loadModule(_, _)) // test 1
        .WillOnce(Invoke([&](const std::string &p_module, const std::string &p_revision) -> INetconfServer::eLoadModule {
            EXPECT_EQ(p_module, "magellan-agent");
            EXPECT_EQ(p_revision, "");
            return INetconfServer::eLoadModule::SUCCESS;
        }));

    EXPECT_CALL(l_mockNetconfServer, setEditCallBack(_))
        .WillOnce(
            Invoke([&](std::function<INetconfServer::eEditCallBack(nc_session & p_session, lyd_node * p_node)> p_editCallBack) -> void {
                return;
            }));

    EXPECT_CALL(l_mockNetconfServer, stop()) // test 1
        .WillOnce(Invoke([&]() -> INetconfServer::eStop {
            return INetconfServer::eStop::SUCCESS;
        }))
        .WillOnce(Invoke([&]() -> INetconfServer::eStop {
            return INetconfServer::eStop::SUCCESS;
        }));


    nlohmann::json p_json;
    EXPECT_EQ(l_configReceiver.init(p_json), IConfigReceiver::eInit::SUCCESS);
    EXPECT_EQ(l_configReceiver.stop(SIGTERM), IConfigReceiver::eStop::SUCCESS);
}

TEST(ConfigReceiver, FAILURE)
{
    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== Start test 2 : ConfigReceiverFailure ====================");

    Mock_INetconfServer     l_mockNetconfServer;
    ConfigReceiver          l_configReceiver(l_mockNetconfServer, g_eventList, l_mock_ilog);

    EXPECT_CALL(l_mockNetconfServer, init(_))
        .WillOnce(
            Invoke([&](const nlohmann::json &p_json) -> INetconfServer::eInit {
                return INetconfServer::eInit::SUCCESS;
            }))
        .WillOnce(
            Invoke([&](const nlohmann::json &p_json) -> INetconfServer::eInit {
                return INetconfServer::eInit::FAIL;
            }));

    EXPECT_CALL(l_mockNetconfServer, loadModule(_, _))
        .WillOnce(Invoke([&](const std::string &p_module, const std::string &p_revision) -> INetconfServer::eLoadModule {
            return INetconfServer::eLoadModule::FAIL;
        }));

    EXPECT_CALL(l_mockNetconfServer, stop()) // test 1
        .WillOnce(Invoke([&]() -> INetconfServer::eStop {
            return INetconfServer::eStop::FAIL;
        }));

    nlohmann::json p_json;
    EXPECT_EQ(l_configReceiver.init(p_json), IConfigReceiver::eInit::FAILURE);
    EXPECT_EQ(l_configReceiver.init(p_json), IConfigReceiver::eInit::FAILURE);
}