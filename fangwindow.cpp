#include "fangwindow.h"
#include "ui_fangwindow.h"

#include <math.h>
#include <QDebug>
#include <QMediaPlaylist>

FangWindow::FangWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FangWindow)
{
    ui->setupUi(this);

    // Set timer props from file

    // Notifier
    notifier = new QSystemTrayIcon(this);
    notifier->setIcon(QIcon("qrc:/icons/icon.png"));

    jingle = new QSoundEffect(this);
    jingle->setSource(QUrl("qrc:/notifications/notification.wav"));
    jingle->setVolume(0.7f);
    jingle->setLoopCount(1);

    // Set clock widget
    // UI - Clock
    wClock = new Clock();
    wComment = new Comment();

    // UI - Stats
    dStats = new StatsDialog(this);

    // UI - Add components
    ui->layClock->addWidget(wClock, 2, Qt::AlignTop);
    ui->layClock->addWidget(wComment, 1, Qt::AlignBottom);

    // Timer set up
    m_totalTime = m_workTime;
    m_currentTime = m_workTime;
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &FangWindow::tick);
}

uint FangWindow::workTime() const {
    return m_workTime;
}

void FangWindow::setWorkTime(uint minutes) {
    m_workTime = minutes * 60;
}

uint FangWindow::restTime() const {
    return m_restTime;
}

void FangWindow::setRestTime(uint minutes) {
    m_restTime = minutes * 60;
}

uint FangWindow::longRestTime() const {
    return m_longRestTime;
}

void FangWindow::updateLoop() {
    m_controlLoop++;
    m_guiLoops++;

    QString message;

    if (m_controlLoop % 2 != 0) {
        m_currentState = state::WORK;
        m_currentTime = m_workTime;
        m_totalTime = m_workTime;
        message = tr("The work cycle started. Try to avoid distractions.");
        wClock->setArcColor(QColor::fromRgb(0, 87, 255));
    } else if (m_controlLoop == 2 || m_controlLoop == 4) {
        m_currentState = state::REST;
        m_currentTime = m_restTime;
        m_totalTime = m_restTime;
        message = tr("Time to rest a bit");
        wClock->setArcColor(QColor::fromRgb(200, 200, 50));
    } else {
        m_currentState = state::LONG_REST;
        m_currentTime = m_longRestTime;
        m_totalTime = m_longRestTime;
        message = tr("Time to take a break, mind to stretch your legs");
        wClock->setArcColor(QColor::fromRgb(0, 200, 255));
        m_controlLoop = 0;
    }

    notifier->show();
    notifier->showMessage("Fang Timer", message, QSystemTrayIcon::Information);
    jingle->play();
    notifier->hide();
}

void FangWindow::updateGui() {
    // Update clock arc
    float percent = (m_currentTime * 70) / m_totalTime;
    wClock->updateArc(ceil(percent));

    // Update clock
    int minutes = m_currentTime / 60;
    int seconds = m_currentTime % 60;

    wClock->updateClock(QString::asprintf("%02d:%02d", minutes, seconds));


    // Update loop
    if (m_currentState == state::WORK) {
        wClock->updateState(tr("Work"));
    } else if (m_currentState == state::REST) {
        wClock->updateState(tr("Rest"));
    } else {
        wClock->updateState(tr("Long Rest"));
    }
}

// Called every second
void FangWindow::tick() {
    if (m_currentTime > 0) {
        updateGui();
        m_currentTime--;
    } else {
        m_timer->stop();
        updateLoop();
        updateGui();
        start();
    }
}

void FangWindow::start() {
    m_timer->start(1000);
}

void FangWindow::stop() {
    m_timer->stop();
}

FangWindow::~FangWindow()
{
    delete ui;
}

void FangWindow::on_btnInteract_toggled(bool checked)
{
    if (checked) {
        start();
        ui->btnInteract->setIcon(QIcon::fromTheme("media-playback-pause"));
    } else {
        stop();
        ui->btnInteract->setIcon(QIcon::fromTheme("media-playback-start"));
    }
}


void FangWindow::on_btnReset_clicked()
{
    stop();
    m_controlLoop = 1;
    wClock->updateClock("00:00");
    wClock->updateState(tr("Reset"));
    wClock->updateArc(0);

    m_currentState = 0;
    m_currentTime = m_workTime;
}


void FangWindow::on_btnStats_clicked()
{
    dStats->show();
}

