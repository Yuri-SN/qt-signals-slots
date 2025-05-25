#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_stopWatch = new Stopwatch(this);
    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::toggleState);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearClick);
    connect(ui->loopButton, &QPushButton::clicked, this, &MainWindow::onLoopClick);

    setInitState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInitState()
{
    ui->timeLabel->setText(m_timerStartText);
    ui->startButton->setText(m_buttonStartLabel);
    ui->clearButton->setText("Очистить");
    ui->loopButton->setText("Круг");
    ui->loopButton->setEnabled(false);
    ui->infoLabel->setText("");
}

void MainWindow::setStartedState()
{
    ui->loopButton->setEnabled(true);
    ui->startButton->setText(m_buttonStopLabel);
    m_stopWatch->start();
    m_timer->start(m_uptadeInterval);
}

void MainWindow::setStoppedState()
{
    ui->loopButton->setEnabled(false);
    ui->startButton->setText(m_buttonStartLabel);
    m_stopWatch->stop();
    m_timer->stop();
}

// Slots

void MainWindow::onTimerTick()
{
    ui->timeLabel->setText(convertTime(m_stopWatch->getElapsedTime()));
}

void MainWindow::toggleState()
{
    if (m_stopWatch->isStarted()) {
        setStoppedState();
    } else {
        setStartedState();
    }
}

void MainWindow::onClearClick()
{
    ui->timeLabel->setText(m_timerStartText);
    ui->infoLabel->setText("");

    m_loopTimeStart = 0;
    m_loopTimeStop = 0;
    m_loopCount = 1;

    m_stopWatch->reset();
}

void MainWindow::onLoopClick()
{
    m_loopTimeStop = m_stopWatch->getElapsedTime();

    ui->infoLabel->setText(QString("Круг %1, время: %2 сек")
                               .arg(m_loopCount)
                               .arg(getSeconds(m_loopTimeStop - m_loopTimeStart)));

    m_loopCount += 1;
    m_loopTimeStart = m_stopWatch->getElapsedTime();
}

// Private

QString MainWindow::convertTime(qint64 timeInMs)
{
    quint8 hours = (timeInMs / 3600000);
    quint8 minutes = (timeInMs / 60000) % 60;
    QString seconds = getSeconds(timeInMs);

    auto result = QString("%1:%2:%3")
                      .arg(hours, 2, 10, QChar('0'))
                      .arg(minutes, 2, 10, QChar('0'))
                      .arg(seconds);

    return result;
}

QString MainWindow::getSeconds(qint64 timeInMs)
{
    quint8 seconds = (timeInMs / 1000) % 60;
    quint16 tenths = (timeInMs % 1000) / 100;

    auto result = QString("%1.%2").arg(seconds, 2, 10, QChar('0')).arg(tenths);

    return result;
}
