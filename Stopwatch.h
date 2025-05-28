#pragma once

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject {
    Q_OBJECT

  signals:
    void signalTimerTick();

  public:
    explicit Stopwatch(QObject* parent = nullptr);
    ~Stopwatch();

    void start();
    void stop();
    void reset();

    QString loopResult();

    bool isStarted();

    qint64 getElapsedTime();
    QString getTime();

  private slots:
    void onTimerTick();

  private:
    QTimer* m_timer;
    qint64 m_totalTimeMs{0};
    bool m_isStarted{false};

    const quint16 m_tickInterval{100};

    quint16 m_loopCount{1};
    qint64 m_loopTimeStart{0};
    qint64 m_loopTimeStop{0};

    QString convertTime(qint64 timeInMs);
    QString getSeconds(qint64 timeInMs);
};
