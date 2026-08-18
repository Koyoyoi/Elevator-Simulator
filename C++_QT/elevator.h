#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QTimer>

class Elevator : public QObject
{
    Q_OBJECT

public:
    explicit Elevator(
        int id,
        int startFloor,
        QObject *parent = nullptr
    );

    int getId() const;
    int getCurrentFloor() const;
    bool isMoving() const;
    void display_floor();

public slots:
    void move(int current, int floor);
    void setCurrentFloor(int floor);

signals:
    void floorChanged(int floor);
    void statusChanged(const QString &status);

private slots:
    void moveOneFloor();

private:
    int m_id;
    int m_currentFloor;
    int m_targetFloor;

    bool m_moving;

    QTimer *m_timer;
};

#endif