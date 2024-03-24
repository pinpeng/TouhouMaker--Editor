#include "globalSource/timerManager.h"
#include <QMutexLocker>
#include <QDebug>

namespace GlobalSource{
    TimerManager::TimerManager(){
        _repaintTimer = QSharedPointer<QTimer>::create();
        _repaintTimer->start(1000/60);
        _timerMap.insert(TIMER_REPAINT,_repaintTimer);
    }

    bool TimerManager::RegistNewTimer(const QString& timerName,int interval){
        QMutexLocker lock(&_rwMutex);
        if(_timerMap.end() != _timerMap.find(timerName)){
            qWarning() << "Cannot create new timer named "<<timerName << " ,this timer already exists!";
            return false;
        }
        QSharedPointer<QTimer> timer = QSharedPointer<QTimer>::create();
        timer->start(interval);
        _timerMap.insert(timerName,timer);
        return true;
    }

    const QSharedPointer<QTimer>& TimerManager::GetTimer(const QString& timerName){\
        QMutexLocker lock(&_rwMutex);
        if(_timerMap.end() == _timerMap.find(timerName)){
            qWarning() << "Cannot find timer " << timerName;
            return nullptr;
        }

        return _timerMap[timerName];
    }
}