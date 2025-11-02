#include "clock.h"

Clock::Clock(QWidget *parent)
    : QWidget{parent}
{
    clockLayout = new QGridLayout(this);

    labelContainer = new QWidget();
    labelLayout = new QVBoxLayout(labelContainer);

    lbClock = new QLabel();
    lbClock->setAlignment(Qt::AlignCenter);
    lbClock->setFont(QFont("Sans Serif", 32));
    lbClock->setText("00:00");

    lbState = new QLabel();
    lbState->setAlignment(Qt::AlignCenter);
    lbState->setFont(QFont("Sans Serif", 16));
    lbState->setText("-");

    labelLayout->addWidget(lbClock);
    labelLayout->addWidget(lbState);

    // Set arc
    arc = new TProgressArcStatic();
    arc->setPenWidth(20);
    arc->setAngle(217);
    arc->setMaximum(70);
    arc->setValue(70);

    clockLayout->addWidget(arc, 0, 0, -1, -1, Qt::AlignCenter);
    clockLayout->addWidget(labelContainer, 0, 0, Qt::AlignCenter);
    clockLayout->setRowStretch(0, 1);
    clockLayout->setColumnStretch(0, 1);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Clock::updateClock(QString text) {
    lbClock->setText(text);
    update();
}

void Clock::updateState(QString text) {
    lbState->setText(text);
    update();
}

void Clock::updateArc(int value) {
    arc->setValue(value);
    update();
}

void Clock::setArcColor(QColor color) {
    arc->setProgressColor(color);
}
