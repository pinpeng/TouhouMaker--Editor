#include "fileoperator.h"
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

namespace ToolKit{
QString FileOperator::GetProjectPath(){
    return QCoreApplication::applicationDirPath();
}

QString FileOperator::GetSubModulePath(FileModule module){
    QString projectPath = GetProjectPath();
    QString subPath = "";
    switch(module){
        case FileModule::LOG:{
            subPath = projectPath + "/log/";
        }
        break;
        case FileModule::CRASH:{
            subPath = projectPath + "/crash/";
        }
        break;
        case FileModule::SETTING:{
            subPath = projectPath + "/setting/";
        }
        break;
        case FileModule::SAVE:{
            subPath = projectPath + "/save/";
        }
        break;
        case FileModule::SOURCE_FONT:{
            subPath = projectPath + "/font/";
        }
        default:{
            qCritical() << "cannot find module " << module;
            subPath = projectPath;
        }
    }

    try{
        if(!CheckDirExists(subPath)){
            CreateFolder(subPath);
        }
    }
    catch(const std::exception& e){
        // qDebug() << "check or create folder failed! what:"<<e.what();
        return projectPath;
    }

    return subPath;
}

bool FileOperator::CheckDirExists(const QString& folderPath){
    QDir dir(folderPath);
    return dir.exists();
}

bool FileOperator::CreateFolder(const QString& folderPath){
    QDir dir(folderPath);
    if(!dir.exists()){
        dir.mkpath(".");
    }
}

}
