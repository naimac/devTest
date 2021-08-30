#include "statusReceiver.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mock/mock_libc.hpp"

#include "mock/mock_iLog.hpp"
#include "mock/mockAgentStatusReceiver.hpp"

#include "json.hpp"

#define SLEEP_DURATION 5

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;


MOCK_LIBC_METHOD3(socket, int(int __domain, int __type, int __protocol));
MOCK_LIBC_METHOD3(bind, int(int __socketfd, const struct sockaddr *__addr, socklen_t __addrlen));
MOCK_LIBC_METHOD1(close, int(int __fd));

std::priority_queue<Event, std::vector<Event>, compareEventPriority> *g_eventList;

TEST(StatusReceiver, SUCCESS)
{
    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== Start test 1 : StatusReceiverSucceed ====================");

    StatusReceiver l_statusReceiver(g_eventList, l_mock_ilog);

    EXPECT_CALL(MOCK_LIBC_INSTANCE(socket), socket(_,_,_))
        .WillOnce(
            Return (1)
        );

    char *l_jsonStr = "{\"protobuf_host\" : \"127.0.0.1\", \"protobuf_port\" : 2424}";
    nlohmann::json l_json = nlohmann::json::parse(l_jsonStr);

    EXPECT_CALL(MOCK_LIBC_INSTANCE(bind), bind(_,_,_))
        .WillOnce(
            Return (0)
        );

    EXPECT_EQ(l_statusReceiver.init(l_json), IStatusReceiver::eInit::SUCCESS);
    EXPECT_EQ(l_statusReceiver.start(), IStatusReceiver::eStart::SUCCESS);
    EXPECT_EQ(l_statusReceiver.stop(SIGTERM), IStatusReceiver::eStop::SUCCESS);
}

TEST(StatusReceiver, FAILURE)
{
    Mock_ILog l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== Start test 2 : StatusReceiverFailure ====================");

    StatusReceiver l_statusReceiver(g_eventList, l_mock_ilog);

    // json configuration file with good format and informations are missing
    char *l_jsonStr_invalid = "{}";
    nlohmann::json l_json_invalid = nlohmann::json::parse(l_jsonStr_invalid);

    // json configuration file with good format and informations are present
    char *l_jsonStr_valid = "{\"protobuf_host\" : \"127.0.0.1\", \"protobuf_port\" : 2424}";
    nlohmann::json l_json_valid = nlohmann::json::parse(l_jsonStr_valid);

    EXPECT_CALL(MOCK_LIBC_INSTANCE(socket), socket(_,_,_))
        .WillOnce(
            Return (-1)
        )
        .WillOnce(
            Return (1)
        );

    EXPECT_CALL(MOCK_LIBC_INSTANCE(bind), bind(_,_,_))
        .WillOnce(
            Return (-1)
        );

    EXPECT_EQ(l_statusReceiver.init(l_json_invalid), IStatusReceiver::eInit::FAILURE);
    EXPECT_EQ(l_statusReceiver.init(l_json_valid), IStatusReceiver::eInit::FAILURE);
    EXPECT_EQ(l_statusReceiver.init(l_json_valid), IStatusReceiver::eInit::FAILURE);
}