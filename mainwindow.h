#pragma once

#include <QMainWindow>
#include "./Stopwatch.h"

#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setInitState();
    void setStartedState();
    void setStoppedState();

private slots:
    void toggleState();
    void onClearClick();
    void onLoopClick();
    void onStopwatchTick();

  private:
    Ui::MainWindow *ui;
    Stopwatch *m_stopWatch;

    const QString m_buttonStartLabel{"Старт"};
    const QString m_buttonStopLabel{"Стоп"};
    const QString m_timerStartText{"00:00:00.0"};

    quint16 m_loopCount{1};
    qint64 m_loopTimeStart{0};
    qint64 m_loopTimeStop{0};

    QString convertTime(qint64 timeInMs);
    QString getSeconds(qint64 timeInMs);
};
