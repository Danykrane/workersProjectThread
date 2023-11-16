#include "otherworkers.h"

#include <QThread>

#include <QDebug>

//---------------------------------------------------------------- First Worker

FirstWorker::FirstWorker(QObject *parent, int id)
    : BaseWorker(parent, id)
    , m_thread(new QThread)
{
    m_thread.get()->setObjectName("FirstWorkerThread");
    runThread();
}

void FirstWorker::onExec()
{
    qDebug() << "first exec";
}

void FirstWorker::onClose()
{
    qDebug() << "first close";
}

void FirstWorker::runThread()
{
    qDebug() << "first runThread";
}


//------------------------------------------------------ GeneratorWorker Worker
GeneratorWorker::GeneratorWorker(QObject *parent, int id)
    : BaseWorker(parent, id)
    , m_thread(new QThread)
{
    m_thread.get()->setObjectName("GeneratorWorkerThread");
}

void GeneratorWorker::onExec()
{
    qDebug() << "GeneratorWorker exec";
}

void GeneratorWorker::onClose()
{
    qDebug() << "GeneratorWorker close";
}

void GeneratorWorker::runThread()
{
    qDebug() << "GeneratorWorker runThread";
}
//--------------------------------------------------------------- Second Worker
SecondWorker::SecondWorker(QObject *parent, int id)
    : GeneratorWorker(parent, id)
{
    m_thread.get()->setObjectName("SecondThread");
    runThread();
}

void SecondWorker::onExec()
{
      qDebug() << "SecondWorker exec";
}

void SecondWorker::onClose()
{
  qDebug() << "SecondWorker close";
}

void SecondWorker::runThread()
{
  qDebug() << "SecondWorker runThread";
}


//---------------------------------------------------------------- Third Worker


ThirdWorker::ThirdWorker(QObject *parent, int id, int waitMsec)
    : GeneratorWorker(parent, id)
    , m_waitMsec(waitMsec)
{
    m_thread.get()->setObjectName("ThirdWorkerThread");
    runThread();

}

void ThirdWorker::onExec()
{
    qDebug() << "third exec";
}

void ThirdWorker::onClose()
{
    qDebug() << "third close";
}

void ThirdWorker::runThread()
{
    qDebug() << "third runThread";
}


