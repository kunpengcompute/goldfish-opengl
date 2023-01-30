#ifndef _TIME_RECORD_H
#define _TIME_RECORD_H

#include <stdint.h>
#include <map>
#include <string>
class TimeRecord {
public:
    TimeRecord();
    void UpdateInfoSync(uint32_t tid, uint32_t line, \
        const char* funcName, uint32_t consumed, uint64_t startTime, uint32_t m_size);
    void WriteFileLast(uint32_t tid)
    {
        CommitMemory(tid);
    }
    void MkDir();
    ~TimeRecord();
private:
    bool InitMemory();
    void CommitMemory(uint32_t tid);
    void WriteToFile(uint32_t tid);
    void WriteFuncInfo(uint32_t line, const char* function, uint32_t tid);
    uint8_t* m_memory = nullptr;
    uint32_t m_pos = 0;
    uint32_t m_TotalSize = 0;
    uint8_t* func_memory = nullptr;
    uint32_t func_pos = 0;
    uint32_t func_TotalSize = 0;
    FILE* m_file = nullptr;
    FILE* m_funcName = nullptr;
    std::map<uint32_t, std::string> m_lineFuncName;
    uint64_t m_lastWrite = 0;
};

#endif