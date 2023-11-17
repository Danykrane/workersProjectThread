#include "mainwindow.h"
#include "workers/otherworkers.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#include <QButtonGroup>

#include <QDebug>

namespace {

enum workerNum { firstWorker = 0,
                 secondWorker = 1,
                 thirdWorker = 2};

QMap<workerNum, QString> workerNames{
    {firstWorker, "First Worker"},
    {secondWorker, "Second Worker"},
    {thirdWorker, "Third Worker"}
};

} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWidgets();
}

MainWindow::~MainWindow()
{
    for (const auto &item : m_workers) {
        delete item;
    }
}

void MainWindow::createWidgets()
{
    // mainLayer
    QVBoxLayout *mainlayer = new QVBoxLayout(new QWidget);

    // Btns Layer
    QHBoxLayout *btnThreadLayer = new QHBoxLayout(new QWidget);

    // BtnsWidget
    m_nameBtnsThread[workerNum::firstWorker] = new QPushButton("First Worker(checker)");
    m_nameBtnsThread[workerNum::secondWorker] = new QPushButton("Second Worker(generator)");
    m_nameBtnsThread[workerNum::thirdWorker] = new QPushButton("Third Worker(generator + stoper)");

    for (const auto &elem : m_nameBtnsThread.values()) {
        btnThreadLayer->addWidget(elem);
        elem->setCheckable(true);
    }
    mainlayer->addWidget(btnThreadLayer->parentWidget());

    //TextLayer
    QTextEdit *textField = new QTextEdit;
    mainlayer->addWidget(textField);

    //Run Quiet buttons
    QPushButton *runBtn = new QPushButton("RUN");
    QPushButton *stopBtn = new QPushButton("STOP");
    runBtn->setCheckable(true);
    stopBtn->setCheckable(true);

    QButtonGroup *groubBtn = new QButtonGroup;
    groubBtn->setExclusive(true);
    groubBtn->addButton(runBtn);
    groubBtn->addButton(stopBtn);


    QHBoxLayout *runStopLayer = new QHBoxLayout(new QWidget);
    runStopLayer->addWidget(runBtn);
    runStopLayer->addWidget(stopBtn);

    QPushButton *clearBtn = new QPushButton("clear");
    mainlayer->addWidget(clearBtn, 0, Qt::AlignRight);
    connect(clearBtn, &QPushButton::clicked, textField, &QTextEdit::clear);

    mainlayer->addWidget(runStopLayer->parentWidget());

    // Заполняем m_workers
    m_workers.push_back(new FirstWorker(firstWorker));
    m_workers.push_back(new SecondWorker(secondWorker));
    m_workers.push_back(new ThirdWorker(thirdWorker, 1000));


    connect(runBtn, &QPushButton::clicked, [=]() {
        runBtn->setEnabled(false);

        for (const auto &elem : m_nameBtnsThread.values()) {
            if (elem->isChecked()) {
                elem->setEnabled(false);
            }
        }
        for (const auto &worker : m_workers) {
            worker->onExec();
        }

    });

    connect(stopBtn, &QPushButton::clicked, [=]() {
        runBtn->setEnabled(true);


        for (const auto &worker : m_workers) {
            int indexWorker = m_workers.indexOf(worker);
            bool state = m_nameBtnsThread.value(indexWorker)->isEnabled();
            if (!state) {
                worker->onClose();
            }
        }

        for (const auto &elem : m_nameBtnsThread.values()) {
            elem->setEnabled(true);
        }

    });

    for (const auto &elem : m_nameBtnsThread.values()) {
        connect(elem, &QPushButton::clicked, [=]() {
            bool status = elem->isChecked();
            m_workers.at(m_nameBtnsThread.key(elem))->setStatus(status);
//            auto enumWorker = m_nameBtnsThread.key(elem);
//            qDebug() << workerNames.value(static_cast<workerNum>(enumWorker)) << "status" << status;
        });
    }


    setCentralWidget(mainlayer->parentWidget());
}

