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

};
#endif // MAINWINDOW_H
