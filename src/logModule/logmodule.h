#ifndef LOGMODULE_H
#define LOGMODULE_H

#include <QtDebug>
#include <QMessageLogContext>
#include <QString>
#include <QMutex>
#include <QFile>

namespace LogModule {
    class LogModule{
    public:
        LogModule();
        /**
         * @brief 日志钩子，设置日志格式并打印日志到文件中。当前日志格式为[版本][时间}[函数名][级别]日志内容
         * @param type
         * @param context
         * @param msg
         */
        void LogHandler(QtMsgType type,const QMessageLogContext& context,const QString& msg);
    private:
        QString getLogLevel(QtMsgType type);
        QString getCurLogPath(QString date);
    private:
        QMutex _logMutex;
        QString _curDate;
        QFile _logFile;
    };

    void StaticLogHandler(QtMsgType type,const QMessageLogContext& context,const QString& msg);
}

#endif // LOGMODULE_H
