#include "launcher.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// libc mock
#include "mock/mock_libc.hpp"
#include "mock/mock_iLog.hpp"

#include "json.hpp"
#include <sys/types.h> // fork
#include <unistd.h> // fork , execve

// #include "commonTools.hpp"

#define SLEEP_DURATION 5

extern char **environ;

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

MOCK_LIBC_METHOD0(fork, pid_t(void));
MOCK_LIBC_METHOD3(execve, int(const char *, const char **, const char **));

TEST(Launcher, Success)
{
    Mock_ILog   l_mock_ilog(ILOG_TEST_FILE);
    l_mock_ilog.LOG(LOG_DEBUG, "==================== Start test 1 : LauncherSucceed ====================");

    // g_fakeModule.id = 1;
    // g_fakeModule.name = "capture";
    // g_fakeModule.parameters = "{\"id\": 23, \"interface\": \"lo\", \"filter\": \"\", \"timeout\": 5, \"promiscMode\": 1, \"tstampType\": 0, \"immediateMode\": 0, \"sharedDataSize\": 300, \"sharedSize\": 10000}";
    // ;

    Module g_fakeModule;
    pid_t l_fakePid = 0;

    char *l_param[3];

    l_param[0] = "/home/airbus/workspace/product/bin/capture-debug";
    l_param[1] = "{\"id\": 23, \"interface\": \"lo\", \"filter\": \"\", \"timeout\": 5, \"promiscMode\": 1, \"tstampType\": 0, \"immediateMode\": 0, \"sharedDataSize\": 300, \"sharedSize\": 10000}";
    l_param[2] = nullptr;

    char *l_fakeEnvp[] = { "aaaa", "bbbb", "cccc" };

    Launcher    l_launcher(l_mock_ilog, l_fakeEnvp);

    // l_mock_ilog.LOG(LOG_DEBUG, "execution fork");
    // EXPECT_CALL(MOCK_LIBC_INSTANCE(fork), fork())
    //     .WillOnce(
    //         Invoke([]() -> pid_t {
    //             std::cout << "XXXXXXXXXXXXXXX" << std::endl;
    //             return 0;
    //         }));

    // EXPECT_CALL(MOCK_LIBC_INSTANCE(execve), execve(_, _, _))
    //     .WillOnce(
    //         Invoke([&](const char *p_fakeFilename, const char **p_fakeArgv, const char **p_fakeEnvp) -> int {
    //             l_mock_ilog.LOG(LOG_DEBUG, ">>>>>>>>> execution execve");
    //             EXPECT_EQ(p_fakeFilename, l_param[0]);
    //             EXPECT_EQ(p_fakeArgv, l_param);
    //             EXPECT_EQ(p_fakeEnvp, environ);
    //             return 0;
    //         }));

    EXPECT_EQ(l_launcher.init(), ILauncher::eInit::SUCCESS);   // empty function
    EXPECT_EQ(l_launcher.start(), ILauncher::eStart::SUCCESS); // useless
    // EXPECT_EQ(l_launcher.launchModule(g_fakeModule, &l_fakePid), ILauncher::eLaunchModule::SUCCESS);
    // EXPECT_EQ(l_launcher.stop(SIGTERM), ILauncher::eStop::SUCCESS);
}