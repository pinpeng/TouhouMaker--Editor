#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <QString>

namespace ToolKit {
    class FileOperator
    {
    public:
        static QString GetProjectPath();
        static bool CheckDirExists(const QString& folderPath);
        static bool CreateFolder(const QString& folderPath);
    };
}

#endif // FILEOPERATOR_H
