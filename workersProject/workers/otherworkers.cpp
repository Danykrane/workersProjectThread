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
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
    qDebug() << "first exec";
}

void FirstWorker::onClose()
{
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
    qDebug() << "first close";
}

void FirstWorker::runThread()
{
    m_thread->start();
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
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
    qDebug() << "GeneratorWorker exec";
}

void GeneratorWorker::onClose()
{
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
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
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
      qDebug() << "SecondWorker exec";
}

void SecondWorker::onClose()
{
      if (!getSatus()) {
        // если статус подключения false
        return;
      }
  qDebug() << "SecondWorker close";
}

void SecondWorker::runThread()
{
  m_thread->start();
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
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
    qDebug() << "third exec";
}

void ThirdWorker::onClose()
{
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
    qDebug() << "third close";
}

void ThirdWorker::runThread()
{
    m_thread->start();
    qDebug() << "third runThread";
}


