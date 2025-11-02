#include "counter.h"

Counter::Counter() {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Counter::tick);
    timer->start(1000);  // Cada segundo
}

void Counter::tick() {
    m_count++;
    qDebug() << "Segundo:" << m_count;

    if (m_count >= 5) {
        qDebug() << "Fin!";
    }
}
