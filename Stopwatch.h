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

    bool isStarted();

    qint64 getElapsedTime();

  private slots:
    void onTimerTick();

  private:
    QTimer* m_timer;
    qint64 m_totalTimeMs{0};
    bool m_isStarted{false};

    const quint16 m_tickInterval{100};
};
