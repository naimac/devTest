#ifndef _MOCK_ILOG_HPP_
#define _MOCK_ILOG_HPP_

#include <gmock/gmock.h>
#include <fstream>
#include <cstdarg>

#include "Ilog.hpp"

#include <sys/time.h>
#include <ctime>

#ifdef __GNUC__
# include <cxxabi.h>
#endif

#include <string>

template <typename T>
std::string TypeToString__()
{
    using TR = typename std::remove_reference<T>::type;
    #ifdef __GNUC__
        char *demangle = abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr);
        std::string retStr = demangle;
        if (demangle != nullptr)
            std::free(demangle);
        else
            retStr = typeid(TR).name();
    #else
        std::string retStr = typeid(TR).name();
    #endif
    return retStr;
}

# define TypeToString(_x) TypeToString__<decltype(_x)>()

#define ILOG_TEST_FILE TypeToString(*this) + ".log"

class Mock_ILog : public Ilog
{

public:

    Mock_ILog(const std::string &p_filename)
    {
        i_fstream.open(p_filename);
        this->log(LOG_INFO, "==== START ====");
        return ;
    }

    ~Mock_ILog(void)
    {
        this->log(LOG_INFO, "====  END  ====");
        i_fstream.close();
        return ;
    }

    /**
     * @brief log in loggator method
     * 
     * @param p_pri 
     * @param p_fmt 
     * @param ... 
     */
    void log(int p_pri, const char *p_fmt, ...)
    {
        char buffer[2048];
        va_list vargs;

        va_start(vargs, p_fmt);
        int buffSize = std::vsnprintf(buffer, 2048, p_fmt, vargs);
        if (buffSize > 2048 - 1 || buffSize < 0)
            buffSize = 2048 - 1;
        va_end(vargs);

        struct timeval  now;
        struct tm       *tm;

        gettimeofday(&now, NULL);
        tm = localtime(&now.tv_sec);
        char buffer_time[64];
        sprintf(buffer_time, "%.4d/%.2d/%.2d %.2d:%.2d:%.2d.%.6ld ",
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec, now.tv_usec);

        i_fstream << buffer_time << syslogTypeToString(p_pri) << " " << std::string(buffer, 0, buffSize) << std::endl;
    }

private:

    std::ofstream i_fstream;

    const char *syslogTypeToString(int p_type)
    {
        switch (p_type)
        {
            case LOG_EMERG:
                return "[EMERG]";
            case LOG_ALERT:
                return "[ALERT]";
            case LOG_CRIT:
                return "[CRIT ]";
            case LOG_ERR:
                return "[ERROR]";
            case LOG_WARNING:
                return "[WARN ]";
            case LOG_NOTICE:
                return "[NOTIC]";
            case LOG_INFO:
                return "[INFO ]";
            case LOG_DEBUG:
                return "[DEBUG]";
            default:
                return "[DEBUG]";
        }
    }

};

#endif