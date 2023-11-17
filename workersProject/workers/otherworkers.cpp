#include "otherworkers.h"

#include <QEventLoop>
#include <QThread>

#include <QAbstractEventDispatcher>

#include <QRandomGenerator>
#include <QDebug>

//---------------------------------------------------------------- First Worker

FirstWorker::FirstWorker(int id)
    : BaseWorker(id)
    , m_thread(new QThread)
{
    m_thread.get()->setObjectName("FirstWorkerThread");

    QEventLoop loop;

    QObject::connect(m_thread.get(),
                     &QThread::started,
                     &loop,
                     &QEventLoop::quit,
                     Qt::QueuedConnection);

    m_thread->start();

    loop.exec();

}

FirstWorker::~FirstWorker()
{
//    qDebug() << "Деструктор FirstWorker";
    m_thread->quit();
    m_thread->wait();
    m_thread->deleteLater();
}

void FirstWorker::onExec()
{
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
//    qDebug() << "first exec";
}

void FirstWorker::onClose()
{
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
//    qDebug() << "first close";
}

void FirstWorker::runThread()
{

//    qDebug() << "first runThread";
}


//------------------------------------------------------ GeneratorWorker Worker
GeneratorWorker::GeneratorWorker(int id)
    : BaseWorker(id)
    , m_thread(new QThread)
{
    m_thread.get()->setObjectName("GeneratorWorkerThread");
}

GeneratorWorker::~GeneratorWorker()
{
//    qDebug() << "Деструктор GeneratorWorkerThread";
    m_thread->quit();
    m_thread->wait();
    m_thread->deleteLater();
}

uint32_t GeneratorWorker::generateNum()
{
    return QRandomGenerator::global()->bounded(256);
}

//--------------------------------------------------------------- Second Worker
SecondWorker::SecondWorker(int id)
    : GeneratorWorker(id)
{
    m_thread.get()->setObjectName("SecondThread");

    QEventLoop loop;
    QObject::connect(m_thread.get(),
                     &QThread::started,
                     &loop,
                     &QEventLoop::quit,
                     Qt::QueuedConnection);

    m_thread->start();

    loop.exec();

}

void SecondWorker::onExec()
{
    if (!getSatus()) {
        // если статус подключения false
        return;
    }

    uint32_t genNum = 0;
    auto generate = [&genNum, this]() -> void {
        genNum = generateNum();
    };

    QMetaObject::invokeMethod(
        QAbstractEventDispatcher::instance(m_thread.get()),
        generate, Qt::QueuedConnection);

}

void SecondWorker::onClose()
{
      if (!getSatus()) {
        // если статус подключения false
        return;
      }
//  qDebug() << "SecondWorker close";
}

void SecondWorker::runThread()
{

//  qDebug() << "SecondWorker runThread";
}


//---------------------------------------------------------------- Third Worker


ThirdWorker::ThirdWorker(int id, int waitMsec)
    : GeneratorWorker(id)
    , m_waitMsec(waitMsec)
{
      m_thread.get()->setObjectName("ThirdWorkerThread");

      QEventLoop loop;
      QObject::connect(m_thread.get(),
                       &QThread::started,
                       &loop,
                       &QEventLoop::quit,
                       Qt::QueuedConnection);

      m_thread->start();

      loop.exec();


}

void ThirdWorker::onExec()
{
    if (!getSatus()) {
        // если статус подключения false
        return;
    }

//    uint32_t genNum;
//    auto generate = [&genNum, this]() -> void {
//        genNum = generateNum();
//    };

//    QMetaObject::invokeMethod(
//        QAbstractEventDispatcher::instance(m_thread.get()),
//                                           generate, Qt::QueuedConnection);
//    qDebug() << "third exec";
}

void ThirdWorker::onClose()
{
    if (!getSatus()) {
        // если статус подключения false
        return;
    }
//    qDebug() << "third close";
}

void ThirdWorker::runThread()
{

}


