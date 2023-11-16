#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QList>
#include <QMap>

class QPushButton;
class BaseWorker;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createWidgets();
    void createConnections();

private:
    QMap<int, QPushButton *> m_nameBtnsThread;
    QList<BaseWorker*> m_workers;

    //TODO[new]:: заменить std::inique_ptr на QSqopedPointer
    //TODO[new]::указательна данные

};
#endif // MAINWINDOW_H
