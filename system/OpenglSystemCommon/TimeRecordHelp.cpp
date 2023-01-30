#include "TimeRecordHelp.h"
#include "HostConnection.h" // 这里已经include了TimeRecord.h

#if IS_TIME_RECORD_OPEN
TimeRecordHelp::TimeRecordHelp(uint32_t tid, uint32_t line, const char *functionName) \
    : m_tid(tid), m_line(line), m_functionName(functionName)
{
    m_start = std::chrono::system_clock::now();
}

TimeRecordHelp::~TimeRecordHelp()
{
    using namespace std::chrono;
    auto end = std::chrono::system_clock::now();
    auto diff = end - m_start;
    uint32_t diffTime = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    auto now_ms = time_point_cast<milliseconds>(m_start);
    auto value = now_ms.time_since_epoch();
    uint64_t startTime = value.count();

    HostConnection *hostCon = HostConnection::get();
    uint32_t size = 0;
    if (hostCon->getOpSize != nullptr) {
        size = hostCon->getOpSize(hostCon->getHandle());
    }
    hostCon->UpdateCallInfo().UpdateInfoSync(m_tid, m_line, m_functionName, diffTime, startTime, size);
}
#endif