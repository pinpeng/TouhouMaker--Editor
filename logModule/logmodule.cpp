#include "logModule/logmodule.h"
#include <QMutexLocker>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include "toolkit/fileoperator.h"
#include "toolkit/timeoperator.h"

namespace LogModule {

void StaticLogHandler(QtMsgType type,const QMessageLogContext& context,const QString& msg){
    static LogModule logModule;
    logModule.LogHandler(type,context,msg);
}

LogModule::LogModule(){
    _curDate = ToolKit::TimeOperator::GetCurDate();
    QString logFilePath = getCurLogPath(_curDate);
    _logFile.setFileName(logFilePath);
    _logFile.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    _logFile.write("Qt log initialize finished!");
    _logFile.flush();
}

void LogModule::LogHandler(QtMsgType type,const QMessageLogContext& context,const QString& msg){
    QMutexLocker lock(&_logMutex);

    QString curDate = ToolKit::TimeOperator::GetCurDate();

    if(_curDate != curDate){
        // change log file
        _logFile.flush();
        _logFile.close();
        _curDate = curDate;
        _logFile.setFileName(getCurLogPath(_curDate));
        _logFile.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    }

    // [版本][时间}[函数名][级别]日志内容
    QTextStream ts(&_logFile);

    // add version
    ts << "[" << APP_VERSION << "]";

    // add time
    ts << "[" << ToolKit::TimeOperator::GetCurTime() << "]";

    // add fileName
    ts << "[" << context.function << "]";

    // add log level
    ts << getLogLevel(type) << " ";

    // add log
    ts << msg << "\n";

    ts.flush();
}

QString LogModule::getCurLogPath(QString date){
    QString folderPath = ToolKit::FileOperator::GetProjectPath().append("/logs/");
    if(!ToolKit::FileOperator::CheckDirExists(folderPath)){
        ToolKit::FileOperator::CreateFolder(folderPath);
    }
    return ToolKit::FileOperator::GetProjectPath().append("/logs/").append(date).append(".log");
}

QString LogModule::getLogLevel(QtMsgType type){
    // QtDebugMsg, QtWarningMsg, QtCriticalMsg, QtFatalMsg, QtInfoMsg, QtSystemMsg = QtCriticalMsg
    switch (type) {
    case QtDebugMsg:
        return "[DEBUG]";
    case QtWarningMsg:
        return "[WARNING]";
    case QtCriticalMsg:
        return "[CRITICAL]";
    case QtFatalMsg:
        return "[FATAL]";
    case QtInfoMsg:
        return "[INFO]";
    default:
        break;
    }
    return "[UNKOWN]";
}
}
