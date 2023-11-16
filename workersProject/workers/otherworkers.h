#ifndef OTHERWORKERS_H
#define OTHERWORKERS_H

#include "baseworker.h"
#include <QVector>

/*!
 * \brief Класс проверщика и хранитиля данных
 */
class FirstWorker : public BaseWorker
{
    Q_OBJECT
public:
    explicit FirstWorker(QObject *parent = nullptr, int id = 0);

    void onExec() override;
    void onClose() override;

    void setValue(int value);
    QVector<int> generatedValues();

private:
    void runThread() override;
    bool checkValueAnitherThread(int value);

private:
    QVector<int> m_generatedValues;
    std::unique_ptr<QThread> m_thread;
};


/*!
 * \brief Класс генератора данных (2 & 3 worker)
 */
class GeneratorWorker : public BaseWorker
{
    Q_OBJECT
public:
    explicit GeneratorWorker(QObject *parent = nullptr, int id = 3);

    void onExec() override;
    void onClose() override;

    int generateNum();

protected:
    void runThread() override;

protected:
    std::unique_ptr<QThread> m_thread;
};

/*!
 * \brief Класс генератора данных (2 worker)
 */
class SecondWorker : public GeneratorWorker
{
    Q_OBJECT
public:
    explicit SecondWorker(QObject *parent = nullptr, int id = 1);

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
    Q_OBJECT
public:
    explicit ThirdWorker(QObject *parent = nullptr, int id = 2, int waitMsec = 0);

    void onExec() override;
    void onClose() override;

    void waitSomeMsec(int waitMsec);

private:
    void runThread() override;

private:
    int m_waitMsec;

};

#endif // OTHERWORKERS_H
