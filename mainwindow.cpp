#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_stopWatch = new Stopwatch(this);

    connect(m_stopWatch, &Stopwatch::signalTimerTick, this, &MainWindow::onStopwatchTick);

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
    ui->textBrowser->clear();
}

void MainWindow::setStartedState()
{
    ui->loopButton->setEnabled(true);
    ui->startButton->setText(m_buttonStopLabel);
    m_stopWatch->start();
}

void MainWindow::setStoppedState()
{
    ui->loopButton->setEnabled(false);
    ui->startButton->setText(m_buttonStartLabel);
    m_stopWatch->stop();
}

// Slots

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
    ui->textBrowser->clear();

    m_stopWatch->reset();
}

void MainWindow::onLoopClick()
{
    ui->textBrowser->append(m_stopWatch->loopResult());
}

void MainWindow::onStopwatchTick() {
    ui->timeLabel->setText(m_stopWatch->getTime());
}
