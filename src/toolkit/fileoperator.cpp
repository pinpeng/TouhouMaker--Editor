#include "fileoperator.h"
#include <QDir>

namespace ToolKit{
QString FileOperator::GetProjectPath(){
    return QDir::currentPath();
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
