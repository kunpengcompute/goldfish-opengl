#ifndef _TIME_RECORD_HELP_H
#define _TIME_RECORD_HELP_H

#include <stdint.h>
#include <chrono>
#include <new>

#define IS_TIME_RECORD_OPEN 0
#if IS_TIME_RECORD_OPEN
class TimeRecordHelp {
public:
    TimeRecordHelp(uint32_t tid, uint32_t line, const char *functionName);
    ~TimeRecordHelp();
private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
    uint32_t m_tid = 0;
    uint32_t m_line = 0;
    const char* m_functionName = nullptr;
};
#define RECORD_TIME(addLine) TimeRecordHelp record(gettid(), __LINE__ + addLine, __FUNCTION__);
#else
#define RECORD_TIME(addLine)  
#endif

#endif