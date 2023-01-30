/*
 * 当前Colorbuffer操作都记录了其顺序，用于在客户端还原，此顺序记录在colorbuffer的共享内存中，并通过共享内存的锁进行保护
 * 为将共享内存锁的粒度降低，所以，共享内存锁只有进行自加执行顺序时会上锁
 * 但，为保证一个进程中多个线程同时操作同一个colorbuffer对象，且到达客户端的顺序必须是小的在前面，大的在后面，所以这些colorbuffer的操作在同一个进程中需互斥
 * 否则，会出现A线程操作colorbuffer并顺序+1，B线程操作同一个colorbuffer顺序再次+1，但是B线程先将此colorbuffer指令执行完并投递到VmiAgent，则客户端还原时将出错
 */
#include <mutex>

class VmiProcessLock {
public:
    VmiProcessLock() {
        m_mutex.lock();
    }
    ~VmiProcessLock() {
        m_mutex.unlock();
    }
private:
    static std::mutex m_mutex;
};