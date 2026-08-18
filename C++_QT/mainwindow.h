#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Elevator;
class QLineEdit;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QWidget *createElevatorWidget(Elevator *elevator);

private:
    Elevator *m_elevator1;
    Elevator *m_elevator2;
};

#endif