#ifndef TPROGRESSARCSTATIC_H
#define TPROGRESSARCSTATIC_H

#include "tprogressarcstatic.h"

#include <QProgressBar>
#include <QVBoxLayout>
#include <QWidget>

class TProgressArcStatic : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor NOTIFY progressColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged)
    Q_PROPERTY(int angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(bool flat READ flat WRITE setFlat NOTIFY flatChanged)

public:
    explicit TProgressArcStatic(QWidget *parent = nullptr);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    QColor progressColor() const;
    void setProgressColor(const QColor &color);

    int penWidth() const;
    void setPenWidth(int width);

    int angle() const;
    void setAngle(int value);

    bool flat() const;
    void setFlat(bool value);

signals:
    void progressColorChanged();
    void backgroundColorChanged();
    void penWidthChanged();
    void angleChanged();
    void flatChanged();

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;

    bool hasHeightForWidth() const override { return true; }
    int heightForWidth(int width) const override { return width; }

private:
    QColor m_backgroundColor;
    QColor m_progressColor;
    int m_penWidth;
    int m_angle;
    bool m_flat;
};

#endif // TPROGRESSARCSTATIC_H
