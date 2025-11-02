#include "tprogressarcstatic.h"

#include <QtPlugin>
#include <QResizeEvent>
#include <QPainter>

#include <QDebug>

TProgressArcStatic::TProgressArcStatic(QWidget *parent)
    : QProgressBar(parent), m_backgroundColor(Qt::darkGray),
    m_progressColor(QColor::fromRgb(0, 86, 255)), m_penWidth(5), m_angle(270), m_flat(true)
{
    setValue(0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(50, 50);
}

QColor TProgressArcStatic::backgroundColor() const {
    return m_backgroundColor;
}

void TProgressArcStatic::setBackgroundColor(const QColor &color) {
    if(m_backgroundColor != color) {
        m_backgroundColor = color;
        update();
        emit backgroundColorChanged();
    }
}

QColor TProgressArcStatic::progressColor() const {
    return m_progressColor;
}

void TProgressArcStatic::setProgressColor(const QColor &color){
    if(m_progressColor != color) {
        m_progressColor = color;
        update();
        emit progressColorChanged();
    }
}

int TProgressArcStatic::penWidth() const {
    return m_penWidth;
}

void TProgressArcStatic::setPenWidth(int width) {
    if(m_penWidth != width) {
        m_penWidth = width;
        update();
        emit penWidthChanged();
    }
}

int TProgressArcStatic::angle() const {
    return m_angle;
}

void TProgressArcStatic::setAngle(int value){
    if(m_angle != value) {
        m_angle = value;
        update();
        emit angleChanged();
    }
}

bool TProgressArcStatic::flat() const {
    return m_flat;
}

void TProgressArcStatic::setFlat(bool value) {
    if (m_flat != value) {
        m_flat = value;
        update();
        emit flatChanged();
    }
}

void TProgressArcStatic::paintEvent(QPaintEvent *) {
    int progress = this->value();
    int progressInDegrees = (progress * 360) / 100;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen backgroundPen;
    backgroundPen.setColor(m_backgroundColor);
    backgroundPen.setWidth(m_penWidth);
    if (m_flat) {
        backgroundPen.setCapStyle(Qt::FlatCap);
    } else {
        backgroundPen.setCapStyle(Qt::RoundCap);
    }

    QPen pen;
    pen.setColor(m_progressColor);
    pen.setWidth(m_penWidth);
    if (m_flat) {
        pen.setCapStyle(Qt::FlatCap);
    } else {
        pen.setCapStyle(Qt::RoundCap);
    }

    painter.setPen(backgroundPen);
    painter.drawArc(10, 10, this->width()-20, this->height()-20, 16 * m_angle, -16 * (maximum() * 3.6));

    painter.setPen(pen);
    painter.drawArc(10, 10, this->width()-20, this->height()-20, 16 * m_angle, -16 * progressInDegrees);
}

void TProgressArcStatic::resizeEvent(QResizeEvent *event) {
    QProgressBar::resizeEvent(event);
    if (parentWidget()) {
        int shortSide = qMin(parentWidget()->width(), parentWidget()->height());
        setFixedSize(shortSide, shortSide);
        //resize(shortSide, shortSide);
    }
}
