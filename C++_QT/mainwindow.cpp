#include "mainwindow.h"
#include "elevator.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include <QIntValidator>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("Elevator Simulator");
    resize(700, 400);
    
    // init radom floor
    int floor1 = QRandomGenerator::global()->bounded(1, 11);
    int floor2 = QRandomGenerator::global()->bounded(1, 11);

    m_elevator1 = new Elevator(1, floor1, this);
    m_elevator2 =new Elevator(2, floor2, this);

    QWidget *central = new QWidget(this);

    setCentralWidget(central);

    // Title
    QLabel *title = new QLabel("Elevator Simulator");
    title->setAlignment(Qt::AlignCenter);
    QFont font = title->font();

    font.setPointSize(20);
    font.setBold(true);

    title->setFont(font);

    // Elevator Layout
    QHBoxLayout *elevatorLayout = new QHBoxLayout();
    elevatorLayout->addWidget(createElevatorWidget(m_elevator1));
    elevatorLayout->addWidget(createElevatorWidget(m_elevator2));

    // Main Layout
    QVBoxLayout *mainLayout =new QVBoxLayout(central);
    mainLayout->addWidget(title);
    mainLayout->addLayout(elevatorLayout);
}


QWidget *MainWindow::createElevatorWidget(Elevator *elevator){
    QWidget *widget =new QWidget();

    // Elevator Title
    QLabel *title = new QLabel(QString("Elevator %1").arg(elevator->getId()) );
    title->setAlignment(Qt::AlignCenter);

    // Current Floor
    QLineEdit *currentFloor = new QLineEdit();
    currentFloor->setText( QString::number(elevator->getCurrentFloor()));
    currentFloor->setAlignment(Qt::AlignCenter);
    currentFloor->setValidator(new QIntValidator(1, 10, currentFloor));

    // Status
    QLabel *status =new QLabel("Arrived");

    // Target Floor
    QLineEdit *targetFloor = new QLineEdit();
    targetFloor->setPlaceholderText("1 - 10");
    targetFloor->setValidator(new QIntValidator(1, 10, targetFloor));

    // Go Button
    QPushButton *goButton = new QPushButton("Go");

    // Layout
    QFormLayout *form = new QFormLayout();

    form->addRow("Current Floor:", currentFloor);
    form->addRow("Status:", status);
    form->addRow("Target Floor:", targetFloor);


    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(title);
    layout->addLayout(form);
    layout->addWidget(goButton);

    // Go
    connect(goButton, &QPushButton::clicked, this,
        [elevator, targetFloor]()
        {
            bool ok;
            int floor = targetFloor->text().toInt(&ok);
            if (!ok) return;
            int currentFloor = elevator->getCurrentFloor();
            elevator->move(currentFloor, floor);
        }
    );
 
    // Current Floor Update
    connect(elevator, &Elevator::floorChanged, this,
        [currentFloor](int floor)
        {
            currentFloor->setText(QString::number(floor));
        }
    );

    // Status Update
    connect(elevator, &Elevator::statusChanged, this,
        [status](const QString &text)
        {
            status->setText(text);
        }
    );

    // Current Floor Input
    connect(currentFloor, &QLineEdit::editingFinished, this,
        [elevator, currentFloor]()
        {
            bool ok;
            int floor = currentFloor->text().toInt(&ok);
            if (!ok) return;
            elevator->setCurrentFloor(floor);
        }
    );
    return widget;
}