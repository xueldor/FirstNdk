//
// Created by xue on 2020/6/3.
//

#ifndef FIRSTNDK_LOG_H
#define FIRSTNDK_LOG_H
class Log {
public:
    static void error(const char *pMessage, ...);

    static void warn(const char *pMessage, ...);

    static void info(const char *pMessage, ...);

    static void debug(const char *pMessage, ...);
};
#ifndef NDEBUG
    #define packt_Log_debug(...) Log::debug(__VA_ARGS__)
#else
    #define packt_Log_debug(...)
#endif

#endif //FIRSTNDK_LOG_H
