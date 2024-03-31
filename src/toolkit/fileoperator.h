#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <QString>

namespace ToolKit {
    enum FileModule{
        LOG,                    // 日志
        SETTING,                // 编辑器配置
        SAVE,                   // 项目数据
        SOURCE_FONT             // 资源文件
    };
    class FileOperator
    {
    public:
        static QString GetProjectPath();
        /**
         * @brief 获取模块配置路径，该路径不存在时会创建该路径
        */
        static QString GetSubModulePath(FileModule module);
        static bool CheckDirExists(const QString& folderPath);
        static bool CreateFolder(const QString& folderPath);
    };
}

#endif // FILEOPERATOR_H
