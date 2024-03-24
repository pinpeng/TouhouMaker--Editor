#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <QMap>
#include <QTimer>
#include <QMutex>
#include <QSharedPointer>

namespace GlobalSource{
    const static QString TIMER_REPAINT              = "repaint";

    class TimerManager{
        public:
        TimerManager();
        bool RegistNewTimer(const QString& timerName,int interval);
        const QSharedPointer<QTimer>& GetTimer(const QString& timerName);
        private:
        QSharedPointer<QTimer> _repaintTimer;
        QMap<QString,QSharedPointer<QTimer>> _timerMap;
        QMutex _rwMutex;
    };
}

#endif