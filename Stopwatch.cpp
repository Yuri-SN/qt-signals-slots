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
}

bool Stopwatch::isStarted()
{
    return m_isStarted;
}

qint64 Stopwatch::getElapsedTime()
{
    return m_totalTimeMs;
}

// Slots

void Stopwatch::onTimerTick()
{
    m_totalTimeMs += m_tickInterval;
}
