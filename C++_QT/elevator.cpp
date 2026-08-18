#include "elevator.h"

Elevator::Elevator(int id, int startFloor, QObject *parent) 
    : QObject(parent),
    m_id(id),
    m_currentFloor(startFloor),
    m_targetFloor(startFloor),
    m_moving(false)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);

    connect(m_timer, &QTimer::timeout, this, &Elevator::moveOneFloor);
}


int Elevator::getId() const
{
    return m_id;
}


int Elevator::getCurrentFloor() const
{
    return m_currentFloor;
}


bool Elevator::isMoving() const
{
    return m_moving;
}


void Elevator::move(int current, int floor)
{
    if (floor < 1 || floor > 10)
        return;

    if (m_moving)
        return;

    m_currentFloor = current;
    m_targetFloor = floor;

    if (m_currentFloor == m_targetFloor) {
        display_floor();
        emit statusChanged("Arrived");
        return;
    }

    m_moving = true;
    emit statusChanged("Moving...");
    m_timer->start();
}


void Elevator::moveOneFloor()
{
    if (m_currentFloor < m_targetFloor)
        ++m_currentFloor;
    else if (m_currentFloor > m_targetFloor)
        --m_currentFloor;
    

    display_floor();

    if (m_currentFloor == m_targetFloor){
        m_timer->stop();
        m_moving = false;
        emit statusChanged("Arrived");
    }
}

void Elevator::display_floor()
{
    emit floorChanged(m_currentFloor);
}

void Elevator::setCurrentFloor(int floor)
{
    if (m_moving)
        return;

    if (floor < 1 || floor > 10)
        return;

    m_currentFloor = floor;
    m_targetFloor = floor;

    display_floor();
    emit statusChanged("Arrived");
}