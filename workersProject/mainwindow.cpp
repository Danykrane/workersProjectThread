#include "mainwindow.h"
#include "workers/otherworkers.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#include <QButtonGroup>

#include <QDebug>


enum workerNum { firstWorker = 0,
                 secondWorker = 1,
                 thirdWorker = 2};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWidgets();
}

MainWindow::~MainWindow()
{
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
    m_workers.push_back(new FirstWorker(this, firstWorker));
    m_workers.push_back(new SecondWorker(this, secondWorker));
    m_workers.push_back(new ThirdWorker(this, thirdWorker, 1000));


    connect(runBtn, &QPushButton::clicked, [=]() {
        for (const auto &worker : m_workers) {
            worker->onExec();
        }
    });

    connect(stopBtn, &QPushButton::clicked, [=]() {
        for (const auto &worker : m_workers) {
            worker->onClose();
        }
    });

    for (const auto &elem : m_nameBtnsThread.values()) {
        connect(elem, &QPushButton::clicked, [=]() {
            bool status = elem->isChecked();
            m_workers.at(m_nameBtnsThread.key(elem))->setStatus(status);
        });
    }


    setCentralWidget(mainlayer->parentWidget());
}
