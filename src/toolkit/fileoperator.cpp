#include "fileoperator.h"
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

namespace ToolKit{

QString FileOperator::_projectPath = "";

QString FileOperator::getEditorPath(){
    return QCoreApplication::applicationDirPath();
}

QString FileOperator::getEditorSubModulePath(FileModule module){
    QString editorPath = getEditorPath();
    QString subPath = "";
    switch(module){
        case FileModule::LOG:{
            subPath = editorPath + "/log/";
        }
        break;
        case FileModule::CRASH:{
            subPath = editorPath + "/crash/";
        }
        break;
        case FileModule::SETTING:{
            subPath = editorPath + "/setting/";
        }
        break;
        case FileModule::SOURCE_FONT:{
            subPath = editorPath + "/font/";
        }
        default:{
            qCritical() << "cannot find module " << module;
            subPath = editorPath;
        }
    }

    try{
        if(!checkDirExists(subPath)){
            createFolder(subPath);
        }
    }
    catch(const std::exception& e){
        return editorPath;
    }

    return subPath;
}

bool FileOperator::checkDirExists(const QString& folderPath){
    QDir dir(folderPath);
    return dir.exists();
}

bool FileOperator::createFolder(const QString& folderPath){
    QDir dir(folderPath);
    if(!dir.exists()){
        dir.mkpath(".");
    }
}

QString FileOperator::setProjectPath(const QString& path){
    _projectPath = path;
}

QString FileOperator::getProjectSubModulePath(ProjectModule module){
    QString subPath = "";
    switch(module){
        case ProjectModule::IMAGE:
            subPath = _projectPath + "/image/";
            break;
        case ProjectModule::DATA:
            subPath = _projectPath + "/data";
            break;
        case ProjectModule::AUDIO:
            subPath = _projectPath + "/audio";
            break;
        default:
            subPath = _projectPath;
    }
    try{
        if(!checkDirExists(subPath)){
            createFolder(subPath);
        }
    }
    catch(const std::exception& e){

    }
    return subPath;
}

QString FileOperator::getFileName(const QString& filePath){
    int n = filePath.lastIndexOf("/");
    if(n != -1){
        return filePath.mid(n+1);
    }
    return filePath;
}

}
