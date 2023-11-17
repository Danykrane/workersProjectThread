#include "baseworker.h"

#include <QDebug>

BaseWorker::BaseWorker(int id):
    lockerMutex(new workerLock())
    , m_id(id)
{

}

BaseWorker::~BaseWorker()
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
