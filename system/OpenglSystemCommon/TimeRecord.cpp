#include "TimeRecord.h"
#include <log/log.h>
#include <new>
#include <string>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

TimeRecord::TimeRecord()
{
    ALOGI("TimeRecord mudule start");
    MkDir();
}

TimeRecord::~TimeRecord()
{
    if (m_pos != 0) {
        CommitMemory(gettid());
    }
    ALOGI("destroy function TimeRecord module");
    delete[] m_memory;
    if (m_file != nullptr) {
        fclose(m_file);
    }
    if (m_funcName != nullptr) {
        fclose(m_funcName);
    }
    ALOGI("TimeRecord mudule end");
}

void TimeRecord::UpdateInfoSync(uint32_t tid, uint32_t line, \
    const char* funcName, uint32_t consumed, uint64_t startTime, uint32_t opSize)
{
    if (m_memory == nullptr) {
        if (!InitMemory()) {
            ALOGE("Failed to alloc memory");
            return;
        }
    }
    uint32_t needSize = sizeof(tid) + sizeof(line) + sizeof(consumed) + sizeof(startTime) + sizeof(opSize);
    if (m_lastWrite == 0) {
        m_lastWrite = startTime;
    }
    const int64_t writeTimeout = 1000; // 1s
    if (m_TotalSize - m_pos < needSize || (int64_t)(startTime - m_lastWrite) > writeTimeout) {
        CommitMemory(tid);
        m_lastWrite = startTime;
    }
    uint32_t* writeInfo = reinterpret_cast<uint32_t*>(m_memory + m_pos);
    *writeInfo = tid;
    writeInfo++;
    *writeInfo = line;
    writeInfo++;
    *writeInfo = consumed;
    writeInfo++;
    *writeInfo = opSize;
    writeInfo++;
    uint64_t* startTimeInfo = reinterpret_cast<uint64_t *>(writeInfo);
    *startTimeInfo = startTime;
    m_pos += needSize;
    if (m_lineFuncName.find(line) == m_lineFuncName.end()) {
        ALOGI("func not exist previously, now create and write %s", funcName);
        WriteFuncInfo(line, funcName, tid);
        m_lineFuncName[line] = std::string(funcName);
    }
}

bool TimeRecord::InitMemory()
{
    if (m_memory != nullptr) {
        return true;
    }
    const uint32_t memorySize = 16 * 1024 * 1024; // 16M
    const uint32_t funcMemorySize = 1024 * 1024; // 1M
    m_memory = new (std::nothrow) uint8_t[memorySize];
    if (m_memory == nullptr) {
        ALOGE("Failed to malloc size:%u memory", memorySize);
        return false;
    }
    m_TotalSize = memorySize;
    m_pos = 0;

    func_memory = new (std::nothrow) uint8_t[funcMemorySize];
    if (func_memory == nullptr) {
        ALOGE("Failed to malloc size: %u funcMemory", funcMemorySize);
    }
    func_TotalSize = funcMemorySize;
    func_pos = 0;

    return true;
}

void TimeRecord::CommitMemory(uint32_t tid)
{
    WriteToFile(tid);
    m_pos = 0;
}

void TimeRecord::WriteToFile(uint32_t tid)
{
    if (m_file == nullptr) {
        const char* filePath = "/sdcard/perfData";
        uint32_t pid = getpid();
        if (access(filePath, F_OK | R_OK) == -1) {
            if (mkdir(filePath, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
                ALOGE("Failed to create folder:%s", filePath);
                return;
            }
        }
        std::string fileName = std::string(filePath) + "/" + std::to_string(pid) + "_" + std::to_string(tid) + ".data";
        m_file = fopen(fileName.c_str(), "w");
        if (m_file == nullptr) {
            ALOGE("Failed to open file:%s", fileName.c_str());
            return;
        }

        if (m_funcName == nullptr) {
            std::string fileName = std::string(filePath) + "/" + \
                std::to_string(pid) + "_"  + std::to_string(tid) + ".function";
            m_funcName = fopen(fileName.c_str(), "w");
            if (m_funcName == nullptr) {
                ALOGE("Failed to open file:%s", fileName.c_str());
                return;
            }
        }
    }

    if (m_funcName != nullptr && func_pos != 0) {
        if (fwrite(func_memory, func_pos, 1, m_funcName) != 1) {
            ALOGE("Failed to write func info from main-memory to file %u", func_pos);
            return;
        }
        fflush(m_funcName);
        func_pos = 0;
        ALOGI("Succeed write func info from main-memory to file");
    }

    ALOGI("commit memory to file, size:%u", m_pos);
    if (fwrite(m_memory, m_pos, 1, m_file) != 1) {
        ALOGE("Failed to write data size:%u", m_pos);
        return;
    }
    fflush(m_file);
}

void TimeRecord::WriteFuncInfo(uint32_t line, const char* function, uint32_t tid)
{
    if (m_funcName == nullptr) {
        const char* filePath = "/sdcard/perfData";
        uint32_t pid = getpid();
        if (access(filePath, F_OK | R_OK) == -1) {
            if (mkdir(filePath, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
                ALOGE("Failed to create folder:%s when write func info", filePath);
                uint32_t funcLen = strlen(function); // 此时若文件夹还没有创建好，则先把相关信息存到内存里，之后当识别出文件夹后统一进行存储
                uint32_t needSize = sizeof(line) + sizeof(funcLen) + strlen(function);
                uint32_t* writeInfo = reinterpret_cast<uint32_t*>(func_memory + func_pos);
                *writeInfo = line;
                writeInfo++;
                *writeInfo = funcLen;
                writeInfo++;
                uint8_t* funcNameInfo = reinterpret_cast<uint8_t *>(writeInfo);
                *funcNameInfo = *function;
                for (int i = 0; i < funcLen; ++i) {
                    funcNameInfo[i] = function[i];
                }
                func_pos += needSize;
                ALOGI("func info write to main-memory needsize=%u", needSize);
                return;
            }
        }
        std::string fileName = std::string(filePath) + "/" \
            + std::to_string(pid) + "_"  + std::to_string(tid) + ".function";
        m_funcName = fopen(fileName.c_str(), "w");
        if (m_funcName == nullptr) {
            ALOGE("Failed to open file:%s", fileName.c_str());
            return;
        }
    }
    if (func_pos != 0) {
        if (fwrite(func_memory, func_pos, 1, m_funcName) != 1) {
            ALOGE("Failed to write func info from main-memory to file %u", func_pos);
            return;
        }
        fflush(m_funcName);
        func_pos = 0;
        ALOGI("Succeed write func info from main-memory to file");
    }
    if (fwrite(&line, sizeof(uint32_t), 1, m_funcName) != 1) {
        ALOGE("Failed to write line info");
        return;
    }
    uint32_t funcLen = strlen(function);
    if (fwrite(&funcLen, sizeof(uint32_t), 1, m_funcName) != 1) {
        ALOGE("Failed to write function len");
        return;
    }
    if (fwrite(function, funcLen, 1, m_funcName) != 1) {
        ALOGE("Failed to write function name");
        return;
    }
    fflush(m_funcName);
    CommitMemory(tid);
}

void TimeRecord::MkDir()
{
    const char* filePath = "/sdcard/perfData";
    if (access(filePath, F_OK | R_OK) == -1) {
        ALOGE("folder already exist %s", filePath);
        if (mkdir(filePath, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
            ALOGE("Failed to create folder:%s when time module start", filePath);
            return;
        } else {
            ALOGE("create folder successfully");
        }
    } else {
        ALOGE("folder already exist");
    }
}