#include "Stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{
    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &Stopwatch::onTimerTick);
}

Stopwatch::~Stopwatch()
{
    delete m_timer;
}

void Stopwatch::start()
{
    m_isStarted = true;
    m_timer->start(m_tickInterval);
}

void Stopwatch::stop()
{
    m_isStarted = false;
    m_totalTimeMs += m_timer->remainingTime();
    m_timer->stop();
}

void Stopwatch::reset()
{
    m_totalTimeMs = 0;
    if (m_isStarted) {
        m_timer->start();
    }

    m_loopTimeStart = 0;
    m_loopTimeStop = 0;
    m_loopCount = 1;
}

QString Stopwatch::loopResult() {
    m_loopTimeStop = getElapsedTime();

    QString result =
        QString("Круг %1, время: %2 сек").arg(m_loopCount).arg(getSeconds(m_loopTimeStop - m_loopTimeStart));

    m_loopCount += 1;
    m_loopTimeStart = getElapsedTime();

    return result;
}

bool Stopwatch::isStarted()
{
    return m_isStarted;
}

qint64 Stopwatch::getElapsedTime()
{
    return m_totalTimeMs;
}

QString Stopwatch::getTime() {
    auto result = convertTime(getElapsedTime());

    return result;
}

// Slots

void Stopwatch::onTimerTick()
{
    m_totalTimeMs += m_tickInterval;

    emit signalTimerTick();
}

// Private

QString Stopwatch::convertTime(qint64 timeInMs) {
    quint8 hours = (timeInMs / 3600000);
    quint8 minutes = (timeInMs / 60000) % 60;
    QString seconds = getSeconds(timeInMs);

    auto result = QString("%1:%2:%3").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0')).arg(seconds);

    return result;
}

QString Stopwatch::getSeconds(qint64 timeInMs) {
    quint8 seconds = (timeInMs / 1000) % 60;
    quint16 tenths = (timeInMs % 1000) / 100;

    auto result = QString("%1.%2").arg(seconds, 2, 10, QChar('0')).arg(tenths);

    return result;
}
