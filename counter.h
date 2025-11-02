#ifndef COUNTER_H
#define COUNTER_H

#include <QDebug>
#include <QTimer>

class Counter : public QObject
{
    Q_OBJECT
    int m_count = 0;
public:
    Counter();

private slots:
    void tick();
};

#endif // COUNTER_H
