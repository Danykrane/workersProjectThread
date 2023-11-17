#ifndef OTHERWORKERS_H
#define OTHERWORKERS_H

#include "baseworker.h"
#include <QVector>

class QThread;
/*!
 * \brief Класс проверщика и хранителя данных
 */
class FirstWorker : public BaseWorker
{
public:
    explicit FirstWorker(int id = 0);

    ~FirstWorker() override;

    void onExec() override;
    void onClose() override;

    void setValue(int value);
    QVector<int> generatedValues();

private:
    void runThread() override;
    bool checkValueAnitherThread(int value);

private:
    QVector<int> m_generatedValues;
    QScopedPointer<QThread> m_thread;
};


/*!
 * \brief Класс генератора данных (2 & 3 worker)
 */
class GeneratorWorker : public BaseWorker
{
public:
    explicit GeneratorWorker(int id = 3);
    ~GeneratorWorker() override;

    uint32_t generateNum();

protected:
    QScopedPointer<QThread> m_thread;
};

/*!
 * \brief Класс генератора данных (2 worker)
 */
class SecondWorker : public GeneratorWorker
{
public:
    explicit SecondWorker(int id = 1);

    void onExec() override;
    void onClose() override;

private:
    void runThread() override;
};

/*!
 * \brief Класс генератора данных (3 worker)
 */
class ThirdWorker : public GeneratorWorker
{
public:
    explicit ThirdWorker(int id = 2, int waitMsec = 0);

    void onExec() override;
    void onClose() override;

    void waitSomeMsec(int waitMsec);

private:
    void runThread() override;

private:
    int m_waitMsec;

};

#endif // OTHERWORKERS_H
