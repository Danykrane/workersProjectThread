#include "workerlock.h"

workerLock::workerLock()
{

}

void workerLock::lock()
{
    m_mutex.lock();
}

void workerLock::unlock()
{
    m_mutex.unlock();
}
