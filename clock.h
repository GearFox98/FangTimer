#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "tprogressarcstatic.h"

class Clock : public QWidget
{
    Q_OBJECT
public:
    explicit Clock(QWidget *parent = nullptr);

    void updateClock(QString text);
    void updateState(QString text);
    void updateArc(int value);
    void setArcColor(QColor color);

private:
    QGridLayout *clockLayout;
    QWidget *labelContainer;
    QVBoxLayout *labelLayout;
    TProgressArcStatic *arc;
    QLabel *lbClock;
    QLabel *lbState;
};

#endif // CLOCK_H
