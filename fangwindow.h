#ifndef FANGWINDOW_H
#define FANGWINDOW_H

#include "clock.h"
#include "comment.h"
#include "statsdialog.h"

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class FangWindow;
}
QT_END_NAMESPACE

class FangWindow : public QMainWindow
{
    Q_OBJECT

public:
    FangWindow(QWidget *parent = nullptr);
    ~FangWindow();

    // Timer functions
    // Props
    uint workTime() const;
    void setWorkTime(uint minutes);

    uint restTime() const;
    void setRestTime(uint minutes);

    uint longRestTime() const;
    void setLongRestTime(uint minutes);

    void updateLoop();
    void updateGui(); // UI related

    // Timer related
    void start();
    void stop();

private:
    Ui::FangWindow *ui;

    // ATTRIBUTES
    // Timer
    QTimer *m_timer;

    // Timer props
    // Vars in seconds
    uint m_workTime = 1500;
    uint m_restTime = 300;
    uint m_longRestTime = 900;

    uint m_currentTime;
    uint m_totalTime;

    // Timer props - state related
    enum state {
        WORK,
        REST,
        LONG_REST
    };

    short m_currentState = 0;

    short m_controlLoop = 1;
    uint m_guiLoops = 1;

    // Timer - GUI
    Clock *wClock;
    Comment *wComment;

    // Timer - Notifier
    QSystemTrayIcon *notifier;
    QSoundEffect *jingle;

    // GUI - Stats
    StatsDialog *dStats;

    // METHODS
    //void readConfig();

private slots:
    void tick();
    void on_btnInteract_toggled(bool checked);
    void on_btnReset_clicked();

    //void updateConfig(); // Re-read configs
    void on_btnStats_clicked();
};
#endif // FANGWINDOW_H
