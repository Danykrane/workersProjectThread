#ifndef WORKERLOCK_H
#define WORKERLOCK_H

#include <QMutex>

class workerLock
{
public:
    workerLock();
    void lock();
    void unlock();

private:
    QMutex m_mutex;
};

#endif // WORKERLOCK_H
