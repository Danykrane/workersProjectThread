#ifndef BASEWORKER_H
#define BASEWORKER_H

#include <QObject>

#include "workerlock.h"

class workerLock;
class BaseWorker : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief BaseWorker - конструктор базового класса
     * \param parent - родитель
     * \param id - id Worker
     */
    explicit BaseWorker(QObject *parent = nullptr, int id = 0);

    /*!
     * \brief onExec - функция запуска выполнения основных действий
     */
    virtual void onExec() = 0;
    /*!
     * \brief onClose - функция остановки
     */
    virtual void onClose() = 0;

    /*!
     * \brief setStatus - задать статус воркеру
     */
    void setStatus(bool value);

    /*!
     * \brief getSatus - получить статус воркера
     * \return
     */
    bool getSatus();

protected:
    /*!
     * \brief runThread - ф-ия запуска потока в дочернем классе
     */
    virtual void runThread() = 0;
public:
    /*!
     * \brief lockerMutex - мбютекс
     */
    QScopedPointer<workerLock> lockerMutex;
private:
    // workerNum::0 \ 1 \ 2
    int m_id;
    bool m_status = false;
};

#endif // BASEWORKER_H
