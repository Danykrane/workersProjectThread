#include "baseworker.h"

BaseWorker::BaseWorker(QObject *parent, int id)
    : QObject(parent)
    , lockerMutex(new workerLock())
    , m_id(id)
{

}

void BaseWorker::setStatus(bool value)
{
    m_status = value;
}

bool BaseWorker::getSatus()
{
    return m_status;
}
